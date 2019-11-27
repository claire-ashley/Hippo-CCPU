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
 

  /*Check for engine COM*/
                                                                                              
  if ((Rx_PGN == 0xFEF7) && (Rx_Source_Address == 0x00) && (Rx_CAN == CAN_Tx_2) && (Rx_Module == Display))
  {
       vEngBat = (unsigned int)((canmessage.data[7] << 8) & 0xFF00);
       vEngBat |= (unsigned char) canmessage.data[6];
      
  }
  
 
    /*Check for engine DM1*/
  
                                                                                             
  if ( (Rx_PGN == 0xFECA) && (Rx_Source_Address == 0) && (Rx_CAN == CAN_Tx_2) && (Rx_Module == Display))
  {
       
       As.DM1_timer = 100;
       qNoDM1 = 0;
  }
  
  /* Check to see that Engine messages are still being Rx */
  if ( As.DM1_timer )
  {
    As.DM1_timer--;
  } 
  else 
  {
  /* Timer ran out, so CAN message is now missing */
     qNoDM1 = 1;
  }
  
   /*Check for engine DM1 BAM*/
  
                                                                                             
  if ( (Rx_PGN == 0xECFF) && (Rx_Source_Address == 0) && (Rx_CAN == CAN_Tx_2) && (Rx_Module == Display))
  {
       vBAMnoSPN = (unsigned int)((canmessage.data[2] << 8) & 0xFF00);
       vBAMnoSPN |= (unsigned char) canmessage.data[1];
       vBAM_PGN  = (unsigned int)((canmessage.data[6] << 8) & 0xFF00);
       vBAM_PGN |= (unsigned char) canmessage.data[5];
       As.BAM_timer = 100;
       qNoBAM = 0;
   }
  
  /* Check to see that Engine messages are still being Rx */
  if ( As.BAM_timer )
  {
    As.BAM_timer--;
  } 
  else 
  {
  /* Timer ran out, so CAN message is now missing */
     qNoBAM = 1;
  }
  
  vSPNCount =  vBAMnoSPN;
  vSPNCount -= 2;
  vSPNCount /= 4;
  vSPNCount -= 1;   /* Subtract one, array index starts at (0)*/
  
  
  
  
 User_BAM();

}

void User_BAM (void)
{
/*Set up BAM Error detection  */
   ui8_Number_Of_J1939_BAM_Messages = 1;
   s_BAM_Properties[0].ui16_pgn = 0xFECA;
   s_BAM_Properties[0].ui8_source_address = 0x00;
   s_BAM_Properties[0].ui8_module_id = Display;
   s_BAM_Properties[0].ui8_can_line = CAN_Tx_2;
   
     /*Calulate Fault Codes*/
   if (qNoBAM == 0) 
   {
      vSPNState = (unsigned short) (s_BAM_Values[0].s_spn_values[vMPIndex].ui8_spn_state);
      vSPN_Display = (unsigned long) (s_BAM_Values[0].s_spn_values[vMPIndex].ui32_spn);
      vFMI_Display = (unsigned short) (s_BAM_Values[0].s_spn_values[vMPIndex].ui8_fmi);
      vOCount = (unsigned short)(s_BAM_Values[0].s_spn_values[vMPIndex]. ui8_occurance_count);
      vConv = (unsigned short)(s_BAM_Values[0].s_spn_values[vMPIndex]. ui8_conversion_method);
      vNewSPN = (unsigned short)(s_BAM_Values[0].s_spn_values[vMPIndex]. ui8_new_error);
      
       //vTestA = (unsigned long) (s_BAM_Values[0].s_spn_values[0].ui32_spn);
       //vTestB = (unsigned long) (s_BAM_Values[0].s_spn_values[1].ui32_spn);
       //vTestC = (unsigned long) (s_BAM_Values[0].s_spn_values[2].ui32_spn);
       //vTestD = (unsigned long) (s_BAM_Values[0].s_spn_values[3].ui32_spn);
       //vTestE = (unsigned long) (s_BAM_Values[0].s_spn_values[4].ui32_spn);
       //vTestF = (unsigned long) (s_BAM_Values[0].s_spn_values[5].ui32_spn);
       
       As.CANclear_timer = 400;
       
   }
   else if (qNoDM1 == 0) 
   {
      vSPN_Display = (CAN_SPN_Least16_VALUE + (CAN_SPN_Most3_VALUE << 16)) ;
      vFMI_Display = (short) CAN_FMI_VALUE;
      As.CANclear_timer = 400;
   }
   else
   {
      if (As.CANclear_timer)
      {
        As.CANclear_timer--;
      }
      if (As.CANclear_timer == 0)
      {
        vSPN_Display = 0;
        vFMI_Display = 0;
      }
   }
   
  if ( As.MP_timer )
  {
    As.MP_timer--;
  } 
  else
  {
      if (vMPIndex < vSPNCount)
      {
        vMPIndex++; 
      }
      else
      {
        vMPIndex=0;
      }
      As.MP_timer = 800;
  }
  
               
   
} 
   
