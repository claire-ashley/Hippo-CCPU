/*
** ###################################################################
**     Filename  : User_Shutdown.c
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User can add code for when the module shuts down
**          This function gets called once a loop when unswitched battery is off
**             and switched battery is high
**          returns:
**                   0 = Don't shut off
**                   1 = Shut off
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
#include "user_shutdown.h"

UINT8 User_Shutdown(void)
{
   return(1);
}
