#include "stm32f10x.h"                  // Device header
#include "menu.h"
#include "OLED.h"
#include "set_light.h"

void MenuMain(MenuMain_Config* cfg){
	OLED_Printf(0,0,OLED_6X8,"%d-%d-%d",cfg->tm.year,cfg->tm.month,cfg->tm.day);
		OLED_Printf(16,16,OLED_12X24,"%02d-%02d-%02d",cfg->tm.hour,cfg->tm.minute,cfg->tm.second);
		OLED_ShowString(0,48,"菜单",OLED_8X16);
		OLED_ShowString(96,48,"设置",OLED_8X16);
		if(cfg->chance ==0)
			OLED_ReverseArea(0,48,32,16);
		else
			OLED_ReverseArea(96,48,32,16);
}

void MenuMenu(MenuMenu_Config* cfg){
    static uint16_t tp[5] = {48, 96, 144, 192, 240};
    static uint8_t old_target = 0;

	if(old_target == 4 && cfg->chance == 0){
		OLED_Clear();
		for(int i = 0;i<5;i++)
			tp[i] += 48*4;
	}
    if (tp[cfg->chance] == 48) {
        old_target = cfg->chance;
        cfg->Move_State = 0;
    }

    if (cfg->chance > old_target) {
        for (int i = 0; i < 5; i++)
            tp[i] -= 4;
        cfg->Move_State = 1;
    }
    else if (cfg->chance < old_target) {
        for (int i = 0; i < 5; i++)
            tp[i] += 4;
        cfg->Move_State = 1;
    }

    if (cfg->Move_State)
        OLED_Clear();
    OLED_ShowImage(46, 14, 36, 36, Menu_Selection);
    OLED_ShowImage(tp[0], 16, 32, 32, Menu_draw[1]);
    OLED_ShowImage(tp[1], 16, 32, 32, Menu_draw[2]);
    OLED_ShowImage(tp[2], 16, 32, 32, Menu_draw[3]);
    OLED_ShowImage(tp[3], 16, 32, 32, Menu_draw[4]);
    OLED_ShowImage(tp[4], 16, 32, 32, Menu_draw[5]);
}

void MenuSettings(MenuSettings_Config* cfg){
	OLED_ShowImage(0,0,16,16,Return);
	OLED_ShowString(0,16,"时间日期设置",OLED_8X16);

	switch(cfg->chance){
		case 0:
			OLED_ReverseArea(0,0,16,16);
			break;
		case 1:
			OLED_ReverseArea(0,16,96,16);
			break;
	
	}
}

void MenuSetTime(MenuSetTime_Config* cfg){
	static uint8_t tp_flag = 0;
	if(cfg->chance <4){
		if(tp_flag)OLED_Clear();
		tp_flag = 0;
		OLED_ShowImage(0,0,16,16,Return);
		OLED_ShowString(0,16,"年:",OLED_8X16);
		OLED_Printf(32,16,OLED_8X16,"%04d",cfg->tm.year);
		OLED_ShowString(0,32,"月:",OLED_8X16);
		OLED_Printf(32,32,OLED_8X16,"%02d",cfg->tm.month);
		OLED_ShowString(0,48,"日:",OLED_8X16);
		OLED_Printf(32,48,OLED_8X16,"%02d",cfg->tm.day);
		OLED_ReverseArea(0,16*cfg->chance,16,16);
	}
	else{
		if(tp_flag ==0)OLED_Clear();
		tp_flag = 1;
		OLED_ShowString(0,0,"时:",OLED_8X16);
		OLED_Printf(32,0,OLED_8X16,"%02d",cfg->tm.hour);
		OLED_ShowString(0,16,"分:",OLED_8X16);
		OLED_Printf(32,16,OLED_8X16,"%02d",cfg->tm.minute);
		OLED_ShowString(0,32,"秒:",OLED_8X16);
		OLED_Printf(32,32,OLED_8X16,"%02d",cfg->tm.second);
		OLED_ReverseArea(0,16*(cfg->chance-4),16,16);
	}
}

void MenuLight(MenuLight_Config *cfg){
	Set_Light(cfg->Light_State);
	OLED_Clear();
    OLED_ShowImage(0, 0, 16, 16, Return);
    OLED_ShowString(5, 20,"OFF", OLED_12X24);
    OLED_ShowString(85, 20,"ON", OLED_12X24);
	if(cfg->chance == 0)
		OLED_ReverseArea(0,0,16,16);
	else if (cfg->chance == 1)	
		OLED_ReverseArea(5,20,36,24);
	else 
		OLED_ReverseArea(85,20,24,24);
}

void MenuStopwatch(MenuStopwatch_Config *cfg){
}

void MenuGame(MenuGame_Config *cfg){
}

void MenuTV(MenuTV_Config *cfg){
}