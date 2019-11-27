/*
 * User_Low_Power.c
 *
 *  Created on: Apr 2, 2013
 *      Author: mikkelsenb
 */
/*Include Header Files */
#include "reserved.h"
#include "Prototypes.h"
#include "Prototypes_Low_Power.h"
#include "Constants.h"
#include "User_App.h"
#include "User_Low_Power.h"

uint8_t User_Low_Power(void)
{

/*
** ######################################################################################
** TODO: Add your code here for choosing when to shutdown to the low power state.
**       e.g. Monitor the wakeup pin and when it goes false, save your data and return 1
**       Note: When you return 1, user_app() will no longer be called
** ######################################################################################
*/
  if (I_Wakeup==0) 
 {
      tonShutdown_STATUS = TRUE;
			if (tonShutdown_VALUE >= 50) 
			{
			  return (1);
			}
 } 
 else
 {
     tonShutdown_STATUS = FALSE;
     tonShutdown_VALUE = 0;
  return (0); /*Return 0 to continue running, return 1 to shut down to low power state*/
 }

}
