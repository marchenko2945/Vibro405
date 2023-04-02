#include "modbus.h"

static BusState_t BusState = BUS_BUSY;


static uint8_t MyAddress = 100;
static uint8_t temp_rx[1];
static uint8_t rx_buf[16];
static uint8_t tx_buf[128];
static uint8_t rx_ptr = 0;

void UpdateMB_MapData(MB_Funcs_t func);
void ExecuteMB(void);

static uint8_t CheckCrc()
{
	uint16_t recCrc = rx_buf[rx_ptr - 1] | rx_buf[rx_ptr - 2] << 8;

	if((uint32_t)(rx_ptr-2) > sizeof(rx_buf))
		return 0;

	if(recCrc == CRC16(rx_buf, rx_ptr-2))
		return 1;
	else
		return 0;
}

static void UpdateTimer(void)
{
	TIM6->CNT = 0;
	//HAL_TIM_Base_Start_IT(&htim6);
	TIM6->DIER |= 1<<0;
	TIM6->CR1 |= 1<<0;
}

static void SetTimer(uint32_t us)
{
	//работа таймера должны быть настроена на 3.5+ байта, или 4 с учетом старт-стопов
	//При 9600 это 3.5мс
	SystemCoreClockUpdate();
	uint32_t SysFreq = HAL_RCC_GetHCLKFreq();
	TIM6->PSC = SysFreq / 1000000;
	TIM6->ARR = us;
	TIM6->SR = 0;
	UpdateTimer();
}

void ModBusInit(void)
{
	SET_TX_DIR();
	SET_RX_DIR();
	HAL_UART_Receive_DMA(&huart3, temp_rx, sizeof(temp_rx));
}

static void MB_SendErrorMsg(uint8_t func, Errors_t error)
{
	uint16_t crc;
	tx_buf[ADR_POS] = MyAddress;
	tx_buf[FUNC_POS] = func | 0x80;
	tx_buf[2] = error;
	crc = CRC16(tx_buf, 3);
	tx_buf[3] = crc>>8;
	tx_buf[4] = crc&0xFF;
	SET_TX_DIR();
	HAL_UART_Transmit_IT(&huart3, tx_buf, 5);

}

static int isCorrectAddress(MB_Funcs_t func, uint16_t addr, uint16_t cnt){

	int adressInArray = -1;

	if(func == READ_INPUTS){
		for(uint8_t i = 0; i < InputRegsSize; i++){
			if( InputRegisters[i].address == addr){
				adressInArray = i;
				for(uint8_t k = 1; k < cnt; k++){
					if( InputRegisters[i+k].address != addr + k){
						adressInArray = -1;
						goto EXIT;
					}
				}
			}
		}
	}else if(func == READ_DISCRETE){
		for(uint8_t i = 0; i < DiscreteInputsSize; i++){
			if( DiscreteInputs[i].address == addr){
				adressInArray = i;
				for(uint8_t k = 1; k < cnt; k++){
					if( DiscreteInputs[i+k].address != addr + k){
						adressInArray = -1;
						goto EXIT;
					}
				}
			}
		}
	}else if(func == READ_COILS || func == WRITE_COIL){
		for(uint8_t i = 0; i < CoilsSize; i++){
			if( Coils[i].address == addr){
				adressInArray = i;
				for(uint8_t k = 1; k < cnt; k++){
					if( Coils[i+k].address != addr + k){
						adressInArray = -1;
						goto EXIT;
					}
				}
			}
		}
	}


	EXIT:
	return adressInArray;
}

static void SendInputs(uint16_t address, uint16_t cnt)
{
	uint16_t crc;
	int adrInArray = isCorrectAddress(READ_INPUTS, address, cnt);

	if(adrInArray < 0)
	{
		MB_SendErrorMsg(READ_INPUTS, MB_ADDR_ERROR);
		return;
	}

	UpdateMB_MapData(READ_INPUTS);

	tx_buf[ADR_POS] = MyAddress;
	tx_buf[FUNC_POS] = READ_INPUTS;
	tx_buf[CNT_POS] = cnt*2;

	for(uint16_t i = 0, offset = 0; i < cnt; i++, offset+=2){
		memcpy(&tx_buf[DATA_POS+offset], &InputRegisters[adrInArray+i].value, 2);
	}
	crc = CRC16(tx_buf, 3+cnt*2);

	tx_buf[DATA_POS+cnt*2] = crc>>8;
	tx_buf[DATA_POS+1+cnt*2] = crc&0xFF;
	SET_TX_DIR();
	HAL_UART_Transmit_IT(&huart3, tx_buf, 5+cnt*2);
}

static void SendDiscrete(uint16_t address, uint16_t cnt)
{
	uint16_t crc;
	int adrInArray = isCorrectAddress(READ_DISCRETE, address, cnt);

	if(adrInArray < 0)
	{
		MB_SendErrorMsg(READ_DISCRETE, MB_ADDR_ERROR);
		return;
	}

	tx_buf[ADR_POS] = MyAddress;
	tx_buf[FUNC_POS] = READ_DISCRETE;
	tx_buf[CNT_POS] = 1 + cnt/8;

	tx_buf[DATA_POS] = 0;
	for(uint16_t i = 0, shift = 0, offset = 0; i < cnt; i++, shift++){
		if(shift == 8){
			shift = 0;
			offset++;
			tx_buf[DATA_POS+ offset] = 0;
		}
		tx_buf[DATA_POS + offset] |= (DiscreteInputs[adrInArray + i].value << shift);
	}
	crc = CRC16(tx_buf, 3+ (1+cnt/8));

	tx_buf[DATA_POS+(1+cnt/8)] = crc>>8;
	tx_buf[DATA_POS+1+(1+cnt/8)] = crc&0xFF;
	SET_TX_DIR();
	HAL_UART_Transmit_IT(&huart3, tx_buf, 5+(1+cnt/8));
}

static void SendCoils(uint16_t address, uint16_t cnt)
{
	uint16_t crc;
	int adrInArray = isCorrectAddress(READ_COILS, address, cnt);

	if(adrInArray < 0)
	{
		MB_SendErrorMsg(READ_COILS, MB_ADDR_ERROR);
		return;
	}

	tx_buf[ADR_POS] = MyAddress;
	tx_buf[FUNC_POS] = READ_COILS;
	tx_buf[CNT_POS] = 1 + cnt/8;

	tx_buf[DATA_POS] = 0;
	for(uint16_t i = 0, shift = 0, offset = 0; i < cnt; i++, shift++){
		if(shift == 8){
			shift = 0;
			offset++;
			tx_buf[DATA_POS+ offset] = 0;
		}
		tx_buf[DATA_POS + offset] |= (Coils[adrInArray + i].value << shift);
	}
	crc = CRC16(tx_buf, 3+ (1+cnt/8));

	tx_buf[DATA_POS+(1+cnt/8)] = crc>>8;
	tx_buf[DATA_POS+1+(1+cnt/8)] = crc&0xFF;
	SET_TX_DIR();
	HAL_UART_Transmit_IT(&huart3, tx_buf, 5+(1+cnt/8));
}

static void WriteCoils(uint16_t address, uint16_t data)
{
	uint16_t crc;
	int adrInArray = isCorrectAddress(WRITE_COIL, address, 1);

	if(adrInArray < 0)
	{
		MB_SendErrorMsg(WRITE_COIL, MB_ADDR_ERROR);
		return;
	}

	if(data){
		Coils[adrInArray].value = 1;
	}
	else{
		Coils[adrInArray].value = 0;
	}

	memcpy(tx_buf, rx_buf, 8); //Если все ок, то копируем ответ
	tx_buf[0] = MyAddress;
	tx_buf[1] = WRITE_COIL;
	tx_buf[2] = address >> 8;
	tx_buf[3] = address & 0xFF;
	tx_buf[4] = data >> 8;
	tx_buf[5] = data & 0xFF;
	crc = CRC16(tx_buf, 6);
	tx_buf[6] = crc >> 8;
	tx_buf[7] = crc & 0xFF;
	SET_TX_DIR();
	HAL_UART_Transmit_IT(&huart3, tx_buf, 8);
	ExecuteMB();

}

static void RecMsgProc(void)
{
	if( rx_buf[0] != MyAddress || !CheckCrc() )
		return;

	rx_ptr = 0;


	switch( rx_buf[1] )
	{
	case READ_INPUTS:
		SendInputs(EXTRACT_ADDRESS(rx_buf), EXTRACT_CNT(rx_buf));
		break;

	case READ_DISCRETE:
		SendDiscrete(EXTRACT_ADDRESS(rx_buf), EXTRACT_CNT(rx_buf));
		break;

	case READ_COILS:
		SendCoils(EXTRACT_ADDRESS(rx_buf), EXTRACT_CNT(rx_buf));
		break;
	case WRITE_COIL:
		WriteCoils(EXTRACT_ADDRESS(rx_buf), EXTRACT_CNT(rx_buf));
		break;
	case WRITE_HOLDING:
	case READ_HOLDING:

	default:
		MB_SendErrorMsg(rx_buf[1], MB_FUNC_ERROR);
		break;
	}
}


uint8_t ModBusSetAddress(uint8_t address)
{
	if(address > 0 && address < 248)
	{
		MyAddress = address;
		return 1;
	}
	else
		return 0;
}

uint8_t ModBusSetSpeed(uint32_t speed){
	uint32_t pclk = HAL_RCC_GetPCLK1Freq();
	huart3.Instance->BRR = UART_BRR_SAMPLING16(pclk, speed);
	SetTimer((35 * 1000000) / speed);
	return 1;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART3)
	{
		SET_RX_DIR();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART3)
	{
		UpdateTimer();

		if(BusState == BUS_BUSY || ( rx_ptr == 0  && temp_rx[0] != MyAddress)) //Если не наше сообщение, то нечего его пихать в буфер
		{
			BusState = BUS_BUSY;
			return;
		}
		else
		{
			BusState = REC_MY_MSG;
		}

		rx_buf[rx_ptr++] = temp_rx[0];

		if(rx_ptr == sizeof(rx_buf))
			rx_ptr = 0;
	}

}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART3)
	{
		USART3->DR;
		USART3->SR;
		HAL_UART_Receive_DMA(&huart3, temp_rx, sizeof(temp_rx));
	}
}
void TIM6_DAC_IRQHandler(void)
{
	__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);

	if(  BusState == REC_MY_MSG )
	{

	}
	BusState = BUS_FREE;

}

uint32_t MB_GetSettings(uint8_t adr){

}

uint32_t MB_SetSettings(uint8_t adr, uint16_t U, uint16_t F){

}

uint32_t MB_SendCommand(uint8_t adr, Command_t cmd){

}

void modbusTaskBody(void)
{
	ModBusInit();

}


