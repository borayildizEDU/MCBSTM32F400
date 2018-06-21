#include "led.h"


int ToggleLed(int num){
	static int state[8] = {0};
	
	if(!state[num]){
		if(LED_On(num) != -1) state[num] = 1;
	}
	else{
		if(LED_Off(num) != -1) state[num] = 0;
	}
	
	return state[num];	
}
