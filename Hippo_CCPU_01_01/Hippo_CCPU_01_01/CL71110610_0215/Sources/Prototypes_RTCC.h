/*
** ###################################################################
**     Filename  : Prototypes_RTCC.h
**     Processor : Not applicable
**     FileFormat: V2.00
**     Abstract  :
**         This file contains all the function and structure prototypes 
       for supporting a RTCC Real-time clock calendar - if supported by module hardware
**
**     (c) Copyright HED,Inc. 2006-2012
**     HED,Inc.
**     2120 Constitution Ave.
**     Hartford, WI 53089
**     United States
**     http      : www.hedonline.com
**     mail      : support@hedonline.com
** #########################################################################
**                            !!!  WARNING !!!
**     ALTERING THIS FILE IN ANY WAY MAY CAUSE PERSONAL INJURY AND/OR DEATH.
** #########################################################################
*/

#ifndef PROTOTYPES_RTCC_H_
#define PROTOTYPES_RTCC_H_

#include <time.h>
#include "typedefs.h"

/* return for set RTCC status */
typedef enum
{
   RTCC_SET_WAS_SUCCESSFUL,
   RTCC_SET_HAD_INVALID_VALUE,
   RTCC_SET_WAS_UNSUCCESSFUL,
   RTCC_SET_NOT_AVAIALABLE,
   RTCC_SET_WAITING_RESPONCE      
} Rtcc_Set_Status_t;

/*
 * #Function only used by particular modules# 
 * 
 *This function gets the current year
 */
int GetRTCCActualYear(void);  
                         
/* This function gets the Years since 1900*/
int GetRTCCAnsiCYear(void);

/* This function gets the current month 0 = January ... 11 = December*/
int GetRTCCMonth(void); 

/* This function gets the current day of the month  1 - 31*/
int GetRTCCDay(void);   

/* This function gets the current day of the week  0 = Sunday 6 = Saturday*/
int GetRTCCDOW(void);   

/* This function gets the current hour 0-23*/
int GetRTCCHour(void);   

/* This function gets the current minute 0-59*/
int GetRTCCMinute(void); 

/* This function gets the current second 0-59*/
int GetRTCCSecond(void); 

/* 
 * This function gets current time as stored by the Real Time Clock Calendar 
 * ClockCalendar    time structure provided by <time.h> that gets filled with current RTCC value
 * returns the stored time and date
 *
 */
struct tm Get_DateTime (void);

/* 
 * This function sets current time as stored by the Real Time Clock Calendar 
 * Sets the time and saves it
 * returns false if there was error
 */
bool_t Set_DateTime (struct tm timeDate);

/* Set the alarm on the Real Time Clock chip with all applicable fields from tm struct
 * return: TRUE - alarm was set successfully
 *         FALSE - error when setting alarm
 * NOTE: not every module clock supports alarms on a specific date/month/year. See module datasheet for more information.
 */
bool_t Set_RTCCAlarm(struct tm alarm_date_time); 

/*
 * Returns the status of setting the RTCC on a display 
 */
Rtcc_Set_Status_t GetSetRtccStatus(void);

#endif /* PROTOTYPES_RTCC_H_ */
