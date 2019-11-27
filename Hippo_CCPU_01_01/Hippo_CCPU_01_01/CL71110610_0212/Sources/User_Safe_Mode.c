/*
** ###################################################################
**     Filename  : User_Safe_Mode.c
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User can add code for when in safe mode
**          This function gets called once a loop when in safe mode
**
**     (c) Copyright HED, inc. 2006-2009
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
#include "user_app.h"
#include "user_safe_mode.h"

void User_Safe_Mode(void)
{
   #pragma DATA_SEG __RPAGE_SEG PAGED_RAM_USER
      static UINT8  uint8_heartbeat_count = (UINT8) 0;
   #pragma DATA_SEG DEFAULT
   
   /*
   ** ###################################################################
   ** HeartBeat                   
   ** ###################################################################
   */
   if(uint8_heartbeat_count < ONE_HUNDRED_MSECS)
   {
      Heart_Beat_Control((UINT8) 1);
      uint8_heartbeat_count++;
   }
   else if(uint8_heartbeat_count < TWO_HUNDRED_MSECS) 
   {
      Heart_Beat_Control((UINT8) 0);
      uint8_heartbeat_count++;
   }
 
   if(uint8_heartbeat_count >= TWO_HUNDRED_MSECS)
   {
      uint8_heartbeat_count = 0;
   }
}
