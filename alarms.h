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
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ALARMS_H
#define	ALARMS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "sensor.h"

/*******************************************************************************
 * Function: void checkTemperatures (tempLogic* sensors ) 
 * PreCondition:    SMS code must be initialized with SMSinit()
 *                  At least one reading of the sensors must be done
 * @param tempLogic* sensors array of all sensors
 * @param numSensors number of active temperature sensors
 * Overview: This function sends and SMS if there is a temperature out of the
 *           defined limits
 ******************************************************************************/
void checkTemperatures (tempLogic* sensors, int numSensors );

/*******************************************************************************
 * Function: bool isAlarmActive(tempLogic* sensors, int numSensors)
 * PreCondition: checkTemperatures() should be executed before to activate alarm bits     
 * @param tempLogic* sensor array of all sensors
 * @param numSensors number of active temperature sensors
 * Overview: returns true if an alarm is active, false otherwise
 ******************************************************************************/
bool isAlarmActive(tempLogic* sensors, int numSensors);

#endif	/* XC_HEADER_TEMPLATE_H */

