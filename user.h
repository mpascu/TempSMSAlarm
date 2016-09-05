#ifndef _USER_H
#define _USER_H
/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#include <xc.h>
#define LED  	 _LATA0
#define LED_TRIS _TRISA0


//ONE WIRE PORT PIN DEFINITION
///****************************************************
// This Configuration is required to make any PIC MicroController
// I/O pin as Open drain to drive 1-wire.
///****************************************************
#define OW1_PIN_DIRECTION 	_LATB7
#define OW1_WRITE_PIN  		_TRISB7
#define OW1_READ_PIN		PORTBbits.RB7
#define OW2_PIN_DIRECTION 	_LATB8
#define OW2_WRITE_PIN  		_TRISB8
#define OW2_READ_PIN        PORTBbits.RB8
#define OW3_PIN_DIRECTION 	_LATB9
#define OW3_WRITE_PIN  		_TRISB9
#define OW3_READ_PIN		PORTBbits.RB9
#define OW4_PIN_DIRECTION 	_LATB10
#define OW4_WRITE_PIN  		_TRISB10
#define OW4_READ_PIN		PORTBbits.RB10
#define OW5_PIN_DIRECTION 	_LATB11
#define OW5_WRITE_PIN  		_TRISB11
#define OW5_READ_PIN		PORTBbits.RB11

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void); /* I/O and Peripheral Initialization */
#endif