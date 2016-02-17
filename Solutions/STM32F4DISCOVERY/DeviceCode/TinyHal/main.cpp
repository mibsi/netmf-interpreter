////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file is part of the Microsoft .NET Micro Framework Porting Kit Code Samples and is unsupported. 
// Copyright (c) Microsoft Open Technologies, Inc. All rights reserved.
// 
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use these files except in compliance with the License.
// You may obtain a copy of the License at:
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing
// permissions and limitations under the License.
// 
#include <tinyhal.h>
//#include "OsHal.h"
#include "FreeRTOS.h"
#include "task.h"

#ifdef __CC_ARM
// we include this to error at link time if any of the C semihosted support is imported
#pragma import(__use_no_semihosting_swi)
#endif

#undef  TRACE_ALWAYS
#define TRACE_ALWAYS               0x00000001

#undef  DEBUG_TRACE
#define DEBUG_TRACE (TRACE_ALWAYS)

void BootstrapCode_GPIO();

#if PLATFORM_ARM_OS_PORT
static osThreadId ClrThreadId;

osThreadId GetClrThreadId()
{
    return ClrThreadId;
}

extern osStatus osKernelInitialize(void);
extern osStatus osKernelStart(void);
extern osThreadDef_t os_thread_def_main;

#endif

//extern void vTaskStartScheduler( void );

int main(void)
{
    CPU_GPIO_EnableOutputPin(LED4, TRUE);

	/* Start the scheduler. */
	vTaskStartScheduler();
    
        //osKernelInitialize();
        //osThreadCreate(&os_thread_def_main, NULL);
CPU_GPIO_EnableOutputPin(LED5, TRUE);
        //osKernelStart();
//CPU_GPIO_EnableOutputPin(LED5, TRUE);
    
#if PLATFORM_ARM_OS_PORT
   //ClrThreadId = osThreadGetId();
#endif

CPU_GPIO_EnableOutputPin(LED5, TRUE);

    //BootstrapCode_GPIO();
    HAL_Time_Initialize();

    HAL_Initialize();

#if !defined(BUILD_RTM) 
    DEBUG_TRACE4( STREAM_LCD, ".NetMF v%d.%d.%d.%d\r\n", VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD, VERSION_REVISION);
    DEBUG_TRACE3(TRACE_ALWAYS, "%s, Build Date:\r\n\t%s %s\r\n", HalName, __DATE__, __TIME__);
#if defined(__GNUC__)
    DEBUG_TRACE1(TRACE_ALWAYS, "GNU Compiler version %d\r\n", __GNUC__);
#else
    DEBUG_TRACE1(TRACE_ALWAYS, "ARM Compiler version %d\r\n", __ARMCC_VERSION);
#endif

    UINT8* BaseAddress;
    UINT32 SizeInBytes;

    HeapLocation( BaseAddress,    SizeInBytes );
    memset      ( BaseAddress, 0, SizeInBytes );

    debug_printf("\f");

    debug_printf("%-15s\r\n", HalName);
    debug_printf("%-15s\r\n", "Build Date:");
    debug_printf("  %-13s\r\n", __DATE__);
    debug_printf("  %-13s\r\n", __TIME__);

#endif  // !defined(BUILD_RTM)

    /***********************************************************************************/

    {
#if defined(FIQ_SAMPLING_PROFILER)
        FIQ_Profiler_Init();
#endif
    }

    // the runtime is by default using a watchdog 
   
    Watchdog_GetSetTimeout ( WATCHDOG_TIMEOUT , TRUE );
    Watchdog_GetSetBehavior( WATCHDOG_BEHAVIOR, TRUE );
    Watchdog_GetSetEnabled ( WATCHDOG_ENABLE, TRUE );

 
    // HAL initialization completed.  Interrupts are enabled.  Jump to the Application routine
    ApplicationEntryPoint();

    debug_printf("main exited!!???.  Halting CPU\r\n");

#if defined(BUILD_RTM)
    CPU_Reset();
#else
    CPU_Halt();
#endif
    return -1;
}

extern "C" void vApplicationTickHook( void )
{
// 	#if ( mainCREATE_SIMPLE_LED_FLASHER_DEMO_ONLY == 0 )
// 	{
// 		/* Just to verify that the interrupt nesting behaves as expected,
// 		increment ulFPUInterruptNesting on entry, and decrement it on exit. */
// 		ulFPUInterruptNesting++;
// 
// 		/* Fill the FPU registers with 0. */
// 		vRegTestClearFlopRegistersToParameterValue( 0UL );
// 
// 		/* Trigger a timer 2 interrupt, which will fill the registers with a
// 		different value and itself trigger a timer 3 interrupt.  Note that the
// 		timers are not actually used.  The timer 2 and 3 interrupt vectors are
// 		just used for convenience. */
// 		NVIC_SetPendingIRQ( TIM2_IRQn );
// 
// 		/* Ensure that, after returning from the nested interrupts, all the FPU
// 		registers contain the value to which they were set by the tick hook
// 		function. */
// 		configASSERT( ulRegTestCheckFlopRegistersContainParameterValue( 0UL ) );
// 
// 		ulFPUInterruptNesting--;
// 	}
// 	#endif
}

extern "C" void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	//taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

extern "C" void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

extern "C" void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	//taskDISABLE_INTERRUPTS();
	for( ;; );
}