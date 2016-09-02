/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File: sensor.h  
 * Author: Marc Pascual
 * Comments: Sensor related methods (get serial number, temperature...) go here
 * Revision history: 
 */

/**
 * Sensor commands definition
 */
#define Skip_ROM            0x00CC // 0b11001100
#define Convert_temperature 0x0044 // 0b01000100
#define Read_scratchpad     0x00BE // 0b10111110
#define READ_COMMAND_DS2411 0x33   // Command to read the 64-bit serial number from 1-wire slave device.

typedef struct tempLogic {
    int8_t intPart;
    int8_t decPart;
};

#include <xc.h> // include processor files - each processor file is guarded.  

/**Function: bool Detect_Slave_Device(int8_t sId)
 * PreCondition:    None
 * @param sId identifier of the sensor
 * @return true if there is a sensor present, false otherwise
 */
bool Detect_Slave_Device(int8_t sId);

/**Function: void readSerialNumber(char *serial_number, int8_t sId){
 * PreCondition:    None
 * @param serial_number pointer to a char[8] where the serial number will be stored
 * @param sId   identifier of the sensor
 * Overview: This function reads the serial number of the specified sensor
 */
void readSerialNumber(char *serial_number, int8_t sId);

/**Function: tempLogic getTemperature(int8_t sId)
 * PreCondition:    None
 * @param sId   identifier of the sensor
 * Overview: This function tells the specified sensor to read the temperature 
 * and then reads it from the scratchpad
 */
tempLogic getTemperature(int8_t sId);

