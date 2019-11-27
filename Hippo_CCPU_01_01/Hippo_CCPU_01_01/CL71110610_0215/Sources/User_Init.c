/*
** ###################################################################
**     Filename  : User_Init.c
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User can initilize their global variables
**          This function gets called once on startup prior to the main loop
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
#include <stdio.h>
#include "user_app.h"


void User_Init(void)
{
  /*Start up on service screen*/ 
   V_Screen_Number = Screen_Screen1;
   
   /*Initialize engine power*/
   Update_Output (doIgnition   , OUTPUT_ON);
   Update_Output (doStart   , OUTPUT_OFF);
      
   /*Initialize Timers*/
   As.RC1_com_timer = 100;
   As.RC2_com_timer = 100;
   As.CAN_TX_100ms_timer = 10;
   As.CAN_TX_1s_timer = 10;
   As.MP_timer = 800;
   As.Shutdown_timer = 500;
   As.RunCountReset_timer = 6000;
   As.ClearLog_timer = 500;
   As.CANclear_timer = 400;
   As.NewRead_timer = 300;
   As.DeleteLog_timer  = 1000;
   As.DM3_timer = 1000;
   As.DM11_timer = 1000;
   As.SysWarnON_timer = 500;
	 As.SysWarnOFF_timer = 500;
	 As.RegenReq_timer = 350;
	 As.ResetCond_timer = 3000;
   tonServScreen_VALUE = 12;
   tonShutdown_VALUE = 0;
   tonWarnDisable_VALUE = 14;
   
   /*Initialize USB Variables*/
      V_USB_Select = 0;
   V_Execute_USB_Update = 0;
   
   /*Initialize Flash Variables*/
   vTable = eeEvent;
   vTable /= 10; 
   vReadChart2 = eeChart2;
   
   if ((eeEvent == 0) && (eeChart2 == 0))
   {
      Delete_Logged_Errors();
   }
   else
   { 
   }
   
   /*Initialize Flash Variables*/ 
      As.InhibitCAN = 1;
   
}

