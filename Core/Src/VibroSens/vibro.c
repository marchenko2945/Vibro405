#include "vibro.h"
#include "math.h"
static uint16_t adc_data[3][128] = {0};

void InitVibro(void){
	//Тут стартуем ацп по трем каналам
	HAL_ADC_Start_DMA(&hadc1, adc_data, sizeof(adc_data));
	HAL_TIM_Base_Start(&htim3);
}

static void CalcXFreq(void){

	float tempFreq1 = 0, tempFreq2= 0;
	for(uint8_t i = 0; i < 128; i++){
		tempFreq1+=adc_data[0][i];
	}

	for(uint8_t i = 0; i < 128; i++){
		tempFreq2+=adc_data[1][i];
	}

	tempFreq1 = sqrt(tempFreq1/128);
	tempFreq2 = sqrt(tempFreq2/128);

	Current_X_Speed = (tempFreq1 - tempFreq2) * CALIB_KOEF_X;
}

static void CalcYFreq(void){
	float tempFreq1 = 0;
	for(uint8_t i = 0; i < 128; i++){
		tempFreq1+=adc_data[0][i];
	}
	tempFreq1 = sqrt(tempFreq1/128);

	Current_X_Speed = (tempFreq1) * CALIB_KOEF_Y;
}

static void PrepareAdcData(void){
	HAL_TIM_Base_Stop(&htim3);

	for(uint8_t i = 0; i < 3; i++){
		for(uint8_t k = 0; k < 128; k++)
			adc_data[i][k] *= PREP_KOEF;
	}

	HAL_TIM_Base_Start(&htim3);
}

void VibroProc(void){
	static uint32_t delayTime = 0;

	if(HAL_GetTick() - delayTime > 100){
		delayTime = HAL_GetTick();
		CalcXFreq();
		CalcYFreq();
	}
}
