#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "RTE_Components.h"             // Component selection
#include "EventRecorder.h"
#include "Common.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX



/*----------------------------------------------------------------------------
 *      Threads
 *---------------------------------------------------------------------------*/
#define THREAD_COUNT 4
osThreadId tid_Thread[THREAD_COUNT]; 


/*
Common thread function: circular thread switching
> wait for signal 
> write EventRecord
> wait as wait_ms
> set next thread signal
*/
void Thread_Func (void const *params) {
	char str[32];
	int i = *(int*) params;
	int next_thread_id = (i + 1 + THREAD_COUNT) % THREAD_COUNT;
	int wait_ms = 500;
	
  while (1) {		
		osSignalWait(0x0001, osWaitForever);		
		sprintf(str, "Thread: %d", i);
		EventRecordData(PRINT, (const void*)str, sizeof(str));
		osDelay(wait_ms);
		osSignalSet(tid_Thread[next_thread_id], 0x0001);
  }
}                                                                   
   

/*
> create threads
> set thread signal for the first thread
*/
int Init_Threads (void) {
	int i;
	void* params = &i;

	osThreadDef (Thread_Func, osPriorityNormal, 1, 0); 
	
	
	for(i = 0; i < THREAD_COUNT; i++){
		tid_Thread[i] = osThreadCreate (osThread(Thread_Func), params);
		osDelay(10);
	}		
	
  osSignalSet(tid_Thread[0], 0x0001);

  return(0);
}


