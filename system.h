#ifndef _SYSTEM_H
#define _SYSTEM_H
/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

#include <libpic30.h>        // includes delay_us and delay_ms
#include <stdint.h>
/* ****** G E N E R I C   D E F I N I T I O N S ************************************************/

#define	HIGH	1
#define	LOW		0
#define	OUTPUT	0
#define	INPUT 	1
#define	SET		1
#define	CLEAR	0

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        32000000UL

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

#endif