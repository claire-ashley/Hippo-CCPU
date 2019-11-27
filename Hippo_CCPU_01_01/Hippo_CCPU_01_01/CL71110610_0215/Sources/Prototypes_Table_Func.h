/*
** ###################################################################
**     Filename  : Prototypes_Table_Func.h
**     Processor : Not applicable
**     FileFormat: V1.00
**     Date/Time : 07/26/12, 1:05
**     Abstract  :
**         Functions for using the Chart Loader Feature.
**
**     (c) Copyright HED, inc. 2006-2012
**     HED, inc.
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

/******************************************************************************
Example for defining flash section for the chart to be stored in


** #########################################################################
**                            !!!  WARNING !!!
**     USE OF INCORRECT FLASH SECTORS CAN RESULT IN CORRUPTION OF SOFTWARE.
** #########################################################################


*******************************************************************************/

/*

      PAGE_E8_A     = READ_WRITE  0xE88000 TO 0xE8AFFF;          * Config Chart section for the Error Codes *
      PAGE_E8       = READ_ONLY   0xE8B000 TO 0xE8BFFF;          * Section reduced for the Config Chart *

*/

/******************************************************************************
Flash address offsets for chart data

All table cell locations are signed long values

Column 0 is the row header column to be used for locating the Row Input in the 
interpolation functions.

Interpolation functions assume that Row 0 is a column header row to be used for
locating the Column Input in the table interpolation function.

NOTE: Charts are Phrase Aligned (4 INTs) - so if the number of columns is not 
even, then an additional column will be "created" with data values of 0xFFFFFFFF

Terminology:
Chart Group  - a group of tables, up to 5 may be defined numbered 0 - 4
Chart Number - a table within a given Chart Group


*******************************************************************************/

#define     CONFIG_CHART_NUMBER_OF_COLUMNS_ADDRESS_OFFSET     0x00 
#define     CONFIG_CHART_NUMBER_OF_ROWS_ADDRESS_OFFSET        0x02
#define     CONFIG_CHART_NUMBER_OF_TABLES_ADDRESS_OFFSET      0x04

#define     DEVICE_TYPE_DIGIT_1_ADDRESS_OFFSET                0x08
#define     DEVICE_TYPE_DIGIT_2_ADDRESS_OFFSET                0x0A
#define     DEVICE_TYPE_DIGIT_3_ADDRESS_OFFSET                0x0C
#define     DEVICE_TYPE_DIGIT_4_ADDRESS_OFFSET                0x0E
#define     DEVICE_TYPE_DIGIT_5_ADDRESS_OFFSET                0x10
#define     DEVICE_TYPE_DIGIT_6_ADDRESS_OFFSET                0x12

#define     CHART_VERSION_DIGIT_1_ADDRESS_OFFSET              0x18
#define     CHART_VERSION_DIGIT_2_ADDRESS_OFFSET              0x1A
#define     CHART_VERSION_DIGIT_3_ADDRESS_OFFSET              0x1C
#define     CHART_VERSION_DIGIT_4_ADDRESS_OFFSET              0x1E

#define     SERIAL_NUMBER_DIGIT_1_ADDRESS_OFFSET              0x20
#define     SERIAL_NUMBER_DIGIT_2_ADDRESS_OFFSET              0x22
#define     SERIAL_NUMBER_DIGIT_3_ADDRESS_OFFSET              0x24
#define     SERIAL_NUMBER_DIGIT_4_ADDRESS_OFFSET              0x26

#define     CONFIG_CHART_CRC_ADDRESS_OFFSET                   0x28
#define     CONFIG_CHART_WRITE_RESULT_ADDRESS_OFFSET          0x30

#define     START_OF_FIRST_CONFIG_CHART_ADDRESS_OFFSET        0x38

/******************************************************************************
Enumerated values for chart loader functions
*******************************************************************************/

typedef enum
{
   WRITE_NOT_OK,
   WRITE_OK
} Write_Results_;

typedef enum
{
   CHART_LOCATION_UNDEFINED,
   LOADING_DISABLED,
   LOADING_ENABLED,
   LOADING_CHART
} ChartLoader_State_;

/******************************************************************************
Structures for chart loader functions
*******************************************************************************/

typedef struct
{
   unsigned char ui08_device_type[12];
} device_type_;

typedef struct
{
   unsigned char ui08_version_serial_type[8];
} version_serial_type_;

typedef struct
{
  unsigned int          number_of_columns;
  unsigned int          number_of_rows;
  unsigned int          number_of_tables;
} version_chart_information_;

typedef struct
{
  unsigned char         chart_loading_state;
  unsigned char         chart_uploading_state;
  unsigned char         chart_write_ok;
} chart_status_;

/******************************************************************************
Chart Loader function prototypes
*******************************************************************************/

/******************************************************************************
Function Name: Init_Chart_Loader
*******************************************************************************
  Description:  
    Function to initalize a give chart group
    Downloading of charts defaults to enabled on successful initialization
    Uploading of charts defaults to disabled on successful initialization

  Inputs:
    ui08_Chart_Group  - defines which of the chart groups being initialized; 
            Value of 255 clears all data (DOES NOT ERASE CHARTS)
    ptr_start         - pointer to starting memory address of this chart group
    ptr_end           - pointer to ending memory address of this chart group

*******************************************************************************/
void Init_Chart_Loader(unsigned char ui08_Chart_Group, unsigned int *far ptr_start, unsigned int *far ptr_end);

/******************************************************************************
Function Name: EraseCharts
*******************************************************************************
  Description:  
    Function to erase an entire chart group

  Inputs:
    ui08_Chart_Group  - defines which of the chart groups being erased

  Return Value:
    0 = Erase Successful
    1 = Erase Failed: ui08_Chart_Type greater then max number of chart types
    2 = Erase Failed: ui08_Chart_Type selects undefined chart type
    3 = Erase Failed: Flash erase failed

*******************************************************************************/
unsigned char EraseCharts(unsigned char ui08_Chart_Group);

/******************************************************************************
Function Name: GetChartStatus
*******************************************************************************
  Description:  
    Function to enable or disable the HED Chart Loader.

  Inputs:
    ui08_Chart_Group  - defines which of the chart groups being erased

  Return Value:
    chart_status_ Structure
      chart_loading_state:
        0 - Chart Location Undefined
        1 - Loading Disabled
        2 - Loading Enabled
        3 - Loading Chart
      chart_uploading_state:
        0 - Chart Location Undefined
        1 - Uploading Disabled
        2 - Uploading Enabled
        3 - Uploading Chart
      chart_write_ok:
        0 - WRITE_NOT_OK (No chart loaded; loading failed)
        1 - WRITE_OK (Chart loaded)

*******************************************************************************/
chart_status_ GetChartStatus(unsigned char ui08_Chart_Group);

/******************************************************************************
Function Name: SetChartStatus
*******************************************************************************
  Description:  
    Function to enable or disable the HED Chart Loader.

  Inputs:
    ui08_Chart_Group  - defines which of the chart groups being configured
    download_status   - FALSE (0) will disable HED Chart loading
                        TRUE  (1) will enable HED Chart loading
                        0xFF is no change
    upload_status     - FALSE (0) will disable HED Chart uploading
                        TRUE  (1) will enable HED Chart uploading
                        0xFF is no change
    compare_mask      - Used to enable, disable vehicle type compare when loading charts
                        NOTE: Only updated with a change to download_status
                        bits 0-11 is the mask for comparing (1 = check that digit)
                        bit 12 - UNUSED
                        bit 13-15 determine the Chart Group to compare to (must be less then 5)

  Return Value:
    Low Nibble is download (bits 0-3):
      0 (status changed)
      1 (status not changed - no change requested)
      2 (status not changed - can't enable or disable during chart downloading/uploading)
      3 (invalid status value)
      4 (invalid Chart Group)

    High Nibble is download (bits 4-7):
      0 (status changed)
      1 (status not changed - no change requested)
      2 (status not changed - can't enable or disable during chart downloading/uploading)
      3 (invalid status value)
      4 (invalid Chart Group)

*******************************************************************************/
unsigned char SetChartStatus(unsigned char ui08_Chart_Group, unsigned char download_status, unsigned char up_status, unsigned int compare_mask);

/******************************************************************************
Function Name: Get_Chart_Information
*******************************************************************************
  Description:  
    Function to look-up the chart information for a given chart group

  Inputs:
    ui08_Chart_Group  - defines which of the chart groups being queried

  Return Value:
    A structure containing

      number_of_columns - int containing the number of columns per chart
      number_of_rows - int containing the number of row per chart
      number_of_tables - int containing the number of charts in this group

*******************************************************************************/
version_chart_information_ Get_Chart_Information(unsigned char ui08_Chart_Group);

/******************************************************************************
Function Name: Get_Device_Type
*******************************************************************************
  Description:  
    Function to look-up the device type for a given chart group

  Inputs:
    ui08_Chart_Group  - defines which of the chart groups being queried

  Return Value:
    An array of bytes (12 in total) containing the ASCII values of the device 
    type
*******************************************************************************/
device_type_ Get_Device_Type(unsigned char ui08_Chart_Group);

/******************************************************************************
Function Name: Get_Version_Number
*******************************************************************************
  Description:  
    Function to look-up the version number for a given chart group

  Inputs:
    ui08_Chart_Group  - defines which of the chart groups being queried

  Return Value:
    An array of bytes (8 in total) containing the ASCII values of the version 
    number
*******************************************************************************/
version_serial_type_ Get_Version_Number(unsigned char ui08_Chart_Group);

/******************************************************************************
Function Name: Get_Serial_Number
*******************************************************************************
  Description:  
    Function to look-up the serial number for a given chart group

  Inputs:
    ui08_Chart_Group  - defines which of the chart groups being queried

  Return Value:
    An array of bytes (8 in total) containing the ASCII values of the serial 
    number
*******************************************************************************/
version_serial_type_ Get_Serial_Number(unsigned char ui08_Chart_Group);

/******************************************************************************
Function Name: Chart_Cell_Lookup
*******************************************************************************
  Description:  
    Function to look-up the value of a specific cell within a chart

  Inputs:
    ui08_Chart_Group  - defines which of the chart groups being used
    ui08_Chart_Number - chart number within that group (0 based number)
    ui16_Chart_Row    - row number of desired cell look-up (0 based number)
    ui16_Chart_Column - colum number of desired cell look-up (0 based number)

  Return Value:
    A float value that is the desired cell value
*******************************************************************************/
signed long int Chart_Cell_Lookup(unsigned char ui08_Chart_Group, unsigned char ui08_Chart_Number, unsigned int ui16_Chart_Row, unsigned int ui16_Chart_Column);

/******************************************************************************
Function Name: Chart_Interpolated_Lookup
*******************************************************************************
  Description:  
    Function to look-up a chart value by interpolating between known chart entries
    Acts as a one-dimensional look-up  - comparing values in a known column; 
      and interpolating between rows
    This function requires that the chart have at least 2 data rows and that the 
      ui16_First_Data_Row is NOT the last row

  Inputs:
    ui08_Chart_Group            - defines which of the chart groups being used (0-4)
    ui08_Chart_Number           - chart number within that group (0 based number)
    ui16_Chart_Reference_Column - column within the chart used for the row selection (0 based number)
    ui16_Chart_Column           - column within that chart used for result interpolation (0 based number)
    f_Row_Input                 - X input value
    ui16_First_Data_Row         - defines which row is the 1st row containing data values, all rows after this 
                                  row are considered data items as well (0 based number)

  Return Value:
    A float value that is the interpolated look-up
*******************************************************************************/
float Column_Interpolated_Lookup(unsigned char ui08_Chart_Group, unsigned char ui08_Chart_Number, unsigned int ui16_Chart_Reference_Column, unsigned int ui16_Chart_Column, float f_Row_Input, unsigned int ui16_First_Data_Row);

/******************************************************************************
Function Name: Table_Interpolated_Lookup
*******************************************************************************
  Description:  
    Function to look-up a chart value by interpolating between known chart entries
    Acts as a two-dimensional look-up interoplating between rows and columns

    Row 0 and Column 0 are a "header" row/column used for indexing, all other locations
      are assumed to be data items

  Inputs:
    ui08_Chart_Group            - defines which of the chart groups being used (0-4)
    ui08_Chart_Number           - chart number within that group (0 based number)
    f_Row_Input                 - X input value
    f_Column_Input              - Y input value

  Return Value:
    A float value that is the interpolated look-up
*******************************************************************************/
float Table_Interpolated_Lookup(unsigned char ui08_Chart_Group, unsigned char ui08_Chart_Number, float f_Row_Input, float f_Column_Input);

/******************************************************************************
Function Name: Stepped_Interpolated_Lookup
*******************************************************************************
  Description:  
    Function to look-up a chart value by interpolating between known chart entries
    Acts as a stepped two-dimensional look-up interoplating between rows and using 
    either the lessor or greater of two column values based on the ui08_Direction input

  Inputs:
    ui08_Chart_Group    - defines which of the chart groups being used (0-4)
    ui08_Chart_Number   - chart number within that group (0 based number)
    f_Row_Input         - X input value
    f_Column_Input      - Y input value
    f_Transition_Margin - Value used to create a range around each column 
                            for the determination of f_Column_Input being "in" the column
    ui08_Direction      - 0 returns the lesser of the two column results; all other values
                            result in the greater of the column values being returned

  Return Value:
    A float value that is the interpolated look-up
*******************************************************************************/
float Stepped_Interpolated_Lookup(unsigned char ui08_Chart_Group, unsigned char ui08_Chart_Number, float f_Row_Input, float f_Column_Input, float f_Transition_Margin, unsigned char ui08_Direction);