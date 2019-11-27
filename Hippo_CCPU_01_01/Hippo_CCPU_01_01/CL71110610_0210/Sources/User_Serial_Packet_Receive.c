/*
** ###################################################################
**     Filename  : User_Serial_Packet_Receive.c
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User can write applications for serial packet recieves
**          This function gets called once per received serail packet
**          A packet consists of:
**          [ = start byte
**          * = denotes that it is a user packet
**          data (up to 147 bytes- 150 total include start, packet type, and end byte
**          ] = close byte
**
**     (c) Copyright HED, inc. 2006-2008
**     HED, inc.
**     2120 Constitution Ave.
**     Hartford, WI 53089
**     United States
**     http      : www.hedonline.com
**     mail      : support@hedonline.com
** ###################################################################
*/

/* Include Header Files */
#include "reserved.h"
#include "prototypes.h"
#include "constants.h"
#include "User_Serial_Packet_Receive.h"
#include <stdio.h>

void User_Serial_Packet_Receive(UINT8 far sci_bytes[MAX_RX_MESSAGE_SIZE], UINT8 uint8_sci_line)
{
   UINT8 index;

   SciLineForPrintf = uint8_sci_line;
   (void) printf("packet");
   
   for(index = 0; index < MAX_RX_MESSAGE_SIZE; index++)
   {
      (void) Send_SCI_Byte(uint8_sci_line, sci_bytes[index]);
      
      if(sci_bytes[index] == ']')
      {
         break;
      }
      else
      {
         /* continue sending */
      }
   }
}
