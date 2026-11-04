#include "stm32f10x.h"                  // Device header
#include "keys.h"

void Keys_Init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef gpio_initstruct;
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU;
	gpio_initstruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_5;
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_initstruct);
}


uint8_t Check_KeyNum(){
	uint8_t num=0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)
		num =1;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 0)
		num =2;
	return num;
}

void Get_KeyNum(Key_State* state){
	static uint8_t Key_Val,Key_Old;
	Key_Val = Check_KeyNum();
	state->key_down = Key_Val&(Key_Val^Key_Old);
	state->key_up = ~Key_Val&(Key_Val^Key_Old);
	Key_Old = Key_Val;
}