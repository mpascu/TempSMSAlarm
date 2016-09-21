/*
 * File:   SMS.c
 * Author: Marc Pascual
 *
 * Created on 1 de septiembre de 2016, 11:55
 */
#define FCY SYS_FREQ/2

#include "system.h"
#include "xc.h"
#include "SMS.h"
#include "uart1.h"
#include <stdio.h>      //sprintf
#include <libpic30.h>


/* SMS parameters declaration*/
char AT[] = "AT\r"; // To initialize mode
char noecho[] = "ATE0\r"; // To stop echo
char mode_text[] = "AT+CMGF=1\r"; // to set text mode
char char_mode[] = "AT+CSCS=\"GSM\"\r"; // to set character mode
char param[] = "AT+CSMP=17,167,0,0\r"; // set the parameter of character
char mobile_no[] = "AT+CMGS=\"+34xxxxxxxxx\"\r"; //use to set receinpent number and mesg
char mobile_no1[] = "AT+CMGS=\"+34625xxxxxx\"\r"; //use to set receinpent number and mesg
char ALRmesg[] = "Temperatura de la nevera %i fora de rang [4-8]C : %i,%i C \r"; // mesg we want to send
char INFOmesg[] = "Sensor "; // mesg we want to send
char terminator = 0x1A; // chartacter form of control + z terminator character

/*******************************************************************************
 * Function: void initSMS() 
 * PreCondition: none
 * Overview: This function initializes the GSM module with the parameters 
 *           needed to send SMS
 ******************************************************************************/
void initSMS(){
    vPutStrU1(AT);
    vPutStrU1(noecho);
    vPutStrU1(mode_text);
    vPutStrU1(char_mode);
    vPutStrU1(param);
}

/*******************************************************************************
 * Function: void sendInfoSMS(tempLogic temp1, tempLogic temp2, 
 *              tempLogic temp3, tempLogic temp4, tempLogic temp5 ) 
 * PreCondition:    SMS code must be initialized with SMSinit()
 * @param temp1 - temp5 temperatures of the different sensors to be sent
 * Overview: This function sends and SMS indicating the temperature of each sensor
 ******************************************************************************/
void sendInfoSMS(tempLogic temp1, tempLogic temp2, tempLogic temp3, tempLogic temp4, tempLogic temp5 ) {
    char aux[20];
    vPutStrU1(mobile_no);
    __delay_ms(50);
    
    /* SENSOR 1*/
    sprintf(aux, "Sensor 1: %i,%i C \n", temp1.intPart, temp1.decPart);
    vPutStrU1(aux);
    __delay_ms(50);
    
    /* SENSOR 2*/
    sprintf(aux, "Sensor 2: %i,%i C \n", temp2.intPart, temp2.decPart);
    vPutStrU1(aux);
    __delay_ms(50);
    
    /* SENSOR 3*/
    sprintf(aux, "Sensor 3: %i,%i C \n", temp3.intPart, temp3.decPart);
    vPutStrU1(aux);
    __delay_ms(50);
    
    /* SENSOR 4*/
    sprintf(aux, "Sensor 4: %i,%i C \n", temp4.intPart, temp4.decPart);
    vPutStrU1(aux);
    __delay_ms(50);
    
    /* SENSOR 5*/
    sprintf(aux, "Sensor 5: %i,%i C \n", temp5.intPart, temp5.decPart);
    vPutStrU1(aux);
    __delay_ms(50);
    
    vPutCharU1(terminator);  
    
}

/*******************************************************************************
 * Function: void sendErrorSMS(tempLogic sensor, int id)
 * PreCondition:    SMS code must be initialized with SMSinit()
 * @param sensor    sensor which temperature is wrong
 * @param id        if of the out of limits sensor
 * Overview: This function sends and SMS indicating that some temperature is 
 * out of the limit
 ******************************************************************************/
void sendErrorSMS(tempLogic sensor, int id) {
    vPutStrU1(mobile_no);
    __delay_ms(100);
    char mesg [80];
    sprintf(mesg , "Temperatura de la nevera %i fora de rang [4-8]C : %i,%i C ", id+1 , sensor.intPart,sensor.decPart);
    vPutStrU1(mesg);
    __delay_ms(100);
    vPutCharU1(terminator);
    __delay_ms(10000);
}
