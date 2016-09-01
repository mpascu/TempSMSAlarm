


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
#include "system.h"          /* variables/params used by system.c */
#include <libpic30.h>        /* includes delay_us and delay_ms
/*                                                                            */
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c                                           */
/*                                                                            */
/*                                                                            */

/* Refer to the device Family Reference Manual Oscillator section for
information about available oscillator configurations.  Typically
this would involve configuring the oscillator tuning register or clock
switching useing the compiler's __builtin_write_OSCCON functions.
Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
compiler installation directory /doc folder for documentation on the
__builtin functions. */

/* TODO Add clock switching code if appropriate.  An example stub is below.   */
void ConfigureOscillator(void) {

#if 1

    /* Disable Watch Dog Timer */
    RCONbits.SWDTEN = 0;
    //CLKDIV = 0x0000;

    CLKDIVbits.FRCDIV = 0x00;
    CLKDIVbits.PLLPOST = 0x01; // 1 -> N1 = 4
    CLKDIVbits.PLLPRE = 0x00; // 0 -> N2 = 2 

    PLLFBDbits.PLLDIV = 30;

    OSCTUNbits.TUN = 0;
    /* When clock switch occurs switch to Prim Osc (HS, XT, EC)with PLL */

    __builtin_write_OSCCONH(0x03); /* Set OSCCONH for clock switch */
    __builtin_write_OSCCONL(0x01); /* Start clock switching */
    while (OSCCONbits.COSC != 0b011);

    /* Wait for Clock switch to occur */
    /* Wait for PLL to lock, if PLL is used */
    while (OSCCONbits.LOCK != 1) {
    };
    return;

#endif

}

