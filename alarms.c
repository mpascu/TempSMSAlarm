/*
 * File:   alarms.c
 * Author: Marc Pascual
 *
 * Created on 8 de septiembre de 2016, 16:44
 */

#include "xc.h"
#include <stdint.h>
#include "alarms.h"
#include "sensor.h"
#include "SMS.h"

float TEMP_MIN = 4.0;
float TEMP_MAX = 8.0;

/*******************************************************************************
 * Function: void checkTemperatures (tempLogic* sensors ) 
 * PreCondition:    SMS code must be initialized with SMSinit()
 *                  At least one reading of the sensors must be done
 * @param tempLogic* sensors array of all sensors
 * @param numSensors number of active temperature sensors
 * Overview: This function sends and SMS if there is a temperature out of the
 *           defined limits
 ******************************************************************************/
void checkTemperatures (tempLogic* sensors, int numSensors ){
    int loop;
    for (loop=0;loop<numSensors;loop++){
        //tempLogic *a = **sensors[loop];
        float temp= temp2float(*(sensors+loop));
        if ((sensors+loop)->alarmActive==0 && (temp>TEMP_MAX || temp<TEMP_MIN) ){
            sendErrorSMS(*(sensors+loop),loop);
            (sensors+loop)->alarmActive = 1;
        }
        if ((sensors+loop)->alarmActive == 1 && (temp<TEMP_MAX && temp>TEMP_MIN) ){
            (sensors+loop)->alarmActive = 0;
        }
    }
}
/*******************************************************************************
 * Function: bool isAlarmActive(tempLogic* sensors, int numSensors)
 * PreCondition: checkTemperatures() should be executed before to activate alarm bits     
 * @param tempLogic* sensor array of all sensors
 * @param numSensors number of active temperature sensors
 * Overview: returns true if an alarm is active, false otherwise
 ******************************************************************************/
bool isAlarmActive(tempLogic* sensors, int numSensors){
    int loop;
    for (loop=0;loop<numSensors;loop++){
        if ((sensors+loop)->alarmActive==1){
            return true;
        }
    }
    return false;
}
