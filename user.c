/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include <stdint.h>          /* For uint32_t definition */
#include <stdbool.h>         /* For true/false definition */

#include "user.h"            /* variables/params used by user.c */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

void InitApp(void)
{
    /* Setup analog functionality and port direction */
    // Initialize the LED
    LED_TRIS = 0;

    /* Initialize Timer 1
     * Each configuration sets the MCU's oscillator to 32MHz (see the respective
     * "system.c" for configuration bits).  For the LED to blink
     * at a rate of 1Hz, it must be toggled at 2Hz.
     *
     * Calculation:
     * Fcy = Fosc / 2 = 16E6 [Hz]
     * T1CONbits.TCKPS = 3 divides the input clock by 256.
     * PR1 = Fcy[Hz] / 256 / 2[Hz] = 0x7A12;
     */
    _T1IF = 0;
    _T1IE = 0;
    TMR1 = 0x0000;
    PR1 = 0xF424;
    T1CONbits.TCKPS = 3;
    T1CONbits.TON = 1;
    
    //Set up I/O Port
    AD1PCFGL	 =	0xFFFF;	 //set to all digital I/O
    //TRISB	 =	0xF3FF;	 //configure all PortB as input
    /* Initialize peripherals */
}

