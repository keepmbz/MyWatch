#include "stm32f10x.h"
#include "MyFlash.h"

void Get_InitTime(MyTime_t *my_time){
    *((__IO uint32_t *)0x08008000);
}
void Save_Time(MyTime_t *my_time);
void Load_Time(MyTime_t *my_time);