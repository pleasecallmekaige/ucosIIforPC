/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                             (c) Copyright 1998-2004, Micrium, Weston, FL
*                                          All Rights Reserved
*
*
*                                            WIN32 Sample Code
*
* File : APP.C
* By   : Eric Shufro
*********************************************************************************************************
*/

#include "includes.h"

/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE    128
#define  TASK0_PRIO    4
#define  TASK1_PRIO    5
#define  TASK2_PRIO    6

/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

OS_STK        App_TaskStk0[TASK_STK_SIZE];
OS_STK        App_TaskStk1[TASK_STK_SIZE];
OS_STK        App_TaskStk2[TASK_STK_SIZE];

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  App_Task0(void *p_arg);
static  void  App_Task1(void *p_arg);
static  void  App_Task2(void *p_arg);

#if OS_VIEW_MODULE > 0
static  void  AppTerminalRx(INT8U rx_data);
#endif

/*
*********************************************************************************************************
*                                                _tmain()
*
* Description : This is the standard entry point for C++ WIN32 code.  
* Arguments   : none
*********************************************************************************************************
*/


unsigned int B=0;
void main(int argc, char *argv[])
{
	INT8U  err;

    OSInit();                              /* Initialize "uC/OS-II, The Real-Time Kernel"                                      */

    OSTaskCreateExt(App_Task1,
                    (void *)0,
                    (OS_STK *)&App_TaskStk1[TASK_STK_SIZE-1],
                    TASK1_PRIO,
                    TASK1_PRIO,
                    (OS_STK *)&App_TaskStk1[0],
                    TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_SIZE > 11
    OSTaskNameSet(APP_TASK_START_PRIO, (INT8U *)"Start Task", &err);
#endif

#if OS_TASK_NAME_SIZE > 14
    OSTaskNameSet(OS_IDLE_PRIO, (INT8U *)"uC/OS-II Idle", &err);
#endif

#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
    OSTaskNameSet(OS_STAT_PRIO, "uC/OS-II Stat", &err);
#endif
	OS_Printf("\r\nTCB_cur	0x%x	runtimer	%d	CPU_use	%d",OSTCBCur,OSCtxSwCtr,OSCPUUsage);
//	scanf("%c",&B);
	OS_Printf("\r\nDesdCycle : task");
    OSStart();      /* Start multitasking (i.e. give control to uC/OS-II)                               */                       
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

void  App_Task0 (void *p_arg)
{
	unsigned int Task0_RunTime=0;
    p_arg = p_arg;

#if OS_TASK_STAT_EN > 0
    OSStatInit();                                /* Determine CPU capacity                                                     */
#endif
    
    while (TRUE)                                 /* Task body, always written as an infinite loop.                             */
	{   
		Task0_RunTime++;
		OSTimeDlyHMSM(0, 0, 3, 0); 
		OS_Printf("\r\n任务1你先停停，我要运行一下。");
    }
}

void  App_Task1 (void *p_arg)
{
	unsigned int Task1_RunTime=0;
    p_arg = p_arg;

#if OS_TASK_STAT_EN > 0
    OSStatInit();                                /* Determine CPU capacity                                                     */
#endif
    
    while (TRUE)                                 /* Task body, always written as an infinite loop.                             */
	{
		Task1_RunTime++;
		if(Task1_RunTime&0x40000000)
		{
			B++;
			Task1_RunTime=0;
			OS_Printf("\r\n我是任务1，我是死循环，我还有一个小弟他的优先级比我低，我要一直运行，不让我小弟运行。");
			if(B==10)
			{
		    OSTaskCreateExt(App_Task0,										//
                    (void *)0,										//
                    (OS_STK *)&App_TaskStk0[TASK_STK_SIZE-1],		//
                    TASK0_PRIO,										//
                    TASK0_PRIO,										//
                    (OS_STK *)&App_TaskStk0[0],						//
                    TASK_STK_SIZE,									//
                    (void *)0,										//
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);	
			}
		}
	}
}

void  App_Task2 (void *p_arg)
{
	unsigned int Task2_RunTime=0;
    p_arg = p_arg;

#if OS_TASK_STAT_EN > 0
    OSStatInit();                                /* Determine CPU capacity                                                     */
#endif
    
    while (TRUE)                                 /* Task body, always written as an infinite loop.                             */
	{    
		Task2_RunTime++;
		OSTimeDlyHMSM(0, 0, 1, 0); 
		OS_Printf("\r\n我是任务2，我运行啦。");   
    }
}