#ifndef _MENU_H_
#define _MENU_H_
#include "MyRtc.h"
typedef struct{
	uint8_t chance;
	MyTime_t tm;
}MenuMain_Config;

typedef struct{
	uint8_t chance;
	uint8_t Move_State;
}MenuMenu_Config;

typedef struct{
	uint8_t chance;
}MenuSettings_Config;

typedef struct{
	uint8_t chance;
	MyTime_t tm;
}MenuSetTime_Config;

typedef struct{
	uint8_t chance;
	uint8_t Light_State;
}MenuLight_Config;

typedef struct{
	uint8_t chance;
}MenuStopwatch_Config;

typedef struct{
	uint8_t chance;
}MenuGame_Config;

typedef struct{
	uint8_t chance;
}MenuTV_Config;

void MenuMain(MenuMain_Config* cfg);
void MenuMenu(MenuMenu_Config* cfg);
void MenuSettings(MenuSettings_Config* cfg);
void MenuSetTime(MenuSetTime_Config* cfg);
void MenuLight(MenuLight_Config *cfg);
void MenuStopwatch(MenuStopwatch_Config *cfg);
void MenuGame(MenuGame_Config *cfg);
void MenuTV(MenuTV_Config *cfg);

#endif
