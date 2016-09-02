/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
//#define FCY 16000000UL
#define FCY             SYS_FREQ/2

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

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>         
#include <stdbool.h>       /* Includes true/false definition                  */
#include "uart1.h"
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
#include "1wire.h"
#include "SMS.h"
#include "sensor.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

unsigned char temp_lsb, temp_msb; //, temp;
unsigned char serial_number[8];
unsigned char DEVICE_PRESENT;
int BAUD = 9600;
uint16_t contador = 0;

/*typedef union temperature
{
    int16_t temperatura;
    tempLogic temp;
} ;*/

tempLogic temp1;
tempLogic temp2;
tempLogic temp3;
tempLogic temp4;
/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

int16_t main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    /* Initialize UART */
    UART1Init(BAUD); //BRGx = Fcy / (16*BAUDR) -1 = 21,5E6/16*9600 -1

    DEVICE_PRESENT = Detect_Slave_Device();
 
    //Main Program Loop, Loop forever    
    while (1) {
        while (TMR1 < 0xF424) {
        };
        LED ^= 1;
        TMR1 = 0x0000;
        temp1 = getTemperature(1);
        if (contador == 5) {
            sendSMS(temp1.intPart, temp1.decPart);
        }
        
        contador++;
    }
    return 0;
}