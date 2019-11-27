/*
** ###################################################################
**     Filename  : User_App.h
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
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

/* 
 * These numbers are based off a 10 msec loop time, 
 * if you change the loop time you will need to adjust these as well
 */
typedef enum
{
   ONE_HUNDRED_MSECS = 10,
   TWO_HUNDRED_MSECS = 20,
   FIVE_HUNDRED_MSECS = 50,
   ONE_SECOND = 100,
   THREE_SECONDS = 300,
   FIVE_SECONDS = 500
} enum_Loop_Time_;

/* 
 * Sample structure shown
 */
 
 
 
#define BUTTON_01    0x0001
#define BUTTON_02    0x0002
#define BUTTON_03    0x0004
#define BUTTON_04    0x0008

#define BUTTON_UP    0x0010
#define BUTTON_DOWN  0x0020
#define BUTTON_LEFT  0x0040
#define BUTTON_RIGHT 0x0080
#define BUTTON_CENTER 0x0100

#define COMMAND_WIDGET_BUSY  0x4000

#define     CAN_Tx_1                          1
#define     CAN_Tx_2                          2

#define     MESSAGE_FILLER                    0xFF
#define     FILL2BITS                         0x03

#define     TSC1_TX                           0x0C000028
#define     Y_DPFIF_TX                        0x0CFF1828
#define     Y_STP_TX                          0x0CFF1D28
#define     Y_EC_TX                           0x0CFF1C28
#define     HR_REQ_TX                         0x18EA0028
#define     DM3                               0x0CFECC28
#define     DM11                              0x0CFED328
#define     RC1TX                             0x18FF8C28
#define     RC2TX                             0x18FF8D28

#define SET_TIME_YEAR_TO_STRUCT_OFFSET                  1900






typedef struct
{
   UINT16  temp;
   float  flow1x10;
   float  flow2x10;
   UINT16  flow1UpDeb;
   UINT16  flow1DnDeb;
   UINT16  flow2UpDeb;
   UINT16  flow2DnDeb;
   UINT16  RC1_com_timer;
   UINT16  RC2_com_timer;
   UINT16  CAN_TX_100ms_timer;
   UINT16  CAN_TX_1s_timer;
   UINT16  hr100_reset_timer;
   UINT16  hr250_reset_timer;
   UINT16  Shutdown_timer;
   UINT16  RunCountReset_timer;
   UINT16  CANclear_timer;
   UINT16  ClearLog_timer;
   UINT16  HydStop_timer;
   UINT16  SysWarnON_timer;
   UINT16  SysWarnOFF_timer;
   UINT16  RegenReq_timer;
   UINT16  ResetCond_timer;
   UINT16  flow1Y1;
   UINT16  flow1Y2;        
   UINT8   readlatch;
   UINT8   readlatch2;
   UINT8   RedLight;
   UINT8   AmberLight;
   UINT8   RegenLight;
   UINT8   HEGTLight;
   UINT8   InhibitLight;
   UINT8   deletelatch;
   UINT8   writelatch;
   UINT16  flow2Y2;
   UINT8   NewRead ;
   UINT16  NewRead_timer ;
   UINT16  MaxTable ;
   UINT16  DeleteLog_timer ;
   float   SysWarning ;
   UINT16  DM3_timer ;
   UINT16  DM11_timer ;
   UINT8   sendDM3;
   UINT8   sendDM11 ;
   UINT16  SysWarnRequest ;
   UINT8   InhibitCAN ;
   UINT16  MP_timer;
   UINT16  DM1_timer;
   UINT16  BAM_timer;
   float   BasicFlow1;
   float   PcompFlow1;
   float   BasicFlow2;
   float   PcompFlow2;
   uint16_t TMR_USB_Load_Execute_Delay;
   
   
   	/* System Timers */
	uint16_t  ui16_Power_Up_Timer;

	/* Button Data */
	bool_t    b_Button_Latch;
	uint16_t  ui16_Button_Timer;

	/* Screen Data */
	uint16_t  ui16_Last_Screen;

	/* Software Update Screen Data */
	uint16_t  ui16_Software_Update_State;
	uint16_t  ui16_Software_Update_Text_Timer;
	uint32_t  ui32_FTDI_Programming_Timer;

	/* Version Data */
	uint8_t	  ui08_Firmware_Major_Version;
	uint8_t	  ui08_Firmware_Minor_Version;
	uint8_t	  ui08_App_Major_Version;
	uint8_t	  ui08_App_Minor_Version;

	/* Logging Data */
	uint8_t	  ui08_Device_Name[12];
	uint8_t	  ui08_Serial_Number[8];

} 

App_Structure_;


/* 
 * Defining proto type so other files can use this structure
 * using the #pragma to put in into the paged ram user section
 */
#pragma DATA_SEG __RPAGE_SEG PAGED_RAM_USER_APP
   extern App_Structure_ As;
#pragma DATA_SEG DEFAULT

/*
 * Function Prototype
 */
 
void Screen_Control(void);
void Sensor_Control(void);
void User_App(void);
void Engine_Control(void);
void Radio_Control (void);
void Hydraulic_Control(void);
void Send_CAN(void);
void Warning_Ribbons (void); 
void Logging(void); 
void Settings(void); 
                 
uint16_t Process_Buttons(void);
uint16_t Check_Button(uint16_t ui16_button, uint16_t ui16_button_mask);

void Process_Screen_1(uint16_t ui16_buttons_pressed); 	   
void Process_Screen_2(uint16_t ui16_buttons_pressed); 	   
void Process_Screen_3(uint16_t ui16_buttons_pressed); 	   
void Process_Screen_4(uint16_t ui16_buttons_pressed); 
void Process_Screen_5(uint16_t ui16_buttons_pressed); 
void Process_Screen_6(uint16_t ui16_buttons_pressed);  
 


