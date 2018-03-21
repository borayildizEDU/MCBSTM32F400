#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "RTE_Components.h"             // Component selection
#include "EventRecorder.h"
#include "Common.h"
#include "Config.h"
#include "Test.h"
#include "Threads.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX


/*----------------------------------------------------------------------------
 * System Analyzer Tests
 *---------------------------------------------------------------------------*/
void Test_NOP(){
	while(1){

	}
}


void Test_SystemClock(){	
	int count = 5;
	int preDelay = 5000;
	int postDelay = 5000;
	int delay = 1000;
	
	osDelay (preDelay);
	
	while(count){
		osDelay (delay);
		SystemClock_Config(RCC_SYSCLKSOURCE_HSI);	
		osDelay (delay);
		SystemClock_Config(RCC_SYSCLKSOURCE_HSE);			
		osDelay (delay);
		SystemClock_Config(RCC_SYSCLKSOURCE_PLLCLK);		
		count--;
	}	
	
	osDelay (postDelay);
	
}

void Test_SleepMode(){
	int count = 5;
	int preDelay = 5000;
	int postDelay = 5000;
	int delay = 1000;
	
	osDelay (preDelay);

	while(count){
		HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFE);
		osDelay (delay);		
		count--;
	}
	
	osDelay (postDelay);
}


void Test_StopMode(){
	int count = 5;
	int preDelay = 5000;
	int postDelay = 5000;
	int delay = 1000;
	
	osDelay (preDelay);

	while(count){
		HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFE);
		osDelay (delay);		
		count--;
	}
	
	osDelay (postDelay);
}
	

void Test_StandbyMode(){
	int count = 5;
	int preDelay = 5000;
	int postDelay = 5000;
	int delay = 1000;
	
	osDelay (preDelay);

	while(count){
		HAL_PWR_EnterSTANDBYMode();
		osDelay (delay);		
		count--;
	}
	
	osDelay (postDelay);
}
	



/*
Circular thread switching
*/
void Test_ThreadSwitch(){
	Init_Threads();
}



void Test_PeripheralSwitch(){
	
}


void Test_EventRecorder(){
  char data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  
  while(1){
    EventRecordData(0x01, data, 8);
    HAL_Delay(1);   
  }

}


/*
return 1: BigEndian, 0: LittleEndian
*/
int Test_Endian(){
	uint32_t i = 1;
	uint8_t *c = (uint8_t*) &i;
	
	if(*c == 1){			// LittleEndian
		return 0;
	}
	else{							// Big Endian
		return 1;
	}
}



void Reverse(unsigned int* val){
	uint8_t *c = (uint8_t*)val;
	uint8_t temp = c[0];
	
	c[0] = c[3];
	c[3] = temp;
	
	temp = c[1];
	c[1] = c[2];
	c[2] = temp;
}




