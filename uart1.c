/*
 * File:   uartSetup.c
 * Author: Marc Pascual Terron
 *
 * Created on 16 de agosto de 2016, 16:19
 */


#include "system.h" 
#include "uart1.h"

char rcv [100];
int count = 0;

/******************************************************************************
 * Function:   void UART1Init(int BAUDRATE)
 * PreCondition: None
 * Input:        int BAUDRATE                 
 * Output:       None
 * Overview:     Initialises UART1 module setting all required bits and the 
 *               given baudrate
 *****************************************************************************/
void UART1Init(int BAUDRATE) {

    // This is an EXAMPLE, so brutal typing goes into explaining all bit sets
    // The HPC16 board has a DB9 connector wired to UART2, so we will
    // be configuring this port only
    // configure U1MODE
    U1MODEbits.UARTEN = 0; // Bit15 TX, RX DISABLED, ENABLE at end of func

    //U1MODEbits.notimplemented;// Bit14
    U1MODEbits.USIDL = 0; // Bit13 Continue in Idle
    U1MODEbits.IREN = 0; // Bit12 No IR translation
    U1MODEbits.RTSMD = 0; // Bit11 Simplex Mode

    //U1MODEbits.notimplemented;// Bit10
    U1MODEbits.UEN = 0; // Bits8,9 TX,RX enabled, CTS,RTS not
    U1MODEbits.WAKE = 0; // Bit7 No Wake up (since we don't sleep here)
    U1MODEbits.LPBACK = 0; // Bit6 No Loop Back
    U1MODEbits.ABAUD = 0; // Bit5 No Autobaud (would require sending '55')
    U1MODEbits.BRGH = 0; // Bit3 16 clocks per bit period
    U1MODEbits.PDSEL = 0; // Bits1,2 8bit, No Parity
    U1MODEbits.STSEL = 0; // Bit0 One Stop Bit

    // Load a value into Baud Rate Generator.  Example is for 9600.
    // See section 19.3.1 of datasheet.
    //  U1BRG = (Fcy/(16*BaudRate))-1
    //  U1BRG = (37M/(16*9600))-1
    //  U1BRG = 240
    long aux = BAUDRATE;
    long aux1 = 16L * aux;
    int BRG = 16000000UL / aux1;
    U1BRG = BRG; // 16Mhz osc, 9600 Baud 104

    // Load all values in for U1STA SFR
    U1STAbits.UTXISEL1 = 0; //Bit15 Int when Char is transferred (1/2 config!)
    U1STAbits.UTXINV = 0; //Bit14 N/A, IRDA config
    U1STAbits.UTXISEL0 = 0; //Bit13 Other half of Bit15

    //U1STAbits.notimplemented = 0;//Bit12
    U1STAbits.UTXBRK = 0; //Bit11 Disabled
    U1STAbits.UTXEN = 0; //Bit10 TX pins controlled by periph
    U1STAbits.UTXBF = 0; //Bit9 *Read Only Bit*
    U1STAbits.TRMT = 0; //Bit8 *Read Only bit*
    U1STAbits.URXISEL = 0; //Bits6,7 Int. on character recieved
    U1STAbits.ADDEN = 0; //Bit5 Address Detect Disabled
    U1STAbits.RIDLE = 0; //Bit4 *Read Only Bit*
    U1STAbits.PERR = 0; //Bit3 *Read Only Bit*
    U1STAbits.FERR = 0; //Bit2 *Read Only Bit*
    U1STAbits.OERR = 0; //Bit1 *Read Only Bit*
    U1STAbits.URXDA = 0; //Bit0 *Read Only Bit*


    IPC7 = 0x4400; // Mid Range Interrupt Priority level, no urgent reason
    IFS0bits.U1TXIF = 0; // Clear the Transmit Interrupt Flag
    IEC0bits.U1TXIE = 1; // Enable Transmit Interrupts
    IFS0bits.U1RXIF = 0; // Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1; // Enable Recieve Interrupts

    RPINR18bits.U1RXR = 2; //UART1 receive set to RB2
    RPOR1bits.RP3R = 3; //UART1 transmit set to RB3

    U1MODEbits.UARTEN = 1; // And turn the peripheral on
    U1STAbits.UTXEN = 1;
}

/******************************************************************************
 * Function:   void vPutCharU1 ( char cChar )
 * PreCondition: UART1 module must be initialized from void UART1Init
 * Input:        char cChar (character to send)              
 * Output:       None
 * Overview:     Sends one character to UART1 (use of blocking wait)
 *****************************************************************************/
void vPutCharU1(char cChar) {
    while (U1STAbits.UTXBF); // Waits when the output buffer is full
    U1TXREG = cChar; // Puts the character to the buffer
    //UART1            = cChar;
}

/******************************************************************************
 * Function:   void vPutStrU1 ( char* pcStr )
 * PreCondition: UART1 module must be initialized from void UART1Init
 * Input:        char* pcStr Pointer to the string              
 * Output:       None
 * Overview:     Sends given string to UART1
 *****************************************************************************/
void vPutStrU1(char* pcStr) {
    /*while( *pcStr != 0 )
    {
        vPutCharU1(*pcStr++);
    }*/

    int i;
    for (i = 0; pcStr[i] != '\0'; i++) {
        char ch = pcStr[i];
        vPutCharU1(ch);
    }
}

/******************************************************************************
 * Function:   char cGetCharU1( void )
 * PreCondition: UART1 module must be initialized from void UART1Init
 * Input:        None              
 * Output:       char, received character
 * Overview:     Waits until there is a char in the input buffer and returns it
 *                  (blocking wait)
 *****************************************************************************/
char cGetCharU1(void) {
    while (!U1STAbits.URXDA); // Waits when the input buffer is empty
    return U1RXREG; // Returns with the received character
}

/******************************************************************************
 * Function:   void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void)
 * PreCondition: UART Module must be Initialized with receive interrupt enabled.
 * Input:        None                
 * Output:       None
 * Overview:     UART reveive interrupt service routine called whenever a data
 *               is received from UART Rx buffer
 *****************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {

    //rcv[count] = U1RXREG;
    count++;
    //custom code  
    while (!U1STAbits.TRMT); // Echo Back Received Character
    //U1TXREG = a;   
    //end custom code
    _U1RXIF = 0; // Clear UART RX Interrupt Flag.
}

/******************************************************************************
 * Function:   void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void)
 * PreCondition: UART Module must be Initialized with transmit interrupt enabled.
 * Input:        None                
 * Output:       None
 * Overview:     UART transmit interrupt service routine called whenever a data
 *               is sent from UART Tx buffer
 *****************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0;
}


