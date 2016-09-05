/*
 * File:   SMS.c
 * Author: Marc Pascual
 *
 * Created on 1 de septiembre de 2016, 11:55
 */


#include "xc.h"
#include "SMS.h"
#include "uart1.h"
#include <stdio.h>      //sprintf

/* SMS parameters declaration*/
char AT[] = "AT\n"; // To initialize mode
char noecho[] = "ATE0\n"; // To stop echo
char mode_text[] = "AT+CMGF=1\n"; // to set text mode
char char_mode[] = "AT+CSCS=\"GSM\"\n"; // to set character mode
char param[] = "AT+CSMP=17,167,0,0\n"; // set the parameter of character
char mobile_no[] = "AT+CMGS=\"+34666352492\"\n"; //use to set receinpent number and mesg
char ALRmesg[] = "Temperatura de la nevera 1 fora de rang [4-8]C : "; // mesg we want to send
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
    vPutStrU1(mobile_no);
    
    /* SENSOR 1*/
    vPutStrU1(INFOmesg);
    vPutStrU1("1: ");
    char t1[2];
    sprintf(t1, "%i", temp1.intPart);
    vPutStrU1(t1);
    vPutStrU1(",");
    char t11[2];
    sprintf(t11, "%i", temp1.decPart);
    vPutStrU1(t11);
    vPutStrU1("C \n");
    
    /* SENSOR 2*/
    vPutStrU1(INFOmesg);
    vPutStrU1("2: ");
    char t2[2];
    sprintf(t2, "%i", temp2.intPart);
    vPutStrU1(t2);
    vPutStrU1(",");
    char t22[2];
    sprintf(t22, "%i", temp2.decPart);
    vPutStrU1(t22);
    vPutStrU1("C \n");
    
    /* SENSOR 3*/
    vPutStrU1(INFOmesg);
    vPutStrU1("3: ");
    char t3[2];
    sprintf(t3, "%i", temp3.intPart);
    vPutStrU1(t3);
    vPutStrU1(",");
    char t33[2];
    sprintf(t33, "%i", temp3.decPart);
    vPutStrU1(t33);
    vPutStrU1("C \n");
    
    /* SENSOR 4*/
    vPutStrU1(INFOmesg);
    vPutStrU1("4: ");
    char t4[2];
    sprintf(t4, "%i", temp4.intPart);
    vPutStrU1(t4);
    vPutStrU1(",");
    char t44[2];
    sprintf(t44, "%i", temp4.decPart);
    vPutStrU1(t44);
    vPutStrU1("C \n");
    
    /* SENSOR 5*/
    vPutStrU1(INFOmesg);
    vPutStrU1("5: ");
    char t5[2];
    sprintf(t5, "%i", temp5.intPart);
    vPutStrU1(t5);
    vPutStrU1(",");
    char t55[2];
    sprintf(t55, "%i", temp5.decPart);
    vPutStrU1(t55);
    vPutStrU1("C \n");
    
    vPutCharU1(terminator);
}
