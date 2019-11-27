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

#define     CAN_Tx_1                          1
#define     CAN_Tx_2                          2

#define     MESSAGE_FILLER                    0xFF
#define     FILL2BITS                         0x03

#define     TSC1_TX                           0x0C000028
#define     Y_DPFIF_TX                        0x0CFF1828
#define     Y_STP_TX                          0x0CFF1D28
#define     Y_EC_TX                           0x0CFF1C28
#define     HR_REQ_TX                         0x18EA0028


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
   UINT16  Eng_com_timer;
   UINT16  CAN_TX_100ms_timer;
   UINT16  CAN_TX_1s_timer;
   UINT16   hr100_reset_timer;
   UINT16   hr250_reset_timer;
   UINT16  flow1X1;
   UINT16  flow1X2;
   UINT16  flow1Y1;
   UINT16  flow1Y2;        
   UINT16  flow2X1;
   UINT16  flow2X2;
   UINT16  flow2Y1;
   UINT16  flow2Y2;
   UINT16  rDenom ;
   UINT16  rTerm1 ;
   UINT16  rTerm2 ;
   UINT16  rTerm3 ;
   UINT16  rTerm4 ;
   UINT16  CC1ma11 ;
   UINT16  CC1ma12 ;
   UINT16  CC1ma21 ;
   UINT16  CC1ma22 ;
   UINT16  CC1ma ;
   UINT16  rDenom_2 ;
   UINT16  rTerm1_2 ;
   UINT16  rTerm2_2 ;
   UINT16  rTerm3_2 ;
   UINT16  rTerm4_2 ;
   UINT16  CC2ma ;
   UINT8   InhibitCAN ;

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
                 
uint16_t Process_Buttons(void);
uint16_t Check_Button(uint16_t ui16_button, uint16_t ui16_button_mask);

void Process_Screen_1(uint16_t ui16_buttons_pressed); 	   
void Process_Screen_2(uint16_t ui16_buttons_pressed); 	   
void Process_Screen_3(uint16_t ui16_buttons_pressed); 	   
void Process_Screen_4(uint16_t ui16_buttons_pressed); 
