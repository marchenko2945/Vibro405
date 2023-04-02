#include "movecontrol.h"
#include "../Modbus/modbus.h"

static float CalculateNewU(){
	return 400;
}

static float CalculateNewFreq(){
	return 50;
}


static void StartMotor(uint8_t ch, float U, float Freq){
	MB_SetSettings(adr[ch], U, Freq);
	MB_SendCommand(adr[ch], SET_SETTINGS_CMD);
	MB_SendCommand(adr[ch], START_CMD);
}

static void StopMotor(uint8_t ch){
	MB_SendCommand(adr[ch], STOP_CMD);
}

static void CorrectSettings(uint8_t ch){
	float U = CalculateNewU();
	float Freq = CalculateNewFreq();
	MB_SetSettings(adr[ch], U, Freq);
	MB_SendCommand(adr[ch], SET_SETTINGS_CMD);
}

static uint8_t isProcRun(void){
	return 1;
}

void InitMotors(void){
	MB_SendCommand(adr[0], GET_SETTINGS_CMD);
	MB_SendCommand(adr[1], GET_SETTINGS_CMD);
	MB_SendCommand(adr[2], GET_SETTINGS_CMD);
}


void MotorsControlProc(void){
	if(isProcRun()){

		if(abs(Current_X_Speed - X_Speed) > MAX_DIF_X){
			CorrectSettings(0);
			CorrectSettings(1);
		}
		if(abs(Current_Y_Speed - Y_Speed) > MAX_DIF_Y){
			CorrectSettings(3);
		}

	}
}
