/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
//#define FCY 16000000UL
#define FCY             SYS_FREQ/2


#define READ_COMMAND_DS2411  	0x33         // Command to read the 64-bit serial number from 1-wire slave device.



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

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
char AT[] = "AT\n"; // To initialize mode
char noecho[] = "ATE0\n"; // To stop echo
char mode_text[] = "AT+CMGF=1\n"; // to set text mode
char char_mode[] = "AT+CSCS=\"GSM\"\n"; // to set character mode
char param[] = "AT+CSMP=17,167,0,0\n"; // set the parameter of character
char mobile_no[] = "AT+CMGS=\"+34666352492\"\n"; //use to set receinpent number and mesg
char mesg[] = "Temperatura de la nevera 1 fora de rang [4-8]C : "; // mesg we want to send
char terminator = 0x1A; // chartacter form of control + z terminator character

#define Skip_ROM 0x00CC // 0b11001100
#define Convert_temperature 0x0044 // 0b01000100
#define Read_scratchpad 0x00BE // 0b10111110
unsigned char temp_lsb, temp_msb, temp;
char getBit[10];
unsigned int tens;

unsigned char loop;
unsigned char serial_number[8];
unsigned char DEVICE_PRESENT;
uint16_t contador = 2;
int BAUD = 9600;

unsigned char Detect_Slave_Device(void);
void getTemperature();
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
    LATBbits.LATB7 = 0;
    TRISBbits.TRISB7 = 0;


    DEVICE_PRESENT = Detect_Slave_Device();

    OW_write_byte(READ_COMMAND_DS2411); // Send a command to read a serial number

    for (loop = 0; loop < 8; loop++)
        serial_number[loop] = OW_read_byte(); // Read 64-bit registration (48-bit serial number) number from 1-wire Slave Device

    //Main Program Loop, Loop forever    
    while (1) {
        while (TMR1 < 0xF424) {
        };
        LED ^= 1;
        TMR1 = 0x0000;
        if (contador == 5) {
            sendSMS();
        }

            OW_reset_pulse();

    OW_write_byte(Skip_ROM); //Skip rom command because there is only one slave per bus
    OW_write_byte(Convert_temperature); //Ask the sensor to measure and save the temperature to the scratchpad

    __delay_ms(2000); //Let the sensor made the measurement
    OW_reset_pulse();

    OW_write_byte(Skip_ROM);
    OW_write_byte(Read_scratchpad); //Read temperature

    /*for (int k = 0; k < 9; k++) {
        getBit[k] = OW_read_byte();
    }
    temp_msb = getBit[1];
    temp_lsb = getBit[0];*/

    temp_lsb = OW_read_byte();
    temp_msb = OW_read_byte();

    tens = 0;
    //temp = (temp_msb << 8) + temp_lsb;
    //temp = temp >> 4;
    temp = (temp_msb * 16)+(temp_lsb >> 4);
    if (temp_lsb & 0x08)
        tens = 500;
    if (temp_lsb & 0x04)
        tens += 250;
    if (temp_lsb & 0x02)
        tens += 125;
    if (temp_lsb & 0x01)
        tens += 62;
        
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

void sendSMS() {
    vPutStrU1(AT);
    vPutStrU1(noecho);
    vPutStrU1(mode_text);
    vPutStrU1(char_mode);
    vPutStrU1(param);
    vPutStrU1(mobile_no);
    vPutStrU1(mesg);
    char a[3];
    sprintf(&a,'%d', temp);
    vPutStrU1('25');
    vPutStrU1(",");
    //char b[3];
    //sprintf(&b,'%d', tens);
    vPutStrU1(tens);
    vPutStrU1("C");
    vPutCharU1(terminator);
}

void getTemperature() {

}