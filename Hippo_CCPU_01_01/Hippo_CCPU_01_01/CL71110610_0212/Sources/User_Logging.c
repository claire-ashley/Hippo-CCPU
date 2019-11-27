/*
** ###################################################################
**     Filename  : User_Logging.c
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User application software is located
**          This function gets called once a loop
**
**		copyright Hydro Electronic Devices, Inc.
**
** ###################################################################
*/

/* Include Header Files */
#include "reserved.h"
#include "typedefs.h"
#include "Prototypes.h"
#include "Constants.h"
#include "User_App.h"
#include <math.h>
#include "User_Logging.h"
#include "Prototypes_Table_Func.h"
#include "Prototypes_Flash.h"

/* Internal Function Prototypes */


 /******************************************************************************
 Function Name: Log_Error
 *******************************************************************************
 Description:  Writes the error to the logged error flash section

 *******************************************************************************/

void Manage_Tables (void)
{   
  if ((eeEvent > 999) && (eeChart2 == 0))
  {
     eeChart2 = 1;
     Delete_Logged_Errors();
  }
  else if ((eeEvent > 999) && (eeChart2 == 1))
  {
    eeChart2 = 0;
    Delete_Logged_Errors();
  }
}

/* Internal Function Prototypes */


 /******************************************************************************
 Function Name: Log_Error
 *******************************************************************************
 Description:  Writes the error to the logged error flash section

 *******************************************************************************/
uint16_t Log_Error(Single_Logged_Error_Code_Structure_ s_Saved_Error)
{

	vuint8_t	ui08_Result;
	vuint8_t	ui08_Return;
	vuint32_t	ui32_Current_Data_Address_Offset;
	vuint32_t	ui32_write_address;
	vuint16_t	ui16_Write_Data[16];
	vuint32_t	ui32_Address_of_Write_Data_Start;
	vuint32_t	ui32_Address_of_Write_Data_End;
	
	ui08_Return = 0;
	
	/* Save Error to Flash */
	/* Get addresses for current Write sector */
	
	if (eeChart2)
	{
  	ui32_Address_of_Write_Data_Start = (uint32_t)(ERROR_CODE_FLASH_START_ADDRESS2);
	  ui32_Address_of_Write_Data_End   = (uint32_t)(ERROR_CODE_FLASH_END_ADDRESS2);
	}
	else
	{
		ui32_Address_of_Write_Data_Start = (uint32_t)(ERROR_CODE_FLASH_START_ADDRESS1);
	  ui32_Address_of_Write_Data_End   = (uint32_t)(ERROR_CODE_FLASH_END_ADDRESS1);
	}
	
	
	/* Find the start of the data */
	ui32_write_address  = (uint32_t)(ui32_Address_of_Write_Data_Start);
	//ui32_write_address += START_OF_FIRST_CONFIG_CHART_ADDRESS_OFFSET;
	
	/* Save new logged errors to flash */
	ui32_Current_Data_Address_Offset  = eeEvent;
	ui32_Current_Data_Address_Offset *= NUMBER_OF_SAVED_ERRORS_COLUMNS;
	ui32_write_address += ui32_Current_Data_Address_Offset;
	           
	//vTestC = ui32_write_address;

	/* Make sure write location is within desired sector */
	if ( ui32_write_address < ui32_Address_of_Write_Data_End )
	{
		/* Save new logged errors to flash */
		ui16_Write_Data[0] = s_Saved_Error.ui16_Event;
		ui16_Write_Data[1] = s_Saved_Error.ui16_RTC_Month;
		ui16_Write_Data[2] = s_Saved_Error.ui16_RTC_Date;
		ui16_Write_Data[3] = s_Saved_Error.ui16_RTC_Hour;
		
		ui16_Write_Data[4] = s_Saved_Error.ui16_RTC_Minute;
		ui16_Write_Data[5] = s_Saved_Error.ui16_Tool;
		ui16_Write_Data[6] = s_Saved_Error.ui16_MaxFlow;

		ui16_Write_Data[7]   = s_Saved_Error.ui16_MaxPSI;
		
		arrayTestWr[0] = ui16_Write_Data[0];
	  arrayTestWr[1] = ui16_Write_Data[1];
	  arrayTestWr[2] = ui16_Write_Data[2];
	  arrayTestWr[3] = ui16_Write_Data[3];
	  arrayTestWr[4] = ui16_Write_Data[4];
	  arrayTestWr[5] = ui16_Write_Data[5];
	  arrayTestWr[6] = ui16_Write_Data[6];
	  arrayTestWr[7] = ui16_Write_Data[7];
	   
    ui08_Result      = FlashWriteBlock(&ui16_Write_Data[0], (unsigned int *far)ui32_write_address, 8);
		
		
		ui08_Return |= ui08_Result;  /*Result = 1 if success*/
		
		vTest3 =   ui08_Result;
		vTest5 ++;


	} 
	else 
	{
		ui08_Return = (uint8_t)0x00;
	}
	
	
return(ui08_Return);

} /* End Log_Error() */



 /******************************************************************************
 Function Name: Delete_Logged_Errors
 *******************************************************************************
 Description:  Deletes the logged error structure in flash

 *******************************************************************************/
void Delete_Logged_Errors(void)
{
  
  vuint8_t      ui08_Result;
  vuint32_t	ui32_Address_of_Delete_Data_Start;
  vuint32_t	ui32_Address_of_Delete_Data_End;
  
  if (eeChart2)
  {
      ui32_Address_of_Delete_Data_Start = ERROR_CODE_FLASH_START_ADDRESS2;
      ui32_Address_of_Delete_Data_End = ERROR_CODE_FLASH_END_ADDRESS2;
  }
  else
  {
      ui32_Address_of_Delete_Data_Start = ERROR_CODE_FLASH_START_ADDRESS1;
      ui32_Address_of_Delete_Data_End = ERROR_CODE_FLASH_END_ADDRESS1;
  }

//  ui08_Result  = FlashEraseSector ((UINT16 *far) ui32_Address_of_Delete_Data_Start);
  ui08_Result  = FlashEraseBlock((UINT16 *far) ui32_Address_of_Delete_Data_Start, (UINT16 *far) ui32_Address_of_Delete_Data_End);

  eeEvent = 0;
 
 vTest4 =   ui32_Address_of_Delete_Data_Start;
  vTest1 ++;
                                                                                           


} /* End Delete_Logged_Errors() */


 /******************************************************************************
 Function Name: Read_Logged_Errors
 *******************************************************************************
 Description:  Reads the logged error structure in flash

 *******************************************************************************/

void Read_Errors (void)
{
    vuint32_t ui32_read_address0;
    vuint32_t ui32_read_address1;
    vuint32_t ui32_read_address2;
    vuint32_t ui32_read_address3;
    vuint32_t ui32_read_address4;
    vuint32_t ui32_read_address5;
    vuint32_t ui32_read_address6;
    vuint32_t ui32_read_address7;
    
    uint8_t   i;
    uint32_t  position;
    uint16_t  data0;
    uint16_t  data1;
    uint16_t  data2;
    uint16_t  data3;
    uint16_t  data4;
    uint16_t  data5;
    uint16_t  data6;
    uint16_t  data7;
    
    if (vReadChart2 > 0)
    {
      ui32_read_address0 = (uint32_t) (ERROR_CODE_FLASH_START_ADDRESS2);
    }
    else
    {
       ui32_read_address0 = (uint32_t) (ERROR_CODE_FLASH_START_ADDRESS1);
    }
 
    ui32_read_address1 = (uint32_t) (ui32_read_address0);
    ui32_read_address1 += 2;

    ui32_read_address2 = (uint32_t) (ui32_read_address1);
    ui32_read_address2 += 2;

    ui32_read_address3 = (uint32_t) (ui32_read_address2);
    ui32_read_address3 += 2;

    ui32_read_address4 = (uint32_t) (ui32_read_address3);    
    ui32_read_address4 += 2;

    ui32_read_address5 = (uint32_t) (ui32_read_address4);
    ui32_read_address5 += 2;

    ui32_read_address6 = (uint32_t) (ui32_read_address5);
    ui32_read_address6 += 2;

    ui32_read_address7 = (uint32_t) (ui32_read_address6);
    ui32_read_address7 += 2;

    As.MaxTable =  eeEvent;
    As.MaxTable /=  10;
    

    for (i=0; i <= 9; i++)
    {            
       position =  vTable;
       position *=  10;
       position +=  i;
       position *=  16;
       vTestD = position;
        
    
        data0 = *((uint16_t * far)(ui32_read_address0 + position)); 
        data1 = *((uint16_t * far)(ui32_read_address1 + position)); 
        data2 = *((uint16_t * far)(ui32_read_address2 + position)); 
        data3 = *((uint16_t * far)(ui32_read_address3 + position)); 
        data4 = *((uint16_t * far)(ui32_read_address4 + position)); 
        data5 = *((uint16_t * far)(ui32_read_address5 + position)); 
        data6 = *((uint16_t * far)(ui32_read_address6 + position)); 
        data7 = *((uint16_t * far)(ui32_read_address7 + position)); 

        vTestB  =  (ui32_read_address7+position);
        vTestE += 1;
        
        arrayEvent[i] = data0;
        arrayMonth[i] = data1;    
        arrayDate[i]  = data2;
        arrayHour[i]   = data3;                  
        arrayMinute[i] = data4;                  
        arrayTool[i]   = data5;                    
        arrayFlow[i]  = data6;                
        arrayPSI[i]  = data7;
        
        if (arrayEvent[i] == 65535)
        {
          arrayEvent[i] = 0;
        }
        if (arrayDate[i] == 65535)
        {
          arrayDate[i] = 0;
        }
        if (arrayHour[i] == 65535)
        {
          arrayHour[i] = 0;
        }
         if (arrayMinute[i] == 65535)
        {
          arrayMinute[i] = 0;
        }
         if (arrayTool[i] == 65535)
        {
          arrayTool[i] = 0;
        }
         if (arrayFlow[i] == 65535)
        {
          arrayFlow[i] = 0;
        }
         if (arrayPSI[i] == 65535)
        {
          arrayPSI[i] = 0;
        }
        
     } 
     

}


 
