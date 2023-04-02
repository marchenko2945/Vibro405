//Основные параметры нашей системы
extern float Current_X_Speed;
extern float Current_Y_Speed;
extern float X_Speed;
extern float Y_Speed;
extern short adr[3];

typedef enum{
	NONE = 0,
	START_CMD,
	STOP_CMD,
	GET_SETTINGS_CMD,
	SET_SETTINGS_CMD
}Command_t;
