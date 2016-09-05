
#ifndef _1wire_H
#define _1wire_H

/** I N C L U D E S **********************************************************/
#include "system.h"
#include <stdbool.h>
/** P R O T O T Y P E S ******************************************************/
void drive_one_wire_low (int8_t sId);
void drive_one_wire_high (int8_t sId);
unsigned char read_OW( int8_t sId );
unsigned char OW_reset_pulse(int8_t sId);
void OW_write_bit (int8_t sId, unsigned char write_data);
void OW_write_byte (int8_t sId,unsigned char write_data);
unsigned char OW_read_bit (int8_t sId);
unsigned char OW_read_byte (int8_t sId);

bool OW_read_pin (int8_t sId);
/*****************************************************************************
   V A R I A B L E S
******************************************************************************/

#endif