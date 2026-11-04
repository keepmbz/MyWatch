#ifndef _KEYS_H_
#define _KEYS_H_


typedef struct{
	uint8_t key_up;
	uint8_t key_down;
}Key_State;


void Keys_Init(void);
void Get_KeyNum(Key_State* state);

#endif
