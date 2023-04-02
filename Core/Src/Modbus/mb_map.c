#include "modbus.h"

/*
 * АДРЕСАЦИЯ ДОЛЖНА БЫТЬ ПО ПОРЯДКУ!!!!
 *
 * ADDRESSING MUST BE IN ORDER !!!!!!
 *
 */

Register_t InputRegisters[] = {

		{
				.address = 0,
				.value = SWAP_BYTE(10),
		},
		{
				.address = 1,
				.value = SWAP_BYTE(20),
		},
		{
				.address = 2,
				.value = SWAP_BYTE(30),
		},
		{
				.address = 3,
				.value = SWAP_BYTE(40),
		},
		{
				.address = 4,
				.value = SWAP_BYTE(50),
		},
		{
				.address = 5,
				.value = SWAP_BYTE(60),
		},
		{
				.address = 6,
				.value = SWAP_BYTE(70),
		},
		{
				.address = 7,
				.value = SWAP_BYTE(80),
		},
		{
				.address = 8,
				.value = SWAP_BYTE(90),
		},
		{
				.address = 9,
				.value = SWAP_BYTE(100),
		},
		{
				.address = 15,
				.value = SWAP_BYTE(110),
		},
		{
				.address = 16,
				.value = SWAP_BYTE(120),
		},
		{
				.address = 17,
				.value = SWAP_BYTE(130),
		},
		{
				.address = 55,
				.value = SWAP_BYTE(140),
		},
		{
				.address = 66,
				.value = SWAP_BYTE(150),
		},
		{
				.address = 0x2024,
				.value = SWAP_BYTE(160),
		},
};

Bit_t DiscreteInputs[] = {
		{
				.address = 0,
				.value  = 1,
		},
		{
				.address = 1,
				.value  = 0,
		},
		{
				.address = 2,
				.value  = 1,
		},
		{
				.address = 3,
				.value  = 1,
		}
};


static void SendCharge(void){

}

static void SendOn(void){

}

static void SendOff(void){

}

Bit_t Coils[] = {


};

void UpdateMB_MapData(MB_Funcs_t func){ //обновляет полезные данные в карте связи

	if(func == READ_INPUTS){

	}
}

void ExecuteMB(void){
	for(uint8_t i = 0; i < CoilsSize; i++){
		if(Coils[i].value){
			Coils[i].value = 0;

			if(Coils[i].handler)
				Coils[i].handler();
		}
	}
}


const uint16_t InputRegsSize = sizeof(InputRegisters) / sizeof(Register_t);
const uint16_t DiscreteInputsSize = sizeof(DiscreteInputs) / sizeof(Bit_t);
const uint16_t CoilsSize = sizeof(Coils) / sizeof(Bit_t);

