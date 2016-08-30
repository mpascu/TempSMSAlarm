

/* 
 * File: uart1.h  
 * Author: Marc Pascual
 * Comments: Prototypes
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

//Initiation
extern void UART1Init(int BAUDRATE);

/*---------------------------------------------------------------------
  Function name: vPutCharU1
  Description: Sends one character to UART1 (use of blocking wait)
  Input parameters: Character to send
  Output parameters: -
-----------------------------------------------------------------------*/
void vPutCharU1(char cChar);

/*---------------------------------------------------------------------
  Function name: vPutStrU1
  Description: Sends string to UART1
  Input parameters: String to send
  Output parameters: -
-----------------------------------------------------------------------*/
void vPutStrU1(char* pcStr);

/*---------------------------------------------------------------------
  Function name: cGetCharU1
  Description: Receives character from UART1 (use of blocking wait)
  Input parameters: -
  Output parameters: Received character
-----------------------------------------------------------------------*/
char cGetCharU1(void);

#endif