#include "MyRtc.h"
#include "stm32f10x.h" // Device header
#include "time.h"

uint16_t tim_inner[] = {2026, 10, 26, 20, 58, 30};

void MyRtc_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);

    PWR_BackupAccessCmd(ENABLE);

    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET)
        ;

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);

    RTC_WaitForSynchro();
    RTC_WaitForLastTask();

    RTC_SetPrescaler(32768 - 1);
    RTC_WaitForLastTask();


    time_t time_cnt;
    struct tm tim = {0};
    tim.tm_year = tim_inner[0] - 1900;
    tim.tm_mon = tim_inner[1] - 1;
    tim.tm_mday = tim_inner[2];
    tim.tm_hour = tim_inner[3];
    tim.tm_min = tim_inner[4];
    tim.tm_sec = tim_inner[5];
    time_cnt = mktime(&tim);
    RTC_SetCounter(time_cnt);
}

void MyRtc_SetTime( MyTime_t *my_time)
{
    time_t time_cnt;
    struct tm tim = {0};
    tim.tm_year = my_time->year - 1900;
    tim.tm_mon = my_time->month - 1;
    tim.tm_mday = my_time->day;
    tim.tm_hour = my_time->hour;
    tim.tm_min = my_time->minute;
    tim.tm_sec = my_time->second;
    time_cnt = mktime(&tim);
    RTC_SetCounter(time_cnt);
}



void MyRtc_SwapTime()
{
    time_t time_cnt = RTC_GetCounter();
    struct tm tim = *localtime(&time_cnt);
    tim_inner[0] = tim.tm_year + 1900;
    tim_inner[1] = tim.tm_mon + 1;
    tim_inner[2] = tim.tm_mday;
    tim_inner[3] = tim.tm_hour;
    tim_inner[4] = tim.tm_min;
    tim_inner[5] = tim.tm_sec;
}

void MyRtc_GetTime(MyTime_t *my_time)
{
    my_time->year = tim_inner[0];
    my_time->month = tim_inner[1];
    my_time->day = tim_inner[2];
    my_time->hour = tim_inner[3];z
    my_time->minute = tim_inner[4];
    my_time->second = tim_inner[5];
}
