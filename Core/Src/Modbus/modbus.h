#ifndef _MODBUS_H
#define _MODBUS_H

#include "main.h"

#define SET_TX_DIR() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET)
#define SET_RX_DIR() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET)



#define INPUT_REGS_CNT	20

#define MB_MSG_CPLT_SIGNAL 1<<1

#define SWAP_BYTE(X)  (X<<8 | X>>8)

#define EXTRACT_ADDRESS(buf)	(buf[2] << 8 | buf[3] )
#define EXTRACT_CNT(buf)	( buf[4] << 8 | buf[5] )
#define EXTRACT_SINGLE_DATA(buf)	( buf[6] << 8 | buf[7] )

//Состояние шины приема
typedef enum
{
	BUS_BUSY = 0,
	REC_MY_MSG,
	BUS_FREE
}BusState_t;

//Формат ответного пакета Адрес+Функция+Кол-во_данных+Данныу+CRC
enum
{
	ADR_POS = 0,
	FUNC_POS,
	CNT_POS,
	DATA_POS
};

//Отправляемые ошибки
typedef enum
{
	MB_FUNC_ERROR = 1,
	MB_ADDR_ERROR,
	MB_VALUE_ERROR
}Errors_t;

//Поддерживаемые функции
typedef enum
{
	READ_COILS = 1,
	READ_DISCRETE,
	READ_HOLDING,
	READ_INPUTS,

	WRITE_COIL = 5,
	WRITE_HOLDING,
}MB_Funcs_t;


typedef struct{
	const uint16_t address;
	uint16_t value;
}Register_t;

typedef struct{
	const uint16_t address;
	uint8_t value : 1;
	void (*handler)(void);
}Bit_t;


extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart3;
extern uint16_t CRC16(uint8_t* bytes, int len);



//Из карты связи
extern Register_t InputRegisters[];
extern Bit_t DiscreteInputs[];
extern Bit_t Coils[];

extern const uint16_t InputRegsSize;
extern const uint16_t DiscreteInputsSize;
extern const uint16_t CoilsSize;
uint8_t ModBusSetAddress(uint8_t address);
uint8_t ModBusSetSpeed(uint32_t speed);
uint8_t ModBusSetSpeed(uint32_t speed);
void ModBusInit(void);
uint32_t MB_GetSettings(uint8_t adr);
uint32_t MB_SetSettings(uint8_t adr, uint16_t U, uint16_t F);
uint32_t MB_SendCommand(uint8_t adr, Command_t cmd);
#endif
