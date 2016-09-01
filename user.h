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
#define OW_PIN_DIRECTION 	_LATB7
#define OW_WRITE_PIN  		_TRISB7
#define OW_READ_PIN			PORTBbits.RB7


/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void); /* I/O and Peripheral Initialization */
