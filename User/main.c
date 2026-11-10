#include "Delay.h"
#include "MyRTC.h"
#include "MyTim.h"
#include "OLED.h"
#include "keys.h"
#include "menu.h"
#include "stm32f10x.h" // Device header
#include "set_light.h"


/**
 * 坐标定义：
 * 左上角为(0, 0)
 * 横坐标为X轴，取值范围为0~127
 * 纵坐标为Y轴，取值范围为0~63
 *
 *       0             X轴           127
 *      .------------------------------->
 *    0 |
 *      |
 *      |
 *      |
 *  Y轴 |
 *      |
 *      |
 *      |
 *   63 |
 *      v
 *
 */

typedef enum
{
    MENU_MAIN = 1,
    MENU_MENU,
    MENU_SETTINGS,
    MENU_SET_TIME,
    MENU_LIGHT,
    MENU_STOPWATCH,
    MENU_GAME,
    MENU_TV,
} menu_id_t;

uint8_t menus_cnt = MENU_MAIN;
MyTime_t tm;
uint8_t keys_cnt, task_cnt;

//菜单栈
menu_id_t menus_stack[3];
uint8_t menus_stack_top = 0;
void push_menu(menu_id_t menu_id){
    menus_stack[menus_stack_top++] = menu_id;
}
void pop_menu(menu_id_t *menu_id)
{
    menus_cnt = menus_stack[--menus_stack_top];
}

// 菜单0
MenuMain_Config m1_cfg = {0};

// 菜单1
MenuMenu_Config m2_cfg = {0};

// 菜单2
MenuSettings_Config m3_cfg = {0};

// 菜单3
MenuSetTime_Config m4_cfg = {0};

//手电筒
MenuLight_Config m5_cfg = {0};

//秒表
MenuStopwatch_Config m6_cfg = {0};

//游戏
MenuGame_Config m7_cfg = {0};

//小电视
MenuTV_Config m8_cfg = {0};

void keys_get(void);
void task_run(void);

int main(void)
{
    Oled_Power_Init();
    OLED_Init();
    OLED_Clear();
    myTIM_Init();
    Light_Init();

    MyRtc_Init();
    Keys_Init();

    while (1)
    {

        keys_get();
        task_run();
    }
}

void keys_get()
{
    if (keys_cnt != 0)
        return;
    keys_cnt = 1;
    static Key_State keyState;
    Get_KeyNum(&keyState);

    if (keyState.key_up == 1)
    {
        switch (menus_cnt)
        {
        case MENU_MAIN:
            if (m1_cfg.chance == 0)
                m1_cfg.chance = 1;
            else
                m1_cfg.chance = 0;
            break;
        case MENU_MENU:
            if (m2_cfg.Move_State == 0 && ++m2_cfg.chance == 5)
                m2_cfg.chance = 0;
            break;
        case MENU_SETTINGS:
            if(++m3_cfg.chance == 2) m3_cfg.chance = 0;
            break;
        case MENU_SET_TIME:
            if(++m4_cfg.chance == 7) m4_cfg.chance = 0;
            break;
        case MENU_LIGHT:
            if(++m5_cfg.chance == 3) m5_cfg.chance = 0;
            break;
        }
    }

    if (keyState.key_up == 2)
    {
        switch (menus_cnt)
        {
        case MENU_MAIN:
            OLED_Clear();
            push_menu(menus_cnt);
            if (m1_cfg.chance == 0)
            {
                menus_cnt = MENU_MENU;
            }
            else
            {
                menus_cnt = MENU_SETTINGS;
            }
            break;

        case MENU_MENU:
            OLED_Clear();
            switch(m2_cfg.chance){
                case 0:
                    pop_menu(&menus_cnt);
                    break;
                case 1:
                    push_menu(menus_cnt);
                    menus_cnt = MENU_LIGHT;
                    break;
                // case 2:
                //     push_menu(menus_cnt);
                //     menus_cnt = MENU_STOPWATCH;
                //     break;
                // case 3:
                //     push_menu(menus_cnt);
                //     menus_cnt = MENU_GAME;
                //     break;
                // case 4:
                //     push_menu(menus_cnt);
                //     menus_cnt = MENU_TV;
                //     break;
            }
            break;
        case MENU_SETTINGS:
            OLED_Clear();
            if(m3_cfg.chance == 0){
                pop_menu(&menus_cnt);
            }
            else{
                m4_cfg.tm = tm;
                push_menu(menus_cnt);
                menus_cnt = MENU_SET_TIME;
            }
            break;
        case MENU_SET_TIME:
            switch (m4_cfg.chance)
            {
            case 0:
                OLED_Clear();
                MyRtc_SetTime(&m4_cfg.tm);
                pop_menu(&menus_cnt);
                break;
            case 1:
                if(++m4_cfg.tm.year ==2051) m4_cfg.tm.year=2026;
                break;
            case 2:
                if(++m4_cfg.tm.month ==13) m4_cfg.tm.month=1;
                break;
            case 3:
                if(++m4_cfg.tm.day ==32) m4_cfg.tm.day=1;
                break;
            case 4:
                if(++m4_cfg.tm.hour ==24) m4_cfg.tm.hour=0;
                break;
            case 5:
                if(++m4_cfg.tm.minute ==60) m4_cfg.tm.minute=0;
                break;
            case 6:
                if(++m4_cfg.tm.second ==60) m4_cfg.tm.second=0;
                break;
            }
            break;
        case MENU_LIGHT:
            if(m5_cfg.chance == 0){
                OLED_Clear();
                pop_menu(&menus_cnt);
            }
            else if(m5_cfg.chance == 1)
                m5_cfg.Light_State = 0;
            
            else if(m5_cfg.chance == 2)
                m5_cfg.Light_State = 1;
            break;
        }
    }
}

void task_run()
{
    if (task_cnt != 0)
        return;
    task_cnt = 1;

    MyRtc_SwapTime();
    MyRtc_GetTime(&tm);

    switch (menus_cnt)
    {
    case MENU_MAIN:
        m1_cfg.tm = tm;
        MenuMain(&m1_cfg);
        break;
    case MENU_MENU:
        MenuMenu(&m2_cfg);
        break;
    case MENU_SETTINGS:
        MenuSettings(&m3_cfg);
        break;
    case MENU_SET_TIME:
        MenuSetTime(&m4_cfg);
        break;
    case MENU_LIGHT:
        MenuLight(&m5_cfg);
        break;
    }
    OLED_Update();
}

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        if (++keys_cnt == 15)
            keys_cnt = 0;
        if (++task_cnt == 10)
            task_cnt = 0;
    }
}
