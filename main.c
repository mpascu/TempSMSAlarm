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

#define FCY SYS_FREQ/2
#define NUM_SENSORS 5

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
#include "alarms.h"
#include <libpic30.h>



void readSensors();
void initSensors();
/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

unsigned char serial_number[8];
unsigned char DEVICE_PRESENT;
int BAUD = 9600;
uint16_t contador = 0;

tempLogic sensors[NUM_SENSORS];

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int16_t main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    __delay_ms(100);

    /* Initialize IO ports and peripherals */
    InitApp();
    __delay_ms(1000);
    //LED =1;
    /* Initialize UART */
    UART1Init(BAUD);
    __delay_ms(5000);

    /* Initialize GSM module */
    initSMS();

    /* Initialize sensors*/
    initSensors();

    //Main Program Loop, Loop forever    
    while (1) {

        readSensors();

        if (RUN_READ_PIN == 1) {
            checkTemperatures(&sensors[0],NUM_SENSORS);
            LEDALR = isAlarmActive(&sensors[0],NUM_SENSORS);
        }
        __delay_ms(200);
        contador++;
    }
    return 0;
}

void readSensors() {
    int loop;
    for (loop = 0; loop < NUM_SENSORS; loop++) {
        getTemperature(loop+1, &sensors[loop]);
    }
}

void initSensors() {
    int loop;
    for (loop = 0; loop < NUM_SENSORS; loop++) {
        sensors[loop].alarmActive = 0;
    }
}

//_INT1Interrupt() is the INT1 interrupt service routine (ISR).
void __attribute__((__interrupt__)) _INT1Interrupt(void);

void __attribute__((__interrupt__, auto_psv)) _INT1Interrupt(void) {
    sendInfoSMS(sensors[0], sensors[1], sensors[2], sensors[3], sensors[4]);
    IFS1bits.INT1IF = 0; //Clear the INT1 interrupt flag or else
    //the CPU will keep vectoring back to the ISR 
}

//_T1Interrupt() is the T1 interrupt service routine (ISR).
void __attribute__((__interrupt__)) _T1Interrupt(void);

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void) {
    if (RUN_READ_PIN == 1) {
        LEDRUN = !LEDRUN;
    }
    else{
        LEDRUN = 0;
    }
    IFS0bits.T1IF = 0;
}