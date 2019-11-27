/*
** ###################################################################
**     Filename  : User_Low_Power_Init.c
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User can initilize their low power settings
**          This function gets called once on startup prior to the main loop
**
**     (c) Copyright HED, inc. 2006-2008
**     HED, inc.
**     2120 Constitution Ave.
**     Hartford, WI 53027
**     United States
**     http      : www.hedonline.com
**     mail      : support@hedonline.com
** ###################################################################
*/

/* Include Header Files */
#include "reserved.h"
#include "Prototypes.h"
#include "Prototypes_Low_Power.h"
#include "Constants.h"
#include "User_App.h"
#include "User_Low_Power_Init.h"


void User_Low_Power_Init(void)
{
  /* Call "Set_Power_Mode" function to set the desired low power mode to enter */


  /* Call "Set_Wakeup_Modes" function to set the desired wake-up mode(s).
     These can be OR'd together for multiple wake-up modes
     (e.g. Set_Wakeup_Modes((wakeup_modes_t)(WAKEUP_PIN|WAKEUP_CAN1|WAKEUP_BUTTON1) */
		 Set_Wakeup_Modes((wakeup_modes_t)(WAKEUP_PIN));	

  /* Call "Set_Pin_Wakeup_Delay" function to set the delay in milliseconds for external pin wake-up
     (e.g. Set_Pin_Wakeup_Delay(50) would set a debounce delay of 50ms for the external pin */


  /* Call "Set_Button_Wakeup_Delay" function to set the delay in milliseconds for push-button wake-up
     (e.g. Set_Button_Wakeup_Delay(2000) would mean the user must push and hold the
           button for at least two seconds in order to wake up the module */
           
}

