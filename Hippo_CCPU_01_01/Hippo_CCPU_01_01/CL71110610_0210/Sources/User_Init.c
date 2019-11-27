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
   SciLineForPrintf = 1;
   (void) printf("hello world");
   
   V_Screen_Number = Screen_Screen4;
   
   Update_Output (doStart   , OUTPUT_OFF);
   As.RC1_com_timer = 100;
   As.RC2_com_timer = 100;
   As.Eng_com_timer = 100;
   As.CAN_TX_100ms_timer = 10;
   As.CAN_TX_1s_timer = 10;
   As.InhibitCAN = 1;
   tonServScreen_VALUE = 8;
}

