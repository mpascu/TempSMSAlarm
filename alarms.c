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
 * Overview: This function sends and SMS if there is a temperature out of the
 *           defined limits
 ******************************************************************************/
void checkTemperatures (tempLogic sensors[] ){
    int len = 5;//( sizeof(sensors)/sizeof(sensors[0]) );
    int loop;
    for (loop=0;loop<len;loop++){
        float temp= temp2float(sensors[loop]);
        if ((temp>TEMP_MAX || temp<TEMP_MIN) && !sensors[loop].alarmActive){
            sendErrorSMS(sensors[loop],loop);
            sensors[loop].alarmActive = 1;
        }
        if ((temp<TEMP_MAX || temp>TEMP_MIN) && sensors[loop].alarmActive){
            sensors[loop].alarmActive = 0;
        }
    }
}
