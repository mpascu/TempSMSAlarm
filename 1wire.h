
#ifndef _1wire_H
#define _1wire_H

/** I N C L U D E S **********************************************************/

/** P R O T O T Y P E S ******************************************************/
void drive_one_wire_low (void);
void drive_one_wire_high (void);
unsigned char read__one_wire (void);
void OW_write_bit (unsigned char write_data);
unsigned char OW_read_bit (void);
unsigned char OW_reset_pulse(void);
void OW_write_byte (unsigned char write_data);
unsigned char OW_read_byte (void);

/*****************************************************************************
   V A R I A B L E S
******************************************************************************/

#endif