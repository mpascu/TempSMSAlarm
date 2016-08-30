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
#include <libpic30.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
char AT[] = "AT"; // To initialize mode
char noecho[] = "ATE0"; // To stop echo
char mode_text[] = "AT+CMGF=1"; // to set text mode
char char_mode[] = "AT+CSCS=\"GSM\""; // to set character mode
char param[] = "AT+CSMP=17,167,0,0"; // set the parameter of character
char mobile_no[] = "AT+CMGS=\"+34666xxxxxx\""; //use to set receinpent number and mesg
char mesg[] = "Temperatura de la nevera 4 fora de rang"; // mesg we want to send
char terminator = 0x1A; // chartacter form of control + z terminator character

uint16_t contador = 2;
int BAUD = 9600;

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

    //Main Program Loop, Loop forever
    while (1) {
        while (TMR1 < 0xF424) {
        };
        LED ^= 1;
        TMR1 = 0x0000;
        if (contador == 5) {

            vPutStrU1(AT);
            vPutCharU1('\n');
            __delay_ms(300);

            vPutStrU1(noecho);
            vPutCharU1('\n');
            __delay_ms(300);

            vPutStrU1(mode_text);
            vPutCharU1('\n');
            __delay_ms(300);

            vPutStrU1(char_mode);
            vPutCharU1('\n');
            __delay_ms(300);

            vPutStrU1(param);
            vPutCharU1('\n');
            __delay_ms(300);

            vPutStrU1(mobile_no);
            vPutCharU1('\n');
            __delay_ms(300);

            vPutStrU1(mesg);
            vPutCharU1('\n');
            __delay_ms(300);

            vPutCharU1(terminator);
        }
        contador++;

    }
    return 0;
}

