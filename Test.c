#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "RTE_Components.h"             // Component selection
#include "EventRecorder.h"
#include "Common.h"
#include "Config.h"
#include "Test.h"
#include "Threads.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include <string.h>


/*----------------------------------------------------------------------------
 * Globals
 *---------------------------------------------------------------------------*/
volatile unsigned int* pMem = (unsigned int *) 0x20000120;


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


void Test_MemoryWindow(){
  int i;
  unsigned int val = 0;
  
  for(;;){
    for(i = 0; i < MAX_MEM_SIZE / 4; i++){
      *(pMem + i) = val;
    }
    osDelay (1000);
    val++;
  }
}


