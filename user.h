#ifndef _USER_H
#define _USER_H
/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#include <xc.h>


//ONE WIRE PORT PIN DEFINITION
///****************************************************
// This Configuration is required to make any PIC MicroController
// I/O pin as Open drain to drive 1-wire.
///****************************************************
#define OW1_PIN_DIRECTION 	_LATB6
#define OW1_WRITE_PIN  		_TRISB6
#define OW1_READ_PIN		PORTBbits.RB6
#define OW2_PIN_DIRECTION 	_LATB7
#define OW2_WRITE_PIN  		_TRISB7
#define OW2_READ_PIN        PORTBbits.RB7
#define OW3_PIN_DIRECTION 	_LATB10
#define OW3_WRITE_PIN  		_TRISB10
#define OW3_READ_PIN		PORTBbits.RB10
#define OW4_PIN_DIRECTION 	_LATB11
#define OW4_WRITE_PIN  		_TRISB11
#define OW4_READ_PIN		PORTBbits.RB11
#define OW5_PIN_DIRECTION 	_LATB12
#define OW5_WRITE_PIN  		_TRISB12
#define OW5_READ_PIN		PORTBbits.RB12

/*
 *BUTTONS
 */
#define TEST_BUTTON      	_LATB14
#define TEST_READ_PIN		PORTBbits.RB14

#define RUN_BUTTON      	_LATB15
#define RUN_READ_PIN		PORTBbits.RB15

/*
 *LEDS
 */
#define LEDRUN  	 _LATA0
#define LEDRUN_TRIS _TRISA0

#define LEDALR  	 _LATA1
#define LEDALR_TRIS _TRISA1

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

void InitApp(void); /* I/O and Peripheral Initialization */

#endif