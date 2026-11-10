#include "stm32f10x.h"
#include "MyFlash.h"

time_t Get_InitTime_cnt(){
    *((__IO uint32_t *)0x08008000) = 0x0000497f;
     return *((__IO uint32_t *)0x08008000);
}
void Save_Time(MyTime_t *my_time){

}
void Load_Time(MyTime_t *my_time);