#ifndef _MYFLASH_H_
#define _MYFLASH_H_

#include "stm32f10x.h"
#include "MyRTC.h"

time_t Get_InitTime_cnt() ;
void Save_Time(MyTime_t *my_time);
void Load_Time(MyTime_t *my_time);
#endif