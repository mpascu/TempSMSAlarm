#ifndef _SMS_H
#define _SMS_H

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

#include <xc.h> // include processor files - each processor file is guarded.  
#include "sensor.h"



/*******************************************************************************
 * Function: void initSMS() 
 * PreCondition: none
 * Overview: This function initializes the GSM module with the parameters 
 *           needed to send SMS
 ******************************************************************************/
void initSMS();

/*******************************************************************************
 * Function: void sendInfoSMS(tempLogic temp1, tempLogic temp2, 
 *              tempLogic temp3, tempLogic temp4, tempLogic temp5 ) 
 * PreCondition:    SMS code must be initialized with SMSinit()
 * @param temp1 - temp5 temperatures of the different sensors to be sent
 * Overview: This function sends and SMS indicating the temperature of each sensor
 ******************************************************************************/
void sendInfoSMS(tempLogic temp1, tempLogic temp2, tempLogic temp3,
        tempLogic temp4, tempLogic temp5 );

/*******************************************************************************
 * Function: void sendErrorSMS(tempLogic sensor, int id)
 * PreCondition:    SMS code must be initialized with SMSinit()
 * @param sensor    sensor which temperature is wrong
 * @param id        if of the out of limits sensor
 * Overview: This function sends and SMS indicating that some temperature is 
 * out of the limit
 ******************************************************************************/
void sendErrorSMS(tempLogic sensor, int id);

#endif