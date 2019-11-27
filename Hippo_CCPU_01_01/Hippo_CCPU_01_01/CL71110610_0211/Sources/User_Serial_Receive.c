/*
** ###################################################################
**     Filename  : User_Serial_Receive.c
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User can write applications for serial byte recieves
**          This function gets called once per received serail byte
**          The user needs to return if their application uses the byte
**          If the user mistakenly uses an HED message it will cause the PC tools not to work properly
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
#include "User_Serial_Receive.h"
#include <stdio.h>

void User_Serial_Receive(UINT8 sci_byte, UINT8 uint8_sci_line)
{
   SciLineForPrintf = uint8_sci_line;
   (void) printf("byte");
   
   (void) Send_SCI_Byte(uint8_sci_line, sci_byte);
}
