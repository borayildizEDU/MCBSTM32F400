#ifndef TEST_H
#define TEST_H


/*----------------------------------------------------------------------------
 * Constants
 *---------------------------------------------------------------------------*/
#define MAX_MEM_SIZE 0x800

/*----------------------------------------------------------------------------
 * Memory pointers
 *---------------------------------------------------------------------------*/
extern volatile unsigned int* pMem;

/*----------------------------------------------------------------------------
 * Functions 
 *---------------------------------------------------------------------------*/
extern void Test_NOP(void);
extern void Test_SystemClock(void);
extern void Test_SleepMode(void);
extern void Test_StopMode(void);
extern void Test_StandbyMode(void);
extern void Test_ThreadSwitch(void);
extern void Test_PeripheralSwitch(void);
extern void Test_MemoryWindow(void);

#endif

