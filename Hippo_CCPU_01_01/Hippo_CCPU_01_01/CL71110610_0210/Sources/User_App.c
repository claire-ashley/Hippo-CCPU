/*
** ###################################################################
**     Filename  : User_App.c
**     Processor : Not applicable
**     FileFormat: V1.00
**     Abstract  :
**          This is where the User application software is located
**          This function gets called once a loop
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
#include "user_app.h"
#include <math.h>

#pragma DATA_SEG __RPAGE_SEG PAGED_RAM_USER_APP
   App_Structure_ As;
#pragma DATA_SEG DEFAULT

void User_App(void)
{
   #pragma DATA_SEG __RPAGE_SEG PAGED_RAM_USER
      static UINT8  uint8_heartbeat_count = (UINT8) 0;
   #pragma DATA_SEG DEFAULT
   
   /*
   ** ###################################################################
   ** HeartBeat                   
   ** ###################################################################
   */
   if(uint8_heartbeat_count < FIVE_HUNDRED_MSECS)
   {
      Heart_Beat_Control((UINT8) 1);
      uint8_heartbeat_count++;
   }
   else if(uint8_heartbeat_count < ONE_SECOND) 
   {
      Heart_Beat_Control((UINT8) 0);
      uint8_heartbeat_count++;
   }
   
   if(uint8_heartbeat_count >= ONE_SECOND)
   {
      uint8_heartbeat_count = 0;
   }
   
       pwmBackLight_VALUE = 700;
       Screen_Control();
       Sensor_Control();
       Engine_Control();
       Radio_Control();
       Hydraulic_Control();
       Warning_Ribbons();
       Send_CAN();

}

/******************************           SCREEN AND BUTTON MANAGEMENT       ************************************/
/****************************************************************************************************************/

void Screen_Control(void)
{
   uint16_t ui16_buttons_pressed = Process_Buttons();
      
    /* ScreenSequenceTimer*/
   if (tonServScreen_VALUE > 0)
   {
	   tonServScreen_STATUS = TRUE;
   }
   else
   {
	   tonServScreen_STATUS = FALSE;
	   if ((V_Screen_Number == 4) && (qScreen1Shot == FALSE))
	   {
		   qScreen1Shot = TRUE;
		   V_Screen_Number = Screen_Screen1; 
	   }
 
   }
   switch(V_Screen_Number)
   {
      case Screen_Screen1:
           Process_Screen_1(ui16_buttons_pressed); 	   
    	   break;
      case Screen_Screen2:
          Process_Screen_2(ui16_buttons_pressed); 	   
    	   break;
      case Screen_Screen3:
          Process_Screen_3(ui16_buttons_pressed); 	   
    	   break;
      case Screen_Screen4:
          Process_Screen_4(ui16_buttons_pressed); 	   
    	   break;
      default:
    	    V_Screen_Number = Screen_Screen4;
    	   break;
   }
}

uint16_t Process_Buttons(void)
{
   uint16_t ui16_buttons_pressed = 0;
   
   ui16_buttons_pressed |= Check_Button(I_Button_01   , BUTTON_01   );
   ui16_buttons_pressed |= Check_Button(I_Button_02   , BUTTON_02   );
   ui16_buttons_pressed |= Check_Button(I_Button_03   , BUTTON_03   );
   ui16_buttons_pressed |= Check_Button(I_Button_04   , BUTTON_04   );
                                                                  
   ui16_buttons_pressed |= Check_Button(I_Button_Up   , BUTTON_UP   );
   ui16_buttons_pressed |= Check_Button(I_Button_Down , BUTTON_DOWN );
   ui16_buttons_pressed |= Check_Button(I_Button_Left , BUTTON_LEFT );
   ui16_buttons_pressed |= Check_Button(I_Button_Right, BUTTON_RIGHT);
               
   ui16_buttons_pressed |= Check_Button(I_Button_Center, BUTTON_CENTER);
   

   return ui16_buttons_pressed; 
}

uint16_t Check_Button(uint16_t ui16_button, uint16_t ui16_button_mask)
{
   static uint16_t ui16_buttons = 0;
   uint16_t ui16_buttons_pressed = 0;
   
   if(ui16_button == INPUT_ON)
   {
	   if((ui16_buttons & ui16_button_mask) == ui16_button_mask)
	   {
	      /* Do Nothing button was already processed */
	   }
	   else
	   {
		   ui16_buttons         |= ui16_button_mask;
		   ui16_buttons_pressed |= ui16_button_mask;
	   }
   }
   else
   {   
	   if((ui16_buttons & ui16_button_mask) == ui16_button_mask)
	   {
		   ui16_buttons &= ~ui16_button_mask;
	   }
	   else
	   {
		   /* Do Nothing button was already cleared */
	   }
   }
   return ui16_buttons_pressed;
}

/*MAIN SCREEN 1*/
void Process_Screen_1(uint16_t ui16_buttons_pressed) 	   
{
	if((ui16_buttons_pressed & BUTTON_01) == BUTTON_01)
	{
	  if ((vTool1Key == 0) && (vNavKey ==1))
	  {
	      vTool1Key = 1;
	  } 
	  else
	  {
	      vTool1Key = 0;
	  } 
	}
	else if((ui16_buttons_pressed & BUTTON_02) == BUTTON_02)
	{
	  if (qEngineRunning == 1)
	  {
	    qDisplayStop = 1;
	    qDisplayStart = 0;
	  }
	  else
	  {
	    qDisplayStop = 0;
	    qDisplayStart = 1;
	  }
	    
	}
	else if((ui16_buttons_pressed & BUTTON_03) == BUTTON_03)
	{
		  if ((qIdleSet == 0) && (vNavKey ==1))
	  {
	      qIdleSet = 1;
	  } 
	  else
	  {
	      qIdleSet = 0;
	  } 
  }
	else if((ui16_buttons_pressed & BUTTON_04) == BUTTON_04)
	{
		  if ((vTool2Key == 0) && (vNavKey ==1))
	  {
	      vTool2Key = 1;
	  } 
	  else
	  {
	      vTool2Key = 0;
	  } 
	}
	else if(((ui16_buttons_pressed & BUTTON_LEFT)   == BUTTON_LEFT) && (vNavKey ==1) )		
	{
	   V_Screen_Number = Screen_Screen4;   
	}
	else if(((ui16_buttons_pressed & BUTTON_RIGHT) == BUTTON_RIGHT ) && (vNavKey ==1) )	
	{       
	    V_Screen_Number = Screen_Screen2;                                
	}
	else if(((ui16_buttons_pressed & BUTTON_UP) == BUTTON_UP ) && (qIdleSet == 1) && (vIdleMode < 2))	
	{       
	    vIdleMode++;                                
	}
	else if(((ui16_buttons_pressed & BUTTON_DOWN) == BUTTON_DOWN ) && (qIdleSet == 1) && (vIdleMode > 0))	
	{       
	    vIdleMode--;                                
	}
	
	if ((vTool1Key == 1) ||  (vTool2Key == 1) || (qIdleSet ==1))
  {
    vNavKey = 0;
    qSetKey = 1;
  }
   else
  {
    vNavKey = 1;
    qSetKey = 0;
  }
  
  	if  (I_Button_02 == 0)   /*Reset Engine Start when key is released*/
	{
	    qDisplayStart = 0;
	}

}


/*ENGINE SCREEN 2*/
void Process_Screen_2(uint16_t ui16_buttons_pressed) 	   
{
	if((ui16_buttons_pressed & BUTTON_01) == BUTTON_01)
	{
	}
	else if((ui16_buttons_pressed & BUTTON_02) == BUTTON_02)
	{
	    qRegenReq = 1;
	}
	else if((ui16_buttons_pressed & BUTTON_03) == BUTTON_03)
	{
	    if (qInhibit == 0)
	    {
	        qInhibit = 1;
	        As.InhibitCAN = 0;
	    }
	    else
	    {
	      qInhibit = 0;
	      As.InhibitCAN = 1;
	    }
  }
	else if((ui16_buttons_pressed & BUTTON_04) == BUTTON_04)
	{
	}
	else if((ui16_buttons_pressed & BUTTON_CENTER)   == BUTTON_CENTER)		
	{
	     V_Screen_Number = Screen_Screen1;
	}
	else if((ui16_buttons_pressed & BUTTON_LEFT)   == BUTTON_LEFT)		
	{
	   V_Screen_Number = Screen_Screen1;   
	}
	else if((ui16_buttons_pressed & BUTTON_RIGHT) == BUTTON_RIGHT )
	{       
	    V_Screen_Number = Screen_Screen3; 
	}
	
	if  (I_Button_02 == 0)   /*Reset Regen Request when key is released*/
	{
	    qRegenReq = 0;
	}
}

/*DIAGNOSTICS SCREEN 3*/
void Process_Screen_3(uint16_t ui16_buttons_pressed) 	   
{
	if((ui16_buttons_pressed & BUTTON_01) == BUTTON_01)
	{
	}
	else if((ui16_buttons_pressed & BUTTON_02) == BUTTON_02)
	{
	}
	else if((ui16_buttons_pressed & BUTTON_03) == BUTTON_03)
	{
	}
	else if((ui16_buttons_pressed & BUTTON_04) == BUTTON_04)
	{
	}
 	else if((ui16_buttons_pressed & BUTTON_CENTER)   == BUTTON_CENTER)		
	{
	     V_Screen_Number = Screen_Screen1;
	}
	else if((ui16_buttons_pressed & BUTTON_LEFT)   == BUTTON_LEFT)		
	{
	   V_Screen_Number = Screen_Screen2;   
	}
	else if((ui16_buttons_pressed & BUTTON_RIGHT) == BUTTON_RIGHT )
	{       
	    V_Screen_Number = Screen_Screen4; 
	}
}

/*SERVICE SCREEN 4*/
void Process_Screen_4(uint16_t ui16_buttons_pressed) 	   
{
	if((ui16_buttons_pressed & BUTTON_01) == BUTTON_01)
	{
	   if (As.hr100_reset_timer)
	   {
	       As.hr100_reset_timer--;
	   }
	   else
	   {
	      qReset100 = 1;
	   }
	}
	else if((ui16_buttons_pressed & BUTTON_02) == BUTTON_02)
	{
	}
	else if((ui16_buttons_pressed & BUTTON_03) == BUTTON_03)
	{
	}
	else if((ui16_buttons_pressed & BUTTON_04) == BUTTON_04)
	{
	 if (As.hr250_reset_timer)
	   {
	       As.hr250_reset_timer--;
	   }
	   else
	   {
	      qReset250 = 1;
	   }
	}
	else if((ui16_buttons_pressed & BUTTON_CENTER)   == BUTTON_CENTER)		
	{
	     V_Screen_Number = Screen_Screen1;
	}
	else if((ui16_buttons_pressed & BUTTON_LEFT)   == BUTTON_LEFT)		
	{
	   V_Screen_Number = Screen_Screen3;   
	}
	else if((ui16_buttons_pressed & BUTTON_RIGHT) == BUTTON_RIGHT )
	{       
	    V_Screen_Number = Screen_Screen1; 
	}                                          

	if  (I_Button_01 == 0)   /*Reset service reset when key is released*/
	{
	    qReset100 = 0;
	    As.hr100_reset_timer = 500;
	}
	
		if  (I_Button_04 == 0)   /*Reset service reset when key is released*/
	{
	    qReset250 = 0;
	    As.hr250_reset_timer = 500;
	}
}

/****************************************        SENSOR SETUP        *********************************************/
/*****************************************************************************************************************/


void Sensor_Control(void)
{

/***************************PRESSURE*************************************/

 /* Calculate Pump Hydraulic Pressure*/
	if ((ai_P_Psi >= 500) && (ai_P_Psi <= 4600))       /*Allow calculation if within normal range*/
	{
	
		vPsiP = (short) (0.75*ai_P_Psi - 375);
	
		qPSI_P_Fault = FALSE;
	}
	else if (ai_P_Psi > 4600)   /*Set max and fault if highter than normal range*/
	{	
		vPsiP = 3000;
		qPSI_P_Fault = TRUE;
	}
	else if ((ai_P_Psi < 500) && (ai_P_Psi> 450))  /*Set min (0) if slightly under range*/
		{	
		vPsiP = 0;
		qPSI_P_Fault = FALSE;
	}
	else         /*Set a fault if outside normal range*/
	{	
		vPsiP = 0;
		qPSI_P_Fault = TRUE;
	}
	
	/*Set High Hydraulic Pressure Fault*/
	
	if ((vPsiP >= 2500) && (tonServScreen_VALUE == 0))
	{
		qHighHydPSI = TRUE;
		tonHiPSIReset_STATUS = FALSE;
		tonHiPSIReset_VALUE = 5;
	} 
	else
	{
		tonHiPSIReset_STATUS = TRUE;
		if (tonHiPSIReset_VALUE == 0)
		{
			qHighHydPSI = FALSE;
		}
	}
	
	/*Set Low Hydraulic Pressure Fault*/
	
	if ((vPsiP <= 100) && (vRPM >= 500))
	{
	    qLowHydPSI = TRUE;
	    tonLoPSIReset_STATUS = FALSE;
		  tonLoPSIReset_VALUE = 5;
	} 
	else
		{
		tonLoPSIReset_STATUS = TRUE;
		if (tonLoPSIReset_VALUE == 0)
		{
			qLowHydPSI = FALSE;
		}
	}
	
	 /* Calculate Load Sense (LS) Hydraulic Pressure*/
	if ((ai_LS_Psi >= 500) && (ai_LS_Psi <= 4600))       /*Allow calculation if within normal range*/
	{
	
		vPsiLS = (short) (0.75*ai_LS_Psi - 375);
	
		qPSI_LS_Fault = FALSE;
	}
	else if (ai_LS_Psi > 4600)   /*Set max and fault if highter than normal range*/
	{	
		vPsiLS = 3000;
		qPSI_LS_Fault = TRUE;
	}
	else if ((ai_LS_Psi < 500) && (ai_LS_Psi> 450))  /*Set min (0) if slightly under range*/
		{	
		vPsiLS = 0;
		qPSI_LS_Fault = FALSE;
	}
	else         /*Set a fault if outside normal range*/
	{	
		vPsiLS = 0;
		qPSI_LS_Fault = TRUE;
	}
	
	/***************************TEMPERATURE*************************************/
	
		/* Calculate Hydraulic Temp at P port*/
				if ((ai_P_Temp >= 1039) && (ai_P_Temp <= 4600))   /*Negative numbers will not be displayed*/
				{
					vTempP = (short) (0.07425*ai_P_Temp - 77.125);
					qTemp_P_Fault = FALSE;
				}
				else if ((ai_P_Temp > 4600))
				{
					vTempP = 257;
					qTemp_P_Fault = TRUE;
				}
				else if ((ai_P_Temp < 1039) && (ai_P_Psi> 450))  /*Set min (0) if slightly under range*/
				{	
					vTempP = 0;
					qTemp_P_Fault = FALSE;
				}
				else
				{	
					vTempP = 0;
					qTemp_P_Fault = TRUE;
				}
				
				/*Set Hyd Over Temperature - */
				
				if ((vTempP >= 210) && (tonServScreen_VALUE == 0))
				{
					qHighHydTemp = TRUE;
					tonHighTReset_STATUS = FALSE;
					tonHighTReset_VALUE = 5;
				}
				else
				{
					tonHighTReset_STATUS = TRUE;
					if (tonHighTReset_VALUE == 0)
					{
						qHighHydTemp = FALSE;
					}
				}
				
						/* Calculate Hydraulic Temp at LS port*/
				if ((ai_LS_Temp >= 1039) && (ai_LS_Temp <= 4600))   /*Negative numbers will not be displayed*/
				{
					vTempLS = (short) (0.07425*ai_LS_Temp - 77.125);
					qTemp_LS_Fault = FALSE;
				}
				else if ((ai_LS_Temp > 4600))
				{
					vTempLS = 257;
					qTemp_LS_Fault = TRUE;
				}
				else if ((ai_LS_Temp < 1039) && (ai_LS_Psi> 450))  /*Set min (0) if slightly under range*/
				{	
					vTempLS = 0;
					qTemp_LS_Fault = FALSE;
				}
				else
				{	
					vTempLS = 0;
					qTemp_LS_Fault = TRUE;
				}
				
	/***************************LEVEL*************************************/
		
	/* Calculate Fuel Level*/
		if ((ai_Fuel_Level >= 15) && (ai_Fuel_Level <= 240))
		{
			vFuelLevel = (short) (115.942-0.48309*ai_Fuel_Level);
			qFuelFault = FALSE;
		}
		else if (ai_Fuel_Level < 15)
		{
			vFuelLevel = 109;
			qFuelFault = TRUE;
		}
		else if ((ai_Fuel_Level > 240) && (ai_Fuel_Level <= 270))
		{	
			vFuelLevel = 0;
			qFuelFault = FALSE;
		}
		else
		{	
			vFuelLevel = 0;
			qFuelFault = TRUE;
		}
		
	/*Set Low Fuel Level*/
		
		if (vFuelLevel <= 10)
		{
			tonLowFuelDebounce_STATUS = TRUE;
			if (tonLowFuelDebounce_VALUE == 0)
			{
				qLowFuel = TRUE;
			}
			else
			{
				qLowFuel = FALSE;
			}
		}
		else if (vFuelLevel >= 15)		
		{
			tonLowFuelDebounce_STATUS = FALSE;
			tonLowFuelDebounce_VALUE = 5;
			qLowFuel = FALSE;
		}
		
			/* Calculate Hydraulic Oil Level*/
		if ((ai_Hyd_Level >= 15) && (ai_Hyd_Level <= 240))
		{
			vHydLevel = (short) (115.942-0.48309*ai_Hyd_Level);
			qHydLevelFault = FALSE;
		}
		else if (ai_Hyd_Level < 15)
		{
			vHydLevel = 109;
			qHydLevelFault = TRUE;
		}
		else if ((ai_Hyd_Level > 240) && (ai_Hyd_Level <= 270))
		{	
			vHydLevel = 0;
			qHydLevelFault = FALSE;
		}
		else
		{	
			vHydLevel = 0;
			qHydLevelFault = TRUE;
		}
		
	/*Set Low Hydraulic Oil Level*/
		
		if (vHydLevel <= 10)
		{
			tonHydLevDebounce_STATUS = TRUE;
			if (tonHydLevDebounce_VALUE == 0)
			{
				qLowHydOil = TRUE;
			}
			else
			{
				qLowHydOil = FALSE;
			}
		}
		else if (vHydLevel >= 15)		
		{
			tonHydLevDebounce_STATUS = FALSE;
			tonHydLevDebounce_VALUE = 5;
			qLowHydOil = FALSE;
		}
}


/*************************************          RADIO CONTROL        ********************************************/
/****************************************************************************************************************/  
  

void Radio_Control (void)
{
//#define CAN_Key1_1_Start_VALUE           IOMap[110]      /*Range 0 - 250*/
//#define CAN_Key1_2_Stop_VALUE            IOMap[111]      /*Range 0 - 250*/
//#define CAN_Key1_3_Up_VALUE              IOMap[112]      /*Range 0 - 250*/
//#define CAN_Key1_4_Dn_VALUE              IOMap[113]      /*Range 0 - 250*/
//#define CAN_Key2_1_Start_VALUE           IOMap[114]      /*Range 0 - 250*/
//#define CAN_Key2_2_Stop_VALUE            IOMap[115]      /*Range 0 - 250*/
//#define CAN_Key2_3_Up_VALUE              IOMap[116]      /*Range 0 - 250*/
//#define CAN_Key2_4_Dn_VALUE              IOMap[117]      /*Range 0 - 250*/
//#define CAN_RC1_Data_VALUE               IOMap[122]      /*Range 0 - 3*/
//#define CAN_RC1_Estop_VALUE              IOMap[123]      /*Range 0 - 3*/
//#define CAN_RC1_Start_VALUE              IOMap[124]      /*Range 0 - 3*/
//#define CAN_RC2_Data_VALUE               IOMap[125]      /*Range 0 - 3*/
//#define CAN_RC2_Estop_VALUE              IOMap[126]      /*Range 0 - 3*/
//#define CAN_RC2_Start_VALUE              IOMap[127]      /*Range 0 - 3*/


  /*****************RADIO CONTROL TOOL 1******************/
  
  
  /*RC ACTIVE AND ESTOP*/
  if  ((CAN_RC1_Data_VALUE == 1) &&  (CAN_RC1_Estop_VALUE == 1)  &&  (CAN_RC1_Start_VALUE == 1))
  {
    qRC1Active = 1;
    qRC1Estop = 0;
  }
  
  if ((qRC1Active == 1) && ((CAN_RC1_Data_VALUE == 0)||(CAN_RC1_Estop_VALUE == 0)))
  {
    qRC1Active = 1;
    qRC1Estop = 1;
  }
  
  if ((CAN_Key1_1_Start_VALUE >= 50) && (CAN_RC1_Data_VALUE == 1))         /*START*/
  {
    qRC1Start = 1;
  }
  else
  {
    qRC1Start = 0;
  }                                                                                                                               
    
  if ((CAN_Key1_2_Stop_VALUE >= 50) && (CAN_RC1_Data_VALUE == 1))          /*STOP*/
  {
    qRC1Stop = 1;
  }
  else
  {
    qRC1Stop = 0;
  }
  
  if ((CAN_Key1_3_Up_VALUE >= 50) && (CAN_RC1_Data_VALUE == 1))            /*UP*/
  {
    qRC1Up = 1;
  }
  else
  {
    qRC1Up = 0;
  }
  
  if ((CAN_Key1_4_Dn_VALUE >= 50) && (CAN_RC1_Data_VALUE == 1))            /*DOWN*/
  {
    qRC1Down = 1;
  }
  else
  {
    qRC1Down = 0;
  }
  
   /*****************RADIO CONTROL TOOL 2******************/
  
  
  /*RC ACTIVE AND ESTOP*/
  
  if  ((CAN_RC2_Data_VALUE == 1) &&  (CAN_RC2_Estop_VALUE == 1)  &&  (CAN_RC2_Start_VALUE == 1))
  {
    qRC2Active = 1;
    qRC2Estop = 0;
  }
  
  if ((qRC2Active == 1) && ((CAN_RC2_Data_VALUE == 0)||(CAN_RC2_Estop_VALUE == 0)))
  {
    qRC2Active = 1;
    qRC2Estop = 1;
  }
  
  if ((CAN_Key2_1_Start_VALUE >= 50) && (CAN_RC2_Data_VALUE == 1))      /*START*/
  {
    qRC2Start = 1;
  }
  else
  {
    qRC2Start = 0;
  }
    
  if ((CAN_Key2_2_Stop_VALUE >= 50) && (CAN_RC2_Data_VALUE == 1))  /*STOP*/
  {
       
    qRC2Stop = 1;
  }
  else
  {
    qRC2Stop = 0;
  }
  
  if ((CAN_Key2_3_Up_VALUE >= 50) && (CAN_RC2_Data_VALUE == 1))         /*UP*/
  {
    qRC2Up = 1;
  }
  else
  {
    qRC2Up = 0;
  }
  
  if ((CAN_Key2_4_Dn_VALUE >= 50) && (CAN_RC2_Data_VALUE == 1))          /*DOWN*/
  {
    qRC2Down = 1;
  }
  else
  {
    qRC2Down = 0;
  }


}

/***************************************           ENGINE        ************************************************/
/****************************************************************************************************************/


void Engine_Control (void)
{
    
  /*Calculate Engine Water Temp*/ 
    
    
    if (CAN_CoolT_VALUE  >=40)         /*Gauge starts at 0,so any negative values will show 0*/
    {
       vWaterT = (short) (((CAN_CoolT_VALUE - 40) *1.8)+32);
    } 
    else
    {
       vWaterT = 0;
    }
    
    
    /*Calculate Engine RPM and set Engine Running*/ 
    
    vRPM = (short) (CAN_RPM_VALUE * 0.125);
    if (vRPM >= 500)
    {
       qEngineRunning = 1;
    }
    else
    {
       qEngineRunning = 0;
    }
                                                            
    
    /*Set Idle Modes*/
    
      switch(vIdleMode)
      {
        case 0:                        /*Automatic Mode - High idle if load sense pressure*/
           if (vPsiLS > 10)
            {
              qHighIdle = 1;
            }
            else
            {
              qHighIdle = 0;
            }
    	   break;
        case 1:                       /*Manual Low Idle*/
            qHighIdle = 0;	   
    	   break;
        case 2:                       /*Manual High Idle*/
          qHighIdle = 1;	   
    	   break;
        default:
    	    qHighIdle = 0;
    	   break;
      }
      
      if (qHighIdle == 1)     /*Set engine speed request to engine, 1/8 RPM/bit*/
      {
        vReqEngSpeed = 2600*8;
      }
      else
      {
        vReqEngSpeed = 750*8;
      }
      
      
      
      /*Calulate Fault Codes*/
      
      
      vSPN_Display = (CAN_SPN_Least16_VALUE + (CAN_SPN_Most3_VALUE << 16)) ;
      vFMI_Display = (short) CAN_FMI_VALUE;
      
      
      /*Start/Stop*/
      
       if ((qRC1Stop == 1) || (qRC2Stop == 1) || (qRC1Estop == 1) || (qRC2Estop == 1) || (qDisplayStop == 1))
      {
        qEngineStop = 1;
       Update_Output (doStart   , OUTPUT_OFF);
        
      }
      else if (((qRC1Estop == 0) && (qRC2Estop == 0) && (tonServScreen_VALUE == 0)) &&
      ((qRC1Start == 1) || (qRC2Start == 1) || (qDisplayStart == 1)))
      {
         qEngineStop = 0;
         Update_Output (doStart   , OUTPUT_ON); 
      }
      else
      {
         qEngineStop = 0;
        Update_Output (doStart   , OUTPUT_OFF); 
      } 
      
      /*Engine Hours and Service Hours*/
      
      vEngHours = (long) (CAN_EngHours_VALUE * 0.5);   /* Eng hours in 1/10 hour*/
      
      if (qReset100)
      {
         ee100HR =  (vEngHours + 1000); /* Eng hours in 1/10 hour*/
         qReset100 = 0;
         qService100 = 0;
      }
      
      if (qReset250)
      {
         ee250HR =  (vEngHours + 2500);  /* Eng hours in 1/10 hour*/
         qReset250 = 0;
         qService250 = 0;
      }
      
      if  (vEngHours > ee100HR)
      {
        qService100 = 1;
      }
      
      if  (vEngHours > ee250HR)
      {
        qService250 = 1;
      }
      
      /*Regen Interlock Output*/
       if ((ccFlow1_VALUE) || (ccFlow2_VALUE))
        {
          Update_Output (doRegInterlock   , OUTPUT_OFF);
        }
        else
        {
    	    Update_Output (doRegInterlock   , OUTPUT_ON);
        }
      
      
   
      
      
}     


/***************************************        HYDRAULIC CONTROL       **********************************************/
/****************************************************************************************************************/
		
void Hydraulic_Control (void)
{

    /*Timer for INC/DEC when buttons are held*/
    tonFlowIncDec_STATUS=TRUE;
       
    
    /***************Tool Circuit 1*******************/    
   
      if (
        (((I_Button_Up==TRUE) && (V_Screen_Number == Screen_Screen1) && (vTool1Key == 1))|| (qRC1Up == 1)) 
        && (qUp1shot == 0) && (I_Button_Down==FALSE))
      {
         if (vFlow1 < 300)
         {
          vFlow1++ ;
         }
         qUp1shot =1;
      }
      else if (
      (((I_Button_Up==TRUE) && (V_Screen_Number == Screen_Screen1) && (vTool1Key == 1))|| (qRC1Up == 1))
      && (I_Button_Down==FALSE))
      {
         if (As.flow1UpDeb > 0)
         {
             As.flow1UpDeb-- ;
         }
         if ((As.flow1UpDeb == 0) &&  (tonFlowIncDec_VALUE ==0))
         {
            if (vFlow1 < 300)
            {
              vFlow1++ ;
            }
         }
       }
       else
       {
        qUp1shot = 0;
        As.flow1UpDeb = 80;
       }
       
      if (
        (((I_Button_Down==TRUE) && (V_Screen_Number == Screen_Screen1) && (vTool1Key == 1)) || (qRC1Down == 1)) 
         && (qDown1Shot == 0))
      {
         if (vFlow1 > 0)
         {
          vFlow1-- ;
         }
         qDown1Shot =1;
      }
      else if  (((I_Button_Down==TRUE) && (V_Screen_Number == Screen_Screen1) && (vTool1Key == 1)) || (qRC1Down == 1)) 
      {
         if (As.flow1DnDeb > 0)
         {
             As.flow1DnDeb-- ;
         }
         if ((As.flow1DnDeb == 0) &&  (tonFlowIncDec_VALUE ==0))
         {
            if (vFlow1 > 0)
            {
              vFlow1-- ;
            }
         }
       }
       else
       {
        qDown1Shot = 0;
        As.flow1DnDeb = 80;
       }
       
        /***************Tool Circuit 2*******************/    
   
      if (
        (((I_Button_Up==TRUE) && (V_Screen_Number == Screen_Screen1) && (vTool2Key == 1))|| (qRC2Up == 1)) 
        && (qUp1Shot2 == 0) && (I_Button_Down==FALSE))
      {
         if (vFlow2 < 300)
         {
          vFlow2++ ;
         }
         qUp1Shot2 =1;
      }
      else if (
      (((I_Button_Up==TRUE) && (V_Screen_Number == Screen_Screen1) && (vTool2Key == 1))|| (qRC2Up == 1))
      && (I_Button_Down==FALSE))
      {
         if (As.flow2UpDeb > 0)
         {
             As.flow2UpDeb-- ;
         }
         if ((As.flow2UpDeb == 0) &&  (tonFlowIncDec_VALUE ==0))
         {
            if (vFlow2 < 300)
            {
              vFlow2++ ;
            }
         }
       }
       else
       {
        qUp1Shot2 = 0;
        As.flow2UpDeb = 80;
       }
       
      if (
        (((I_Button_Down==TRUE) && (V_Screen_Number == Screen_Screen1) && (vTool2Key == 1)) || (qRC2Down == 1)) 
         && (qDown1Shot2 == 0))
      {
         if (vFlow2 > 0)
         {
          vFlow2-- ;
         }
         qDown1Shot2 =1;
      }
      else if  (((I_Button_Down==TRUE) && (V_Screen_Number == Screen_Screen1) && (vTool2Key == 1)) || (qRC2Down == 1)) 
      {
         if (As.flow2DnDeb > 0)
         {
             As.flow2DnDeb-- ;
         }
         if ((As.flow2DnDeb == 0) &&  (tonFlowIncDec_VALUE ==0))
         {
            if (vFlow2 > 0)
            {
              vFlow2-- ;
            }
         }
       }
       else
       {
        qDown1Shot2 = 0;
        As.flow2DnDeb = 80;
       }
    
         
    if (tonFlowIncDec_VALUE ==0)
    {
         tonFlowIncDec_VALUE =4;
    }
    
  /*Calculate Pressure Differential*/
    
   vPresDiff = 200; /*vPsiP - vPsiLS - 40; */
   


 As.flow1Y1 = 150;
 As.flow1Y2 = 300;
  
  if (vFlow1 < 42)
  {
    As.flow1X1 = 0;
    As.flow1X2 = 42;
    As.CC1ma11 = 500;
    As.CC1ma12 = 500;
    As.CC1ma21 = 850;
    As.CC1ma22 = 800;
    
    
  }
  else
  {
    As.flow1X1 = 42;
    As.flow1X2 = 336;
    As.CC1ma11 = 850;
    As.CC1ma12 = 800;
    As.CC1ma21 = 1270;
    As.CC1ma22 = 1170;
    
  }

  As.rDenom = (As.flow1X2-As.flow1X1)*(As.flow1Y2-As.flow1Y1);
  As.rTerm1 = (As.flow1X2-vFlow1)*(As.flow1Y2-vFlow1);
  As.rTerm2 = (vFlow1 - As.flow1X1)*(As.flow1Y2-vFlow1);
  As.rTerm3 = (As.flow1X2-vFlow1)*(vFlow1-As.flow1Y1);
  As.rTerm4 = (vFlow1 - As.flow1X1)*(vFlow1-As.flow1Y1);
  As.CC1ma = ((As.rTerm1*As.CC1ma11)+(As.rTerm2*As.CC1ma21)+(As.rTerm3*As.CC1ma12)+(As.rTerm4*As.CC1ma22))/As.rDenom;
  
  /*ccFlow1_VALUE  =  As.CC1ma;*/
  
   Update_Output (ccFlow1   ,(vFlow1*10), 0 );
   Update_Output (ccFlow2  ,(vFlow2*10), 0 );
     
  /*Control bypass valves*/
  if (ccFlow1_VALUE> 0)
  {
     	Update_Output (doBypass1   , OUTPUT_OFF);
  }
  else
  {
    	Update_Output (doBypass1   , OUTPUT_ON);
  }
  
  if (ccFlow2_VALUE > 0)
  {
     	Update_Output (doBypass2   , OUTPUT_OFF);
  }
  else
  {
    	Update_Output (doBypass2   , OUTPUT_ON);
  }

	/*Turn on hydraulic cooler at 105F */
	if ((qEngineRunning == FALSE)||(vTempP <= 95))
	{
		Update_Output (doCooler   , OUTPUT_OFF);
	}
	else if ((vTempP >= 105) && (qEngineRunning == TRUE))
	{
		Update_Output (doCooler   , OUTPUT_ON);
	} 
}

/******************************           Warning Ribbons / Fault Handling       ********************************/
/****************************************************************************************************************/

void Warning_Ribbons( void ) 
{ 

  
  /*Set RC1 Com Stat*/
  if (qRC1Fault)
  {
     vRC1ComStat = 0;
  }
  else if (CAN_RC1_Estop_VALUE == 1)
  {
      vRC1ComStat = 4;
  }
  else
  {
      vRC1ComStat = 9;
  }
  
  /*Set RC2 Com Stat*/
  
   if (qRC2Fault)
  {
     vRC2ComStat = 0;
  }
  else if (CAN_RC2_Estop_VALUE == 1)
  {
      vRC2ComStat = 4;
  }
  else
  {
      vRC2ComStat = 9;
  }
  
   /*Set Eng Com Stat*/
  
   if (qEngComFault)
  {
     vECUStat = 0;
  }
  else
  {
      vECUStat = 4;
  }
  
  

    /*Cooling Fan Status*/
	if (doCooler_STATUS == 4)
	{
		vCoolerStat = 2;
	}
	else if (doCooler_STATUS > 0)
	{
		vCoolerStat = 1;
	}
	else
	{
		vCoolerStat = 0;
	}
	
	   /*Bypass Valve 1 Status*/
	if (doBypass1_STATUS == 4)
	{
		vBypass1Stat = 2;
	}
	else if (doBypass1_STATUS > 0)
	{
		vBypass1Stat = 1;
	}
	else
	{
		vBypass1Stat = 0;
	}
	
		   /*Bypass Valve 2 Status*/
	if (doBypass2_STATUS == 4)
	{
		vBypass2Stat = 2;
	}
	else if (doBypass2_STATUS > 0)
	{
		vBypass2Stat = 1;
	}
	else
	{
		vBypass2Stat = 0;
	}
	
			   /*Start Output Status*/
	if (doStart_STATUS == 4)
	{
		vStartStat = 2;
	}
	else if (doStart_STATUS > 0)
	{
		vStartStat = 1;
	}
	else
	{
		vStartStat = 0;
	}
	
				   /*Allow Regen Status*/
	if (doRegInterlock_STATUS == 4)
	{
		vAllRegenStat = 2;
	}
	else if (doRegInterlock_STATUS > 0)
	{
		vAllRegenStat = 1;
	}
	else
	{
		vAllRegenStat = 0;
	}
	

    /*Check for output faults*/
   
    if ((doBypass1_STATUS == 4) || (doBypass2_STATUS == 4) || (doCooler_STATUS == 4) || (doRegInterlock_STATUS == 4)||
    (doStart_STATUS == 4))
    {
      qOutputFault = TRUE;
    }
    else
    {
      qOutputFault = FALSE;
    }
    
    /*Check for IO module COM error*/
    
    if (I_Battery_IO < 7)
    {
       qIO_COM_Fault = TRUE;
    }
    else
    {
       qIO_COM_Fault = FALSE;
    }
    
    
    /*Scroll through all warning messages*/

   if ((CAN_Red_VALUE == 1) && (tonMessage1_VALUE != 0))
		{            
			V_WarningNumber = 1;
			tonMessage1_STATUS = TRUE;
		}
	else if ((CAN_Amber_VALUE == 1) && (tonMessage2_VALUE != 0))
		{
			V_WarningNumber = 2;
			tonMessage2_STATUS = TRUE;
		}
	else if ((CAN_Regen_VALUE == 1) && (tonMessage3_VALUE != 0))
		{
			V_WarningNumber = 3;
			tonMessage3_STATUS = TRUE;
		}
	else if ((CAN_HEGT_VALUE == 1) && (tonMessage4_VALUE != 0))
		{
			V_WarningNumber = 4;
			tonMessage4_STATUS = TRUE;
		}
	else if ((qLowHydPSI == 1) && (tonMessage5_VALUE != 0))
		{
			V_WarningNumber = 5;
			tonMessage5_STATUS = TRUE;
		}
	else if ((qHighHydTemp == TRUE)  && (tonMessage6_VALUE != 0))
		{
			V_WarningNumber = 6;
			tonMessage6_STATUS = TRUE;
		}
	else if ((qTemp_P_Fault == TRUE) && (tonMessage7_VALUE != 0))
		{
			V_WarningNumber = 7;
			tonMessage7_STATUS = TRUE;
		}
	else if ((qHighHydPSI == TRUE) && (tonMessage8_VALUE != 0))
		{
			V_WarningNumber = 8;
			tonMessage8_STATUS = TRUE;
		}
	else if (((qPSI_P_Fault == TRUE)||(qPSI_LS_Fault == TRUE)) && (tonMessage9_VALUE != 0))
		{
			V_WarningNumber = 9;
			tonMessage9_STATUS = TRUE;
		}
	else if ((qLowFuel == TRUE) && (tonMessage10_VALUE != 0))
		{
			V_WarningNumber = 10;
			tonMessage10_STATUS = TRUE;
		}
	else if ((qFuelFault == TRUE)  && (tonMessage11_VALUE != 0))
		{
			V_WarningNumber = 11;
			tonMessage11_STATUS = TRUE;
		}
	else if ((qLowHydOil == TRUE) && (tonMessage12_VALUE != 0))
		{
			V_WarningNumber = 12;
			tonMessage12_STATUS = TRUE;
		}
	else if ((qHydLevelFault == TRUE) && (tonMessage13_VALUE != 0))
		{
			V_WarningNumber = 13;
			tonMessage13_STATUS = TRUE;
		}
	else if ((qOutputFault == TRUE) && (tonMessage14_VALUE != 0))
		{
			V_WarningNumber = 14;
			tonMessage14_STATUS = TRUE;
		}
	else if ((CAN_Preheat_VALUE == TRUE) && (tonMessage15_VALUE != 0))
		{
			V_WarningNumber = 15;
			tonMessage15_STATUS = TRUE;
		}
	else if ((qRC1Fault == TRUE) && (tonMessage16_VALUE != 0))
		{
			V_WarningNumber = 16;
			tonMessage16_STATUS = TRUE;
		}
	else if ((qRC2Fault == TRUE) && (tonMessage17_VALUE != 0))
	  {
			V_WarningNumber = 17;
			tonMessage17_STATUS = TRUE;
		}
	else if ((qIO_COM_Fault == TRUE) && (tonMessage18_VALUE != 0))
		{
			V_WarningNumber = 18;
			tonMessage18_STATUS = TRUE;
		}
	else if ((CAN_Inhibit_VALUE == TRUE) && (tonMessage19_VALUE != 0))
		{
			V_WarningNumber = 19;
			tonMessage19_STATUS = TRUE;
		}
	else 
	{
		if ((CAN_Red_VALUE == 1)||(CAN_Amber_VALUE == 1)||(CAN_Regen_VALUE == TRUE)||(CAN_HEGT_VALUE == TRUE)||(CAN_Inhibit_VALUE == TRUE)
				||(qHighHydTemp == TRUE)||(qTemp_P_Fault == TRUE)||(qHighHydPSI == TRUE)||(qPSI_P_Fault == TRUE)||(qPSI_LS_Fault == TRUE)||(qLowFuel == TRUE)
				||(qFuelFault == TRUE)||(qLowHydOil == TRUE)||(qHydLevelFault > 0)||(qOutputFault == 0)||(CAN_Preheat_VALUE == TRUE)
				||(qRC1Fault == TRUE)||(qRC2Fault == TRUE)||(qIO_COM_Fault > 0)||(qLowHydPSI > 0))
		{
		}
		else
		{
			V_WarningNumber = 0;
		}
		
		/*Reset all the message timers*/
		tonMessage1_STATUS = FALSE;
		tonMessage2_STATUS = FALSE;
		tonMessage3_STATUS = FALSE;
		tonMessage4_STATUS = FALSE;
		tonMessage5_STATUS = FALSE;
		tonMessage6_STATUS = FALSE;
		tonMessage7_STATUS = FALSE;
		tonMessage8_STATUS = FALSE;
		tonMessage9_STATUS = FALSE;
		tonMessage10_STATUS = FALSE;
		tonMessage11_STATUS = FALSE;
		tonMessage12_STATUS = FALSE;
		tonMessage13_STATUS = FALSE;
		tonMessage14_STATUS = FALSE;
		tonMessage15_STATUS = FALSE;
		tonMessage16_STATUS = FALSE;
		tonMessage17_STATUS = FALSE;
		tonMessage18_STATUS = FALSE;
		tonMessage19_STATUS = FALSE;
		
		tonMessage1_VALUE = 5;
		tonMessage2_VALUE = 5;
		tonMessage3_VALUE = 5;
		tonMessage4_VALUE = 5;
		tonMessage5_VALUE = 5;
		tonMessage6_VALUE = 5;
		tonMessage7_VALUE = 5;
		tonMessage8_VALUE = 5;
		tonMessage9_VALUE = 5;
		tonMessage10_VALUE = 5;
		tonMessage11_VALUE = 5;
		tonMessage12_VALUE = 5;
		tonMessage13_VALUE = 5;
		tonMessage14_VALUE = 5;
		tonMessage15_VALUE = 5;
		tonMessage16_VALUE = 5;
		tonMessage17_VALUE = 5;
		tonMessage18_VALUE = 5;
	  tonMessage19_VALUE = 5;	
	}

	/*Set warning ribbon color*/
	if (V_WarningNumber == 0)
	{
		V_WarningColor = 0;
	}
	else if ((V_WarningNumber == 1) || (V_WarningNumber == 5) || (V_WarningNumber == 8) )
	{
	     V_WarningColor = 2;
	}
	else
	{
		V_WarningColor = 1;
	}
}




/***************************************           CAN TX        ************************************************/
/****************************************************************************************************************/

void Send_CAN( void ) 
{   
    Can_Message_  canmessage;
    
    if (As.CAN_TX_100ms_timer)
    {
        As.CAN_TX_100ms_timer--;
    }
    
    if (As.CAN_TX_1s_timer)
    {
        As.CAN_TX_1s_timer--;
    }
  
   /*SEND TSC1 ENGINE SPEED CONTROL*/
  
   canmessage.type        = EXTENDED;
   canmessage.length      = 8;
   canmessage.identifier  = TSC1_TX;
  

   canmessage.data[0] = 0x01;               /*Speed Control*/
   canmessage.data[1] = (UINT8)(vReqEngSpeed);     /*Requested speed 0.125 RPM/bit, 2 bytes*/
   canmessage.data[2] = (UINT8)(vReqEngSpeed>>8);
   canmessage.data[3] = MESSAGE_FILLER;
   canmessage.data[4] = MESSAGE_FILLER;
   canmessage.data[5] = MESSAGE_FILLER;
   canmessage.data[6] = MESSAGE_FILLER;
   canmessage.data[7] = MESSAGE_FILLER;

   (void) Send_CAN_Message (Display, CAN_Tx_2, canmessage);
   
   
   /*SEND REGEN REQUEST/INHIBIT */
   if (As.CAN_TX_100ms_timer == 0)
   {
      canmessage.type        = EXTENDED;
      canmessage.length      = 8;
      canmessage.identifier  = Y_DPFIF_TX;
  

      canmessage.data[0] = (UINT8)((FILL2BITS) + (As.InhibitCAN << 2) + (qRegenReq << 4) + (FILL2BITS << 6)) ;             /*Speed Control*/
      canmessage.data[1] = MESSAGE_FILLER;
      canmessage.data[2] = MESSAGE_FILLER;
      canmessage.data[3] = MESSAGE_FILLER;
      canmessage.data[4] = MESSAGE_FILLER;
      canmessage.data[5] = MESSAGE_FILLER;
      canmessage.data[6] = MESSAGE_FILLER;
      canmessage.data[7] = MESSAGE_FILLER;

   
      (void) Send_CAN_Message (Display, CAN_Tx_2, canmessage);
   }
   
   /*SEND ENGINE STOP COMMAND */
   if (As.CAN_TX_100ms_timer == 0)
   {
      canmessage.type        = EXTENDED;
      canmessage.length      = 8;
      canmessage.identifier  = Y_STP_TX;
  

      canmessage.data[0] = (UINT8) (qEngineStop) ;             /*Speed Control*/
      canmessage.data[1] = MESSAGE_FILLER;
      canmessage.data[2] = MESSAGE_FILLER;
      canmessage.data[3] = MESSAGE_FILLER;
      canmessage.data[4] = MESSAGE_FILLER;
      canmessage.data[5] = MESSAGE_FILLER;
      canmessage.data[6] = MESSAGE_FILLER;
      canmessage.data[7] = MESSAGE_FILLER;

    (void) Send_CAN_Message (Display, CAN_Tx_2, canmessage);
    } 
    
     /*SEND ENGINE YEC COMMAND */
   if (As.CAN_TX_100ms_timer == 0)
   {
      canmessage.type        = EXTENDED;
      canmessage.length      = 8;
      canmessage.identifier  = Y_EC_TX;
  

      canmessage.data[0] = 0 ;             /*Misc engine settings*/
      canmessage.data[1] = 0;
      canmessage.data[2] = MESSAGE_FILLER;
      canmessage.data[3] = MESSAGE_FILLER;
      canmessage.data[4] = MESSAGE_FILLER;
      canmessage.data[5] = MESSAGE_FILLER;
      canmessage.data[6] = MESSAGE_FILLER;
      canmessage.data[7] = MESSAGE_FILLER;

    (void) Send_CAN_Message (Display, CAN_Tx_2, canmessage);
    } 
    
       /*SEND ENGINE HOUR REQUEST COMMAND */
   if (As.CAN_TX_1s_timer == 0)
   {
      canmessage.type        = EXTENDED;
      canmessage.length      = 3;
      canmessage.identifier  = HR_REQ_TX;
  

      canmessage.data[0] = 0xE5;             /*PGN for engine hours*/
      canmessage.data[1] = 0xFE;;
      canmessage.data[2] = 0;
      

    (void) Send_CAN_Message (Display, CAN_Tx_2, canmessage);
    } 
   
   if (As.CAN_TX_100ms_timer == 0)
    {
        As.CAN_TX_100ms_timer = 10;
    }
    
    if (As.CAN_TX_1s_timer == 0)
    {
        As.CAN_TX_1s_timer = 100;
    }
   
}