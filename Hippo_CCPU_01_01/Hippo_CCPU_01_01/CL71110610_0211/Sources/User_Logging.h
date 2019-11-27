/*
** ###################################################################
**     Filename  : User_Logging.h
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User application software is located
**          This function gets called once a loop
**
** ###################################################################
*/

#ifndef USER_LOGGING_H_
#define USER_LOGGING_H_

#define   MAX_NUMBER_OF_SAVED_ERRORS      1000
#define   NUMBER_OF_SAVED_ERRORS_ROWS     10
#define   NUMBER_OF_SAVED_ERRORS_COLUMNS  16
#define   NUMBER_OF_SAVED_ERRORS_TABLES   10

/*

    app_PrimaryErrorCodeInfo:	org = 0x000E0000,   len = 0x00020000

*/

/* Memory locations for the configuration chart */

#define     ERROR_CODE_FLASH_START_ADDRESS1                    0x007C0000       // 0xF08000 TO 0xF0BFFF; 
#define     ERROR_CODE_FLASH_END_ADDRESS1                      0x007C3FFF       
#define     ERROR_CODE_FLASH_START_ADDRESS2                    0x007C4000        // 0xF18000 TO 0xF1BFFF 
#define     ERROR_CODE_FLASH_END_ADDRESS2                      0x007C7FFF  



typedef enum
{
  UNDEFINED_SECTOR,
  SECTOR_ONE,
  SECTOR_TWO
} enum_Selected_Sector_;

/* 
 * Error Code structure for a single fault
 */

typedef struct
{
   uint16_t	ui16_Event;
   
   uint16_t	ui16_RTC_Month;
   uint16_t	ui16_RTC_Date;
   uint16_t	ui16_RTC_Hour;
   uint16_t	ui16_RTC_Minute;
   
   uint16_t	ui16_Tool;
   uint16_t	ui16_MaxFlow;
   uint16_t	ui16_MaxPSI;

} Single_Logged_Error_Code_Structure_ ;



/*
 * Function Prototype
 */

uint16_t Log_Error(Single_Logged_Error_Code_Structure_ s_Saved_Error);
void Delete_Logged_Errors(void);
void Read_Errors (void);
void Manage_Tables (void);


#endif /* USER_LOGGING_H_ */
