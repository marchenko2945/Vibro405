
#ifndef DRIVERS_DRIVERS_H_
#define DRIVERS_DRIVERS_H_

#include "main.h"

#define LCD1602

#ifdef MT12864A

int MT12864A_Init();
void MT12864A_cls();
void MT12864A_putc(int x, int y, char ch);

#endif

#ifdef LCD1602

int LCD1602_Init();
void LCD1602_cls();
void LCD1602_putc(int x, int y, char ch);
void DisplayProc(void);
#endif

#ifdef OPTI_TERM_LCD

int termInit();
void termCls();
void termPutc(int x, int y, char ch);
void rxCmdByte(UART_HandleTypeDef *huart);

#endif

#endif /* DRIVERS_DRIVERS_H_ */
