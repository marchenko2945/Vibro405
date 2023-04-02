#ifndef VIBRO_H
#define VIBRO_H

#include "main.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;

#define CALIB_KOEF_X 1.0
#define CALIB_KOEF_Y 1.0
#define PREP_KOEF 1.0

void InitVibro(void);
void VibroProc(void);
#endif
