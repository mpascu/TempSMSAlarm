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

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

#define Skip_ROM            0x00CC // 0b11001100
#define Convert_temperature 0x0044 // 0b01000100
#define Read_scratchpad     0x00BE // 0b10111110
#define READ_COMMAND_DS2411 0x33         // Command to read the 64-bit serial number from 1-wire slave device.

unsigned char temp_lsb, temp_msb; //, temp;

unsigned char serial_number[8];
unsigned char DEVICE_PRESENT;
uint16_t contador = 0;
int BAUD = 9600;

unsigned char Detect_Slave_Device(void);
void getTemperature();

struct tempLogic {
    int8_t intPart;
    int8_t decPart;
};

/*typedef union temperature
{
    int16_t temperatura;
    tempLogic temp;
} ;*/

struct tempLogic tempReal;
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

    OW_write_byte(READ_COMMAND_DS2411); // Send a command to read a serial number
    int loop;
    for (loop = 0; loop < 8; loop++)
        serial_number[loop] = OW_read_byte(); // Read 64-bit registration (48-bit serial number) number from 1-wire Slave Device

    //Main Program Loop, Loop forever    
    while (1) {
        while (TMR1 < 0xF424) {
        };
        LED ^= 1;
        TMR1 = 0x0000;
        if (contador == 5) {
            sendSMS(tempReal.intPart, tempReal.decPart);
        }
        getTemperature();
        contador++;
    }
    return 0;
}

unsigned char Detect_Slave_Device() {
    if (!OW_reset_pulse())
        return HIGH;
    else
        return LOW;
}

void getTemperature() {
    OW_reset_pulse();

    OW_write_byte(Skip_ROM); //Skip rom command because there is only one slave per bus
    OW_write_byte(Convert_temperature); //Ask the sensor to measure and save the temperature to the scratchpad

    __delay_ms(750); //Let the sensor made the measurement
    OW_reset_pulse();

    OW_write_byte(Skip_ROM);
    OW_write_byte(Read_scratchpad); //Read temperature

    /*char getBit[10];
    for (int k = 0; k < 9; k++) {
        getBit[k] = OW_read_byte();
    }
    temp_msb = getBit[1];
    temp_lsb = getBit[0];*/

    temp_lsb = OW_read_byte();
    temp_msb = OW_read_byte();

    tempReal.intPart = (temp_msb * 16)+(temp_lsb >> 4);
    tempReal.decPart = 0;
    if (temp_lsb & 0x08)
        tempReal.decPart = 50;
    if (temp_lsb & 0x04)
        tempReal.decPart += 25;
    if (temp_lsb & 0x02)
        tempReal.decPart += 12;
    if (temp_lsb & 0x01)
        tempReal.decPart += 6;
}