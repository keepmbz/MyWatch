#ifndef __MYRTC_H__
#define __MYRTC_H__
#include "stm32f10x.h"
#include "time.h"
typedef struct {
    uint16_t year;
    uint16_t month;
    uint16_t day;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
    time_t time_cnt;
} MyTime_t;

void MyRtc_Init(void);
void MyRtc_SetTime(MyTime_t *my_time);
void MyRtc_SwapTime(void);
void MyRtc_GetTime(MyTime_t *my_time);

#endif
