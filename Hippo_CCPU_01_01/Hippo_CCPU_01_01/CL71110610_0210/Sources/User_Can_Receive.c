/*
** ###################################################################
**     Filename  : User_Can_Receive.c
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User can write applications for can message recieves
**          This function gets called once per received can message
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
#include "User_Can_Receive.h"
#include "user_app.h"

void User_Can_Receive(Can_Message_ canmessage, UINT8 module_id, UINT8 can_line)
{

 unsigned int Rx_PGN;
 unsigned int Rx_CAN;
 unsigned int Rx_Module ;
 unsigned char Rx_Source_Address;

  Rx_Source_Address = (unsigned char)(canmessage.identifier & 0xFF);
  Rx_PGN = (unsigned int)((canmessage.identifier >> 8) & 0xFFFF);
  Rx_CAN =  (can_line);
  Rx_Module = (module_id);
  
  /*Check for RC1 messages*/
  
                                                                                             
  if ( (Rx_PGN == 0xFF82) && (Rx_Source_Address == 0x4C) && (Rx_CAN == CAN_Tx_1) && (Rx_Module == Display))
  {
       As.RC1_com_timer = 100;
       qRC1Fault = 0;
       
  }
  
  /* Check to see that RC messages are still being Rx */
  if ( As.RC1_com_timer )
  {
    As.RC1_com_timer--;
  } else 
  {
  /* Timer ran out, so CAN message is now missing */
     qRC1Fault = 1;
  }
  
   /*Check for RC2 messages*/
  
                                                                                             
  if ( (Rx_PGN == 0xFF82) && (Rx_Source_Address == 0x4D) && (Rx_CAN == CAN_Tx_1) && (Rx_Module == Display))
  {
       As.RC2_com_timer = 100;
       qRC2Fault = 0;
       
  }
  
  /* Check to see that RC messages are still being Rx */
  if ( As.RC2_com_timer )
  {
    As.RC2_com_timer--;
  } else 
  {
  /* Timer ran out, so CAN message is now missing */
     qRC2Fault = 1;
  }
  
  /*Check for engine messages*/
  
                                                                                             
  if ( (Rx_PGN == 0xF004) && (Rx_Source_Address == 0) && (Rx_CAN == CAN_Tx_2) && (Rx_Module == Display))
  {
       As.Eng_com_timer = 100;
       qEngComFault = 0;
  }
  
  /* Check to see that Engine messages are still being Rx */
  if ( As.Eng_com_timer )
  {
    As.Eng_com_timer--;
  } else 
  {
  /* Timer ran out, so CAN message is now missing */
     qEngComFault = 1;
  }

}
  