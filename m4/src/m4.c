/*
===============================================================================
 Name        : m4.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "board.h"
#include <cr_section_macros.h>
#include "cr_start_m0.h"


/*****************************************************************************
 * Public functions
 ****************************************************************************/

void SysTick_Handler(void)
{
	//__DSB();
	__SEV();
}

void M0SUB_IRQHandler(void)
{
	// Clear M0SUB event
	LPC_CREG->M0SUBTXEVENT = 0;
	Board_LED_Set(0, true);
	__SEV();
}

int main(void) {

    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();

    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();

    // Start M0SUB slave processor
    cr_start_m0(SLAVE_M0SUB,&__core_m0sub_START__);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;

    /* Start the tick timer */
    //SysTick_Config(SystemCoreClock/ 100);

    NVIC_EnableIRQ(M0SUB_IRQn);
    __SEV();
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
        __WFI();
    }
    return 0 ;
}
