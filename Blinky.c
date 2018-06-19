/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher for MCBSTM32F400
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2015 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "RTE_Components.h"             // Component selection
#include "Config.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "led.h"




/*----------------------------------------------------------------------------
 * Task1
 *---------------------------------------------------------------------------*/ 
void task1(void const *argument){
	while(1){
		osDelay(1000);
		ToggleLed(1);
	}
}

/*----------------------------------------------------------------------------
 * Task2
 *---------------------------------------------------------------------------*/ 
void task2(void const *argument){
	while(1){
		osDelay(1000);
		ToggleLed(2);
	}
}

/*----------------------------------------------------------------------------
 * Task3
 *---------------------------------------------------------------------------*/ 
void task3(void const *argument){
	while(1){
		osDelay(1000);
		ToggleLed(3);
	}
}

/*----------------------------------------------------------------------------
 * Threads
 *---------------------------------------------------------------------------*/ 
osThreadId_t tid_app, tid_task1, tid_task2, tid_task3;
osThreadDef(task1, osPriorityNormal, 1, 0);
osThreadDef(task2, osPriorityNormal, 1, 0);
osThreadDef(task3, osPriorityNormal, 1, 0);


/*----------------------------------------------------------------------------
 * MainApplication Thread
 *---------------------------------------------------------------------------*/ 
void app_main(void const *argument){
	
	tid_task1 = osThreadCreate(osThread(task1), NULL);   
	tid_task2 = osThreadCreate(osThread(task2), NULL);  
	tid_task3 = osThreadCreate(osThread(task3), NULL);    
	
	while(1){
		osDelay(1000);
		ToggleLed(0);
	}
}

osThreadDef(app_main, osPriorityNormal, 1, 0);



/*----------------------------------------------------------------------------
 * Main
 *---------------------------------------------------------------------------*/ 
int main (void) {

  HAL_Init();                               				   
  SystemClock_Config(RCC_SYSCLKSOURCE_PLLCLK);     
	LED_Initialize();
	
	
	osKernelInitialize();                     				
	tid_app = osThreadCreate(osThread(app_main), NULL);         
  osKernelStart();                          			
  for(;;);
}
