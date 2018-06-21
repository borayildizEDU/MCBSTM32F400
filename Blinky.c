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
#include "EventRecorder.h"
#include "Driver_USART.h"

/* Thread ids */
osThreadId_t tid_app, tid_task1, tid_task2, tid_task3;


/* USART Driver */
extern ARM_DRIVER_USART Driver_USART1;

/*----------------------------------------------------------------------------
 * Task1: USART THREAD
 *---------------------------------------------------------------------------*/ 
void myUSART_callback(uint32_t event){
  uint32_t mask;
  mask = ARM_USART_EVENT_RECEIVE_COMPLETE  |
         ARM_USART_EVENT_TRANSFER_COMPLETE |
         ARM_USART_EVENT_SEND_COMPLETE     |
         ARM_USART_EVENT_TX_COMPLETE       ;
  if (event & mask) {
    /* Success: Wakeup Thread */
    osSignalSet(tid_task1, 0x01);
  }
  if (event & ARM_USART_EVENT_RX_TIMEOUT) {
    __breakpoint(0);  /* Error: Call debugger or replace with custom error handling */
  }
  if (event & (ARM_USART_EVENT_RX_OVERFLOW | ARM_USART_EVENT_TX_UNDERFLOW)) {
    __breakpoint(0);  /* Error: Call debugger or replace with custom error handling */
  }
}



void task1(void const *argument){
	static ARM_DRIVER_USART * pUART = &Driver_USART1;
	ARM_DRIVER_VERSION     version;
	ARM_USART_CAPABILITIES drv_capabilities;
	char                   cmd;
 
#ifdef DEBUG
	version = USARTdrv->GetVersion();
	if (version.api < 0x200)   /* requires at minimum API version 2.00 or higher */
	{                          /* error handling */
			return;
	}
	drv_capabilities = USARTdrv->GetCapabilities();
	if (drv_capabilities.event_tx_complete == 0)
	{                          /* error handling */
			return;
	}
#endif
 
	/*Initialize the USART driver */
	pUART->Initialize(myUSART_callback);
	/*Power up the USART peripheral */
	pUART->PowerControl(ARM_POWER_FULL);
	/*Configure the USART to 4800 Bits/sec */
	pUART->Control(ARM_USART_MODE_ASYNCHRONOUS |
										ARM_USART_DATA_BITS_8 |
										ARM_USART_PARITY_NONE |
										ARM_USART_STOP_BITS_1 |
										ARM_USART_FLOW_CONTROL_NONE, 4800);
	 
	/* Enable Receiver and Transmitter lines */
	pUART->Control (ARM_USART_CONTROL_TX, 1);
	pUART->Control (ARM_USART_CONTROL_RX, 1);

	pUART->Send("\nPress Enter to receive a message", 34);
	osSignalWait(0x01, osWaitForever);
     
	while (1)
	{
		pUART->Receive(&cmd, 1);          /* Get byte from UART */
		osSignalWait(0x01, osWaitForever);
		if (cmd == 13)                       /* CR, send greeting  */
		{
			pUART->Send("\nHello World!", 12);
			osSignalWait(0x01, osWaitForever);
		}
		
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
osThreadDef(task1, osPriorityNormal, 1, 0);
osThreadDef(task2, osPriorityNormal, 1, 0);
osThreadDef(task3, osPriorityNormal, 1, 0);


/*----------------------------------------------------------------------------
 * MainApplication Thread
 *---------------------------------------------------------------------------*/ 
void app_main(void const *argument){
	int i = 0;
	
	tid_task1 = osThreadCreate(osThread(task1), NULL);   
	tid_task2 = osThreadCreate(osThread(task2), NULL);  
	tid_task3 = osThreadCreate(osThread(task3), NULL);    
	
	while(1){
		osDelay(1000);
		ToggleLed(0);
		EventRecord2(0x0001, i, i); 
		i++;
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
	EventRecorderInitialize (EventRecordAll, 1); 
	
	
	osKernelInitialize();                     				
	tid_app = osThreadCreate(osThread(app_main), NULL);         
  osKernelStart();                          			
  for(;;);
}
