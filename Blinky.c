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



#define MEM_ADDRESS		(*((volatile unsigned long *) 0x20000000))

/*----------------------------------------------------------------------------
 * Main
 *---------------------------------------------------------------------------*/ 
int i __attribute__((at(0x20000004)));
volatile int m = 0;


int foo(int i){
	int a;
 
	//a = m;
	i = a;

	return i;
}
 
 
int main (void) {
	MEM_ADDRESS = 5;
	
	MEM_ADDRESS++;
                         				   
	foo(i);

  for(;;);
}
