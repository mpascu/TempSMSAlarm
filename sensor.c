/*
 * File:   sensor.c
 * Author: Marc Pascual
 *
 * Created on 2 de septiembre de 2016, 10:13
 */

#define FCY SYS_FREQ/2

#include "sensor.h"
#include <stdint.h>
#include "xc.h"
#include "system.h"
#include <stdbool.h>
#include "1wire.h"
#include <libpic30.h>

/**Function: bool Detect_Slave_Device(int8_t sId)
 * PreCondition:    None
 * @param sId identifier of the sensor
 * @return true if there is a sensor present, false otherwise
 */
bool Detect_Slave_Device(int8_t sId) {
    if (!OW_reset_pulse(sId))
        return HIGH;
    else
        return LOW;
}

/**Function: void readSerialNumber(char *serial_number, int8_t sId)
 * PreCondition:    None
 * @param serial_number pointer to a char[8] where the serial number will be stored
 * @param sId   identifier of the sensor
 * Overview: This function reads the serial number of the specified sensor
 */
void readSerialNumber(char *serial_number, int8_t sId){
    OW_write_byte(sId, READ_COMMAND_DS2411); // Send a command to read a serial number
    int loop;
    for (loop = 0; loop < 8; loop++)
        serial_number[loop] = OW_read_byte(sId); // Read 64-bit registration (48-bit serial number) number from 1-wire Slave Device
}

/**Function: tempLogic getTemperature(int8_t sId, tempLogic* sensor)
 * PreCondition:    None
 * @param sId   identifier of the sensor
 * @param sensor sensor struct where the temperature will ve stored
 * Overview: This function tells the specified sensor to read the temperature 
 * and then reads it from the scratchpad
 */
void getTemperature(int8_t sId, tempLogic* sensor) {
    //struct tempLogic tempReal;
    OW_reset_pulse(sId);

    OW_write_byte(sId, Skip_ROM); //Skip rom command because there is only one slave per bus
    OW_write_byte(sId, Convert_temperature); //Ask the sensor to measure and save the temperature to the scratchpad

    __delay_ms(750); //Let the sensor made the measurement
    OW_reset_pulse(sId);

    OW_write_byte(sId, Skip_ROM);
    OW_write_byte(sId, Read_scratchpad); //Read temperature

    /*char getBit[10];
    for (int k = 0; k < 9; k++) {
        getBit[k] = OW_read_byte();
    }
    temp_msb = getBit[1];
    temp_lsb = getBit[0];*/

    unsigned char temp_lsb = OW_read_byte(sId);
    unsigned char temp_msb = OW_read_byte(sId);

    sensor->intPart = (temp_msb * 16)+(temp_lsb >> 4); //get the integer part of the temperature
    sensor->decPart = 0;                               //get the decimal part 
    if (temp_lsb & 0x08)
        sensor->decPart = 50;
    if (temp_lsb & 0x04)
        sensor->decPart += 25;
    if (temp_lsb & 0x02)
        sensor->decPart += 12;
    if (temp_lsb & 0x01)
        sensor->decPart += 6;
    
}

/**Function:        float temp2float(tempLogic tmp);
 * PreCondition:    None
 * @param tmp       temperature to be converted
 * Overview:        This function converts temperature from tempLogic to float 
 */
float temp2float(tempLogic tmp){
    int a,b;
    a = tmp.intPart;
    b = tmp.decPart;
    float c;
    c = (float)b;
    while( c > 1.0f ) c *= 0.1f; //moving the decimal point (.) to left most
    c = (float)a + c;
    return c; 
}