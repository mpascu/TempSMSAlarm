/*
 * File:   SMS.c
 * Author: laiccona9
 *
 * Created on 1 de septiembre de 2016, 11:55
 */


#include "xc.h"
#include "SMS.h"
#include "uart1.h"
#include <stdio.h>      //sprintf

/* SMS parameters declaration*/
const char AT[] = "AT\n"; // To initialize mode
const char noecho[] = "ATE0\n"; // To stop echo
const char mode_text[] = "AT+CMGF=1\n"; // to set text mode
const char char_mode[] = "AT+CSCS=\"GSM\"\n"; // to set character mode
const char param[] = "AT+CSMP=17,167,0,0\n"; // set the parameter of character
const char mobile_no[] = "AT+CMGS=\"+34666xxxxxx\"\n"; //use to set receinpent number and mesg
const char mesg[] = "Temperatura de la nevera 1 fora de rang [4-8]C : "; // mesg we want to send
const char terminator = 0x1A; // chartacter form of control + z terminator character

/**
 * 
 * @param temp
 * @param tens
 */
void sendSMS(int temp, int tens) {
    vPutStrU1(AT);
    vPutStrU1(noecho);
    vPutStrU1(mode_text);
    vPutStrU1(char_mode);
    vPutStrU1(param);
    vPutStrU1(mobile_no);
    vPutStrU1(mesg);
    char a[10];
    int tm = temp;
    sprintf(a, "%i", tm);
    vPutStrU1(a);
    vPutStrU1(",");
    tm = tens;
    sprintf(a, "%i", tm);
    vPutStrU1(a);
    vPutStrU1("C\n");
    vPutCharU1(terminator);
}
