/*
** ###################################################################
**     Filename  : ProtoTypes.h
**     Processor : Not applicable
**     FileFormat: V1.00
**     Date/Time : 07/11/08, 1:05
**     Abstract  :
**         This file contains all the function and structure prototypes that are required.
**
**     (c) Copyright HED, inc. 2006-2008
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

typedef unsigned char UINT8;
typedef   signed char INT8;
typedef unsigned int  UINT16;
typedef   signed int  INT16;
typedef unsigned long UINT32;
typedef   signed long INT32;
#include "typedefs.h"

/* standard commands for digital outputs */
#define OUTPUT_OFF                                   0, 0
#define OUTPUT_ON                                    1000, 0
#define OUTPUT_ON_FLASH                              1000, 1

/*Types of CAN message identifiers */
typedef enum
{
   STANDARD,
   EXTENDED
} Identifier_Type_;

/*Variables in a Can Message */
typedef struct
{
   UINT32 identifier;
   UINT8  data[8];
   UINT8  length;
   UINT8  type;
   UINT16 tsr;
} Can_Message_;

/*Variables in a J1708 Message */
typedef struct 
{
   UINT8 data[MAX_J1708_LENGTH];
   UINT8 length;
   UINT8 priority;
} J1708_Message_;

/* CAN Bus Status */
typedef enum
{
   CAN_OK_STATUS,
   CAN_WARNING_STATUS,
   CAN_ERROR_STATUS,
   CAN_BUSOFF_STATUS
} Can_Status_;

/*Type of Sci line */
typedef enum
{
   CAN_LINE,
   SERIAL_LINE_1,
   SERIAL_LINE_2,
   SERIAL_LINE_3,
} Serial_Lines_;

/* module modes  */
typedef enum
{
   MODULE_MISSING_STATE,
   MODULE_NEEDS_ASSIGNMENT_STATE,
   MODULE_WAKE_UP_STATE,
   MODULE_NEEDS_CONFIGS_STATE,
   MODULE_RUNNING_STATE,
   MODULE_IN_COMMFAIL_STATE,
   MODULE_GOT_SOFT_RESET_STATE,
   MODULE_IN_STUB_STATE,
   MODULE_NEEDS_SAVE_CONFIGS_STATE,
   MODULE_DISABLED
} Module_State_;

/* The different CAN states of the modules (master uses these to keep track of the modules) */
typedef enum
{
   SINGLE_CAN,
   DUAL_CAN_OK,
   DUAL_CAN_1_BAD,
   DUAL_CAN_2_BAD
} Can_State_;

/* input states */
typedef enum
{
   INPUT_OFF,
   INPUT_ON,
   INPUT_DISABLED,
   INPUT_ANALOG_OR_FREQ
} Input_State_;

/* Output Status States */
typedef enum
{
   STATUS_NORMAL,
   STATUS_OPEN,
   STATUS_GROUND,
   STATUS_BATTERY,
   STATUS_OVER_CURRENT,
   STATUS_GROUNDED,
   STATUS_STB_OR_OPEN,
   STATUS_OVER_UNDER_VOLTAGE,
   STATUS_OVER_TEMP,
   STATUS_GROUND_OPEN
} Output_Status_;

/* Diagnostic pull up modes */
typedef enum
{
   DPU_ALWAYS_OFF = 1,
   DPU_ALWAYS_ON,
   DPU_TOGGLE
} Dpu_Modes_;

/* Conductor connection modes */
typedef enum
{
   CONDUCTOR_NO_COMM_MODE,      /* Conductor is not connected */
   CONDUCTOR_CHANGE_COMM_MODE,  /* Conductor is in the process of connecting */
   CONDUCTOR_WAIT_MODE,         /* Conductor is in the process of connecting */
   CONDUCTOR_RUNNING_MODE,      /* Conductor is currently connected */
   CONDUCTOR_DEBUG_MODE         /* Conductor is connected and debugging */
} Conductor_Modes_;

/* Save user value type */
typedef enum
{
   SAVE_ALL_EEPROM = 1,         /* EEPROMs and Timers will be saved*/
   RELOAD_EEPROM,               /* Reads EEPROMs and Timers */
   RESTORE_DEFAULTS,            /* Restores EEPROMs and Timers to their defaults */
   EEPROM_SHUTDOWN,             /* EEPROMs with save on shutdown enabled */
   TIMER_SHUTDOWN,              /* Timers with save on shutdown enabled */
   EEPROM_TIMER_SHUTDOWN,       /* EEPROM and Timers with save on shutdown enabled */
   EEPROM_SINGLE,               /* Single EEPROM value saved */
   TIMER_SINGLE,                /* Single Timer value saved */
   SINGLE_VALUE,                /* Single EEPROM or Timer value saved, code figures out which type based on IO address */
} Save_Types_;
/* properties to setup the bam messages */
typedef struct
{
   UINT16     ui16_pgn;               
   UINT8      ui8_source_address;     
   UINT8      ui8_module_id;          
   UINT8      ui8_can_line;           
} BAM_Properties_;

/* all the values for a spn */
typedef struct
{
   UINT8      ui8_spn_state;          
   UINT32     ui32_spn;               
   UINT8      ui8_fmi;                
   UINT8      ui8_occurance_count;    
   UINT8      ui8_conversion_method;  
   UINT8      ui8_new_error;          
} BAM_Spn_Values_;

/* values for the user */
typedef struct
{
   UINT8             ui8_lamp_status;
   UINT8             ui8_lamp_flash;
   BAM_Spn_Values_   s_spn_values[NUMBER_SPN_PER_BAM];
} BAM_Values_;

/* values for the user */
typedef struct
{
   UINT16            ui16_analog_value;
   bool_t   				 available_analog_value_flag;	 /* if flag false, the analog value return invalid; if flag ture, the analog value return valid */
} Analog_Values_;

/* Defines of true and false */
#define TRUE                     1
#define FALSE                    0

/* Global variables used by the Firmware and User code */
/* Temperary variable to set the state machines, the actual state machine value is not updated until the end of the loop */
extern UINT16  StateMachineTempState[NUMBER_OF_STATE_MACHINES];

/* This is to set what SCI line the printf function sends the characters out on */
extern UINT8 SciLineForPrintf;

/* IOMap is where all the data items values are stored, depending on processor type it could move into paged memory */
#ifdef USE_PAGED_RAM 
   #pragma DATA_SEG __RPAGE_SEG PAGED_RAM_IO_MAP
#endif
extern UINT16 IOMap[IO_MAP_SIZE];                    

#ifdef USE_PAGED_RAM
   #pragma DATA_SEG __RPAGE_SEG PAGED_RAM_J1939_BAM
#endif

#if NUMBER_OF_BAM_MESSAGES > 0
extern BAM_Properties_ s_BAM_Properties[NUMBER_OF_BAM_MESSAGES];
extern BAM_Values_     s_BAM_Values[NUMBER_OF_BAM_MESSAGES];
extern uint8_t           ui8_Number_Of_J1939_BAM_Messages;
#endif

#ifdef USE_PAGED_RAM 
#pragma DATA_SEG DEFAULT
#endif

/* 
 * proto types of functions that may have to be called by the user 
 */

/* 
 * call this function to update an output command 
 * the module id and number can be replaced with the output #define in constants.h
 * value is the value that you want to set the output command to
 * flash is if you want the output to flash or not
 */
void Update_Output(UINT8 module_id, UINT8 number, UINT16 value, UINT8 flash);

/* 
 * call this function to update the heart beat
 * turn_on is the status of the heartbeat (1 = on, 0 = off, any else leaves it in its current state
 */
void Heart_Beat_Control(UINT8 turn_on);

/* 
 * call this function to send a can message
 * module_id is the module to send the message out on (0-F)
 * can_line is the value of the can line you want to send the message on (1-5)
 * can message is a structure that contains all the info about the can message
 * it will return the following
 *    0 = Message added to Transmit buffer
 *    1 = Transmit buffer is full, could not add
 */  
UINT8 Send_CAN_Message(UINT8 module_id, UINT8 can_line, Can_Message_ can_message);
 
/* 
 * call this function to send a J1708 message
 * j1708 message is a structure that contains all the info about the j1708 message
 * it will return the following
 *    0 = Message added to Transmit buffer
 *    1 = Transmit buffer is full, could not add
 */  
UINT8 WriteJ1708(J1708_Message_ j1708message);

/*
 * call this function to get the status of the CAN bus
 * can_line is which can line you want to check (1-5)
 * return the status (see enumeration for different modes)
 */
Can_Status_ Check_For_CAN_Status(UINT8 can_line);

/*
 * call this function to update the 5 volt supply or the output diagnostic mode
 * module_id = which module you want to update, you can use #define for module number in Constants.h
 * dpu = sets the mode of the diagnostic, see the enumberation
 * five volts = turns the 5 volt supply on and off, 0 = Off 1 = On
 */
void Update_Dpu_5v(UINT8 module_id, Dpu_Modes_ dpu, UINT8 five_volts);

/*
 * call this function to set the baudrate of the SCI line 
 * sci_line = the line of the module you want to modify
 * baud_rate = this is the baud rate that the SCI will be set to
 * 
 * NOTE:  The baud rate is defaulted to 9600
 *        All HED PC programs connection sequence start out at 9600
 *        If the baud rate is not at 9600 the HED tools will fail to connect
 */
void Init_SCI(UINT8 sci_line, UINT32 baud_rate);

/*
 * call this function to send a byte on the SCI 
 * sci_line = the line to send the byte on
 * data_byte = byte that to send
 * return = If the byte was added into the tx buffer (0= yes, 1 = no)
 */
UINT8 Send_SCI_Byte(UINT8 sci_line, UINT8 data_byte);

/*
 * call this function to see what the conductor communication status is
 * return = the status of Conductor
 */
UINT8 Get_Conductor_Status(void);

/*
 * call this function to see what the conductor access level is
 * return = the user's access level
 */
UINT8 Get_Conductor_Access_Level(void);

/*
 * Call this function to save values from Timers or EEPROM
 * Save_Type = Type of information to save EEEPROM, Timers, or Both
 * Value_Name = The name of Timer or EEPROM to be saved 
 * Value_Name needs to be a number from 0 - 65535
 */ 
void User_EEPROM_Timer(Save_Types_ Save_Type, UINT16 Value_Name);

/*
 * call this function to see what the firmware version number is
 * module_id is the module to send the message out on (0-F) 
 * return = the version number
 * example: version 2.01 will return 0x0201, version 3.20 will return 0x0320
 */
UINT16 Get_Firmware_Version(UINT8 module_id);

/*
 * call this function to see what the application version number is
 * return = the version number
 * example: version 03-01 will return 0x0301, version 00-10 will return 0x0010
 */
UINT16 Get_Application_Version(void);

/*
 * This function calculates the CRC for the memory between Start and Finish
 * returen the CRC value 
 */
UINT16 CRCcalc(UINT16 *far start, UINT16 *far finish);

/* This function interpolates between points (X1, Y1) and (X2, Y2). The input value passed in
 * should be between X1 and X2, however it is not necessary since the input is plugged into the equation of a line
 * which extends beyond the points (X1, Y1) and (X2, Y2). The calculation used here is derived from y = mx + b,
 * where the input is x, and points (X1, Y1) and (X2, Y2) are substituted into m and b
 */ 
INT16 Interpolate(INT16 si16_x_input, INT16 si16_x1, INT16 si16_x2, INT16 si16_y1, INT16 si16_y2);

/* This function is used to determine if the HED SCI packets are enabled or disabled 
 * Note: It will return 1(True) if disabled and a 0(False) if enabled
 * sci_line  = COM line being used to get status
 */
UINT8 GetSciStatus(Serial_Lines_ sci_line);

/* This function is used to disable the HED SCI packets and enabled the individual byte function.
 * Note: Disabling the HED SCI packets will prevent HED PC tools from connecting
 * sci_line  = COM line being used. If CAN is used sci_line = 0
 * status    = True will disable HED SCI, False will enable HED SCI
 */
void SetSciStatus(Serial_Lines_ sci_line, UINT8 status);

/* 
* call this function to read analog value of input
* software_input_number is the input software number of the input you want to read (since it is on master module it lines up with the IOMap address)
* frequency sets the amount of time the input is sampled over.  For example 50 Hz -> 20 msec, 100 Hz, 10 msec, 200 Hz 5 msec
* return the Analog_Values_ structure
* NOTE: if the frequency is set such that it takes longer to sample the input than the loop time, the previous value will be reported until the sampling is finished.
* In some cases the inputs on the module are run through a multiplexer, in these cases having one long sample time will affect all the inputs since the multiplexer 
* cannot be flipped until all the inputs have finished sampling
*/
Analog_Values_	Read_Analog_Value_Inputs(INT8 software_input_number, UINT16 frequency);

