/*
===============================================================================
 Name        : m0sub.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "board.h"
#include <cr_section_macros.h>

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * Wait for message from M4 core
 */
void M4_IRQHandler(void)
{
	// Clear M4 Event
	LPC_CREG->M4TXEVENT = 0;
    Board_LED_Toggle(0);
}


int main(void) {

    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();

    // Set the LED to the state of "On"
    Board_LED_Set(0, false);


    NVIC_EnableIRQ(M4_IRQn);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
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
