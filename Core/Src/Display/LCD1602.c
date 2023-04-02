#include "main.h"

#include "display.h"

#ifdef LCD1602
#define FONT12X16_WIDTH  20
#define FONT12X16_HEIGHT 4

#define     LCD_OUT                GPIOB->ODR
#define     LCD_PIN_RS             GPIO_PIN_8          // PB0
#define     LCD_PIN_EN             GPIO_PIN_7          // PB1
#define     LCD_PIN_D7             GPIO_PIN_3          // PB7
#define     LCD_PIN_D6             GPIO_PIN_4          // PB6
#define     LCD_PIN_D5             GPIO_PIN_5          // PB5
#define     LCD_PIN_D4             GPIO_PIN_6          // PB4
#define     LCD_PIN_MASK  ((LCD_PIN_RS | LCD_PIN_EN | LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4))

#define HIGH_NIBBLE(x) (x >> 4)
#define LOW_NIBBLE(x)  (x & 0x0F)




static void delay(int a);
static void PulseLCD();
static void SendByte(char ByteToSend, int IsData);
static void Cursor(uint8_t Row, uint8_t Col);
static void ClearLCDScreen();



static uint8_t dataForPort[] = {0x0,0x8,0x4,0xc,0x2,0xa,0x6,0xe,0x1,0x9,0x5,0xD,0x4,0xb,0x7,0xf};

int lcdTransCommand()
{
	return 0;
}

int LCD1602_Init()
{
	LCD_OUT &= ~(LCD_PIN_MASK);  // 0 на дата пинах
	HAL_Delay(2);

	LCD_OUT = 0x20; //задали 2 линии дисплея, интерфейс - 4бита
	PulseLCD();		//запулили команду
	SendByte(0x28, 0);

	SendByte(0x0C, 0); //врубили дисплей, крусор нахер

	//ClearLCDScreen();
	return 0;
}


void LCD1602_putc(int x, int y, char ch)
{
	// для цикличности
	y %= FONT12X16_HEIGHT;
	x %= FONT12X16_WIDTH;

	Cursor(x, y);
	SendByte(ch,1);

}

void LCD1602_cls()
{
	ClearLCDScreen();
}

static void delay(int a)
{
	int i = 0;
	int f = 0;
	while(f < a)
	{
		while(i<5000)
		{i++;}
		f++;
	}
}

//---Нужная функция для работы с дисплеем, по сути "дергаем ножкой" EN---//
static void PulseLCD()
{
	LCD_OUT &= ~LCD_PIN_EN;
	delay(220);
	LCD_OUT |= LCD_PIN_EN;
	delay(220);
	LCD_OUT &= (~LCD_PIN_EN);
	delay(220);
}

//---Отсылка байта в дисплей---//
static void SendByte(char ByteToSend, int IsData)
{
	LCD_OUT &= (~LCD_PIN_MASK);
	LCD_OUT |= dataForPort[HIGH_NIBBLE(ByteToSend)]<<3;

	if (IsData == 1)
		LCD_OUT |= LCD_PIN_RS;
	else
		LCD_OUT &= ~LCD_PIN_RS;
	PulseLCD();
	LCD_OUT &= (~LCD_PIN_MASK);
	LCD_OUT |= dataForPort[LOW_NIBBLE(ByteToSend)] << 3;

	if (IsData == 1)
		LCD_OUT |= LCD_PIN_RS;
	else
		LCD_OUT &= ~LCD_PIN_RS;

	PulseLCD();
}

//---Установка позиции курсора---//
static void Cursor(uint8_t Row, uint8_t Col)
{
	char address;
	if (Row == 0)
		address = 0;
	else
		address = 0x40;
	address |= Col;
	SendByte(0x80 | address, 0);
}

//---Очистка дисплея---//
static void ClearLCDScreen()
{
	SendByte(0x01, 0);
	delay(220);
	SendByte(0x02, 0);
	delay(220);
}



void DisplayProc(void){
	char address;
	uint8_t Row,  Col;
	delay(220);
	if (Row == 0)
		address = 0;
	else
		address = 0x40;
	address |= Col;
	SendByte(0x80 | address, 0);
}


#endif
