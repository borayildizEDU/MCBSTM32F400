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
#include "EventRecorder.h"
#include "Config.h"
#include "Common.h"
#include "Test.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX





/*----------------------------------------------------------------------------
 * Main
 *---------------------------------------------------------------------------*/ 
 void app_main (void const *argument) {

	/* Run Test */
	//Test_ThreadSwitch();

  for(;;);
}
 
osThreadDef(app_main, osPriorityNormal, 1, 0);
 
int main (void) {

  // System Initialization
  HAL_Init();                               				// Initialize the HAL Library     
  SystemClock_Config(RCC_SYSCLKSOURCE_PLLCLK);      // Configure the System Clock  
  osKernelInitialize();                     				// Initialize CMSIS-RTOS  
  osThreadCreate(osThread(app_main), NULL);         // Create main thread
  osKernelStart();                          				// Start thread execution         
	EventRecorderInitialize(EventRecordAll, 1);				// Initialize EventRecorder

  for(;;);
}
