/*
** #########################################################################
**     File Name   : Constants.h
**     Processor   : Not applicable
**     File Format : Version 00.01
**     Composer    : Version 16.9.13.1700
**     Database    : Hippo_CCPU_01_01.sdf
**     IOC         : Hippo_CCPU_01_01.ioc
**     App version : Version 00.00
**     Date/Time   : 10/21/2016, 4:54 PM UTC
**     Abstract    :
**     This header has all the #defines for the system inputs, outputs, modules, etc.
**
**     (c) Copyright HED, Inc. 2006-2009
**     HED, Inc.
**     2120 Constitution Ave.
**     Hartford, WI 53089
**     United States
**     http        : www.hedonline.com
**     mail        : support@hedonline.com
** #########################################################################
**                            !!!  WARNING !!!
**     ALTERING THIS FILE IN ANY WAY MAY CAUSE PERSONAL INJURY AND/OR DEATH.
** #########################################################################
*/

/*  Module Numbers */
#define Display                0     /*CL-711-106-10*/
#define IOModule               1     /*CL-449-100-21*/

/*  IOMap locations */

/*  Inputs assigned to module Display */
#define ai_Fuel_Level                    IOMap[0]        /*Range 0 - 300*/
#define ai_Hyd_Level                     IOMap[1]        /*Range 0 - 300*/
#define I_Wakeup                         IOMap[4]        /*Range 0 - 2*/
#define I_Battery                        IOMap[8]        /*Range 0 - 5000*/
#define I_Button_01                      IOMap[36]       /*Range 0 - 2*/
#define I_Button_02                      IOMap[37]       /*Range 0 - 2*/
#define I_Button_03                      IOMap[38]       /*Range 0 - 2*/
#define I_Button_04                      IOMap[39]       /*Range 0 - 2*/
#define I_Button_Left                    IOMap[40]       /*Range 0 - 2*/
#define I_Button_Right                   IOMap[41]       /*Range 0 - 2*/
#define I_Button_Up                      IOMap[42]       /*Range 0 - 2*/
#define I_Button_Down                    IOMap[43]       /*Range 0 - 2*/
#define I_Button_Center                  IOMap[44]       /*Range 0 - 2*/

/*  Inputs assigned to module IOModule */
#define ai_P_Psi                         IOMap[49]       /*Range 0 - 5000*/
#define ai_P_Temp                        IOMap[50]       /*Range 0 - 5000*/
#define ai_LS_Psi                        IOMap[51]       /*Range 0 - 5000*/
#define ai_LS_Temp                       IOMap[52]       /*Range 0 - 5000*/
#define I_Battery_IO                     IOMap[53]       /*Range 0 - 5000*/

/*  Value Outputs assigned to module Display */
#define doCooler_VALUE                   IOMap[58]       /*Range 0 - 1000*/
#define doStart_VALUE                    IOMap[59]       /*Range 0 - 1000*/
#define doRegInterlock_VALUE             IOMap[60]       /*Range 0 - 1000*/
#define pwmBackLight_VALUE               IOMap[63]       /*Range 0 - 1000*/

/*  Value Outputs assigned to module IOModule */
#define ccFlow1_VALUE                    IOMap[64]       /*Range 0 - 3000*/
#define ccFlow2_VALUE                    IOMap[65]       /*Range 0 - 3000*/
#define doBypass1_VALUE                  IOMap[66]       /*Range 0 - 1000*/
#define doBypass2_VALUE                  IOMap[67]       /*Range 0 - 1000*/

/*  Flash Outputs assigned to module Display */
#define doCooler_FLASH                   IOMap[68]       /*Range 0 - 1*/
#define doStart_FLASH                    IOMap[69]       /*Range 0 - 1*/
#define doRegInterlock_FLASH             IOMap[70]       /*Range 0 - 1*/
#define pwmBackLight_FLASH               IOMap[73]       /*Range 0 - 1*/

/*  Flash Outputs assigned to module IOModule */
#define ccFlow1_FLASH                    IOMap[74]       /*Range 0 - 1*/
#define ccFlow2_FLASH                    IOMap[75]       /*Range 0 - 1*/
#define doBypass1_FLASH                  IOMap[76]       /*Range 0 - 1*/
#define doBypass2_FLASH                  IOMap[77]       /*Range 0 - 1*/

/*  Status Outputs assigned to module Display */
#define doCooler_STATUS                  IOMap[78]       /*Range 0 - 4*/
#define doStart_STATUS                   IOMap[79]       /*Range 0 - 4*/
#define doRegInterlock_STATUS            IOMap[80]       /*Range 0 - 4*/
#define pwmBackLight_STATUS              IOMap[83]       /*Range 0 - 4*/

/*  Status Outputs assigned to module IOModule */
#define ccFlow1_STATUS                   IOMap[84]       /*Range 0 - 4*/
#define ccFlow2_STATUS                   IOMap[85]       /*Range 0 - 4*/
#define doBypass1_STATUS                 IOMap[86]       /*Range 0 - 4*/
#define doBypass2_STATUS                 IOMap[87]       /*Range 0 - 4*/

/*  Current Outputs assigned to module Display */
#define doCooler_CURRENT                 IOMap[88]       /*Range 0 - 2000*/
#define doStart_CURRENT                  IOMap[89]       /*Range 0 - 2000*/
#define doRegInterlock_CURRENT           IOMap[90]       /*Range 0 - 2000*/
#define pwmBackLight_CURRENT             IOMap[93]       /*Range 0 - 10*/

/*  Current Outputs assigned to module IOModule */
#define ccFlow1_CURRENT                  IOMap[94]       /*Range 0 - 3000*/
#define ccFlow2_CURRENT                  IOMap[95]       /*Range 0 - 3000*/
#define doBypass1_CURRENT                IOMap[96]       /*Range 0 - 3000*/
#define doBypass2_CURRENT                IOMap[97]       /*Range 0 - 3000*/

/* Variables */
#define vRPM                             IOMap[160]      /*Range 0 - 5000*/
#define vTempP                           IOMap[161]      /*Range 0 - 300*/
#define V_Screen_Number                  IOMap[162]      /*Range 0 - 20*/
#define qPSI_P_Fault                     IOMap[163]      /*Range 0 - 1*/
#define qPSI_LS_Fault                    IOMap[164]      /*Range 0 - 1*/
#define qTemp_P_Fault                    IOMap[165]      /*Range 0 - 1*/
#define qTemp_LS_Fault                   IOMap[166]      /*Range 0 - 1*/
#define qFuelFault                       IOMap[167]      /*Range 0 - 1*/
#define qHydLevelFault                   IOMap[168]      /*Range 0 - 1*/
#define qOutputFault                     IOMap[169]      /*Range 0 - 1*/
#define qRC1Fault                        IOMap[170]      /*Range 0 - 1*/
#define qRC2Fault                        IOMap[171]      /*Range 0 - 1*/
#define qIO_COM_Fault                    IOMap[172]      /*Range 0 - 1*/
#define qLowFuel                         IOMap[173]      /*Range 0 - 1*/
#define qLowHydOil                       IOMap[174]      /*Range 0 - 1*/
#define qHighHydTemp                     IOMap[175]      /*Range 0 - 1*/
#define qHighHydPSI                      IOMap[176]      /*Range 0 - 1*/
#define qHighLevel5                      IOMap[177]      /*Range 0 - 1*/
#define vFlow2Stat                       IOMap[178]      /*Range 0 - 16*/
#define vFlow1Stat                       IOMap[179]      /*Range 0 - 16*/
#define V_WarningNumber                  IOMap[180]      /*Range 0 - 100*/
#define V_WarningColor                   IOMap[181]      /*Range 0 - 100*/
#define qTool1Shot1                      IOMap[182]      /*Range 0 - 1*/
#define qTool1Shot2                      IOMap[183]      /*Range 0 - 1*/
#define vFlow1                           IOMap[184]      /*Range 0 - 500*/
#define vFlow2                           IOMap[185]      /*Range 0 - 500*/
#define qUp1shot                         IOMap[186]      /*Range 0 - 1*/
#define qDown1Shot                       IOMap[187]      /*Range 0 - 1*/
#define qRC1Active                       IOMap[188]      /*Range 0 - 1*/
#define qRC2Active                       IOMap[189]      /*Range 0 - 1*/
#define qRC1Estop                        IOMap[190]      /*Range 0 - 10*/
#define qRC2Estop                        IOMap[191]      /*Range 0 - 10*/
#define qRegenLamp                       IOMap[192]      /*Range 0 - 2*/
#define wMod1Stat                        IOMap[193]      /*Range 0 - 16*/
#define qCOM4Fault                       IOMap[194]      /*Range 0 - 1*/
#define vTool2Key                        IOMap[195]      /*Range 0 - 16*/
#define vNavKey                          IOMap[196]      /*Range 0 - 1*/
#define vTool1Key                        IOMap[197]      /*Range 0 - 16*/
#define vTempLS                          IOMap[198]      /*Range 0 - 300*/
#define vPsiP                            IOMap[199]      /*Range 0 - 5000*/
#define vPsiLS                           IOMap[200]      /*Range 0 - 5000*/
#define qLowHydPSI                       IOMap[201]      /*Range 0 - 1*/
#define qScreen1Shot                     IOMap[202]      /*Range 0 - 1*/
#define vFuelLevel                       IOMap[203]      /*Range 0 - 5000*/
#define vHydLevel                        IOMap[204]      /*Range 0 - 5000*/
#define vWaterT                          IOMap[205]      /*Range 0 - 5000*/
#define qInhibit                         IOMap[206]      /*Range 0 - 1*/
#define qRegenReq                        IOMap[207]      /*Range 0 - 1*/
#define qRC1Start                        IOMap[208]      /*Range 0 - 1*/
#define qRC1Stop                         IOMap[209]      /*Range 0 - 1*/
#define qRC1Up                           IOMap[210]      /*Range 0 - 1*/
#define qRC1Down                         IOMap[211]      /*Range 0 - 1*/
#define qRC2Start                        IOMap[212]      /*Range 0 - 1*/
#define qRC2Stop                         IOMap[213]      /*Range 0 - 1*/
#define qRC2Up                           IOMap[214]      /*Range 0 - 1*/
#define qRC2Down                         IOMap[215]      /*Range 0 - 1*/
#define vReqEngSpeed                     IOMap[216]      /*Range 0 - 65535*/
#define vIdleMode                        IOMap[217]      /*Range 0 - 2*/
#define qHighIdle                        IOMap[218]      /*Range 0 - 2*/
#define vTest2                           IOMap[219]      /*Range 0 - 5000*/
#define qIdleSet                         IOMap[220]      /*Range 0 - 2*/
#define qUp1Shot2                        IOMap[221]      /*Range 0 - 1*/
#define qDown1Shot2                      IOMap[222]      /*Range 0 - 1*/
#define qSetKey                          IOMap[223]      /*Range 0 - 1*/
#define vSPN_Display                     *((UINT32 *far) &IOMap[224])  /*Range 0 - 555000*/
#define vFMI_Display                     IOMap[226]      /*Range 0 - 255*/
#define qEngineStop                      IOMap[227]      /*Range 0 - 1*/
#define qEngineRunning                   IOMap[228]      /*Range 0 - 1*/
#define qDisplayStart                    IOMap[229]      /*Range 0 - 1*/
#define qDisplayStop                     IOMap[230]      /*Range 0 - 1*/
#define qEngComFault                     IOMap[231]      /*Range 0 - 1*/
#define qService100                      IOMap[232]      /*Range 0 - 1*/
#define qService250                      IOMap[233]      /*Range 0 - 1*/
#define qReset100                        IOMap[234]      /*Range 0 - 1*/
#define qReset250                        IOMap[235]      /*Range 0 - 1*/
#define vEngHours                        *((UINT32 *far) &IOMap[236])  /*Range 0 - 2000000*/
#define vPresDiff                        IOMap[238]      /*Range 0 - 5000*/
#define vBypass1Stat                     IOMap[239]      /*Range 0 - 4*/
#define vBypass2Stat                     IOMap[240]      /*Range 0 - 4*/
#define vCoolerStat                      IOMap[241]      /*Range 0 - 4*/
#define vStartStat                       IOMap[242]      /*Range 0 - 4*/
#define vAllRegenStat                    IOMap[243]      /*Range 0 - 4*/
#define vECUStat                         IOMap[244]      /*Range 0 - 16*/
#define vRC1ComStat                      IOMap[245]      /*Range 0 - 16*/
#define vRC2ComStat                      IOMap[246]      /*Range 0 - 16*/

/* State Machines Enumeration */

/* Timers */
#define tonButton1_VALUE                 IOMap[251]      /*Range 0 - 20*/
#define tonMessage1_VALUE                IOMap[252]      /*Range 0 - 43*/
#define tonMessage2_VALUE                IOMap[253]      /*Range 0 - 43*/
#define tonMessage3_VALUE                IOMap[254]      /*Range 0 - 43*/
#define tonMessage4_VALUE                IOMap[255]      /*Range 0 - 43*/
#define tonMessage5_VALUE                IOMap[256]      /*Range 0 - 43*/
#define tonMessage6_VALUE                IOMap[257]      /*Range 0 - 43*/
#define tonMessage7_VALUE                IOMap[258]      /*Range 0 - 43*/
#define tonMessage8_VALUE                IOMap[259]      /*Range 0 - 43*/
#define tonMessage9_VALUE                IOMap[260]      /*Range 0 - 43*/
#define tonMessage10_VALUE               IOMap[261]      /*Range 0 - 43*/
#define tonMessage11_VALUE               IOMap[262]      /*Range 0 - 43*/
#define tonMessage12_VALUE               IOMap[263]      /*Range 0 - 43*/
#define tonMessage13_VALUE               IOMap[264]      /*Range 0 - 43*/
#define tonMessage14_VALUE               IOMap[265]      /*Range 0 - 43*/
#define tonMessage15_VALUE               IOMap[266]      /*Range 0 - 43*/
#define tonMessage16_VALUE               IOMap[267]      /*Range 0 - 43*/
#define tonMessage17_VALUE               IOMap[268]      /*Range 0 - 43*/
#define tonMessage18_VALUE               IOMap[269]      /*Range 0 - 43*/
#define tonMessage19_VALUE               IOMap[270]      /*Range 0 - 43*/
#define tonMessage20_VALUE               IOMap[271]      /*Range 0 - 43*/
#define tonMessage21_VALUE               IOMap[272]      /*Range 0 - 43*/
#define tonMessage22_VALUE               IOMap[273]      /*Range 0 - 43*/
#define tonMessage23_VALUE               IOMap[274]      /*Range 0 - 43*/
#define tonMessage24_VALUE               IOMap[275]      /*Range 0 - 43*/
#define tonMessage25_VALUE               IOMap[276]      /*Range 0 - 43*/
#define tonButton2_VALUE                 IOMap[277]      /*Range 0 - 20*/
#define tonButton3_VALUE                 IOMap[278]      /*Range 0 - 20*/
#define tonButton4_VALUE                 IOMap[279]      /*Range 0 - 20*/
#define tonStop_VALUE                    IOMap[280]      /*Range 0 - 20*/
#define tonButtonUp_VALUE                IOMap[281]      /*Range 0 - 20*/
#define tonShutdown_VALUE                IOMap[282]      /*Range 0 - 50*/
#define tonMessage26_VALUE               IOMap[283]      /*Range 0 - 43*/
#define tonMessage27_VALUE               IOMap[284]      /*Range 0 - 43*/
#define tonMessage28_VALUE               IOMap[285]      /*Range 0 - 43*/
#define tonMessage29_VALUE               IOMap[286]      /*Range 0 - 43*/
#define tonMessage30_VALUE               IOMap[287]      /*Range 0 - 43*/
#define tonCOM1_VALUE                    IOMap[288]      /*Range 0 - 5*/
#define tonCOM2_VALUE                    IOMap[289]      /*Range 0 - 5*/
#define tonCOM3_VALUE                    IOMap[290]      /*Range 0 - 5*/
#define tonCOM4_VALUE                    IOMap[291]      /*Range 0 - 5*/
#define tonLowFuelDebounce_VALUE         IOMap[292]      /*Range 0 - 5*/
#define tonHiPSIReset_VALUE              IOMap[293]      /*Range 0 - 5*/
#define tonHydLevDebounce_VALUE          IOMap[294]      /*Range 0 - 5*/
#define tonMessage31_VALUE               IOMap[295]      /*Range 0 - 43*/
#define tonMessage32_VALUE               IOMap[296]      /*Range 0 - 43*/
#define tonFlowIncDec_VALUE              IOMap[297]      /*Range 0 - 100*/
#define tonEmptyDeb4_VALUE               IOMap[298]      /*Range 0 - 5*/
#define tonUp1Deb_VALUE                  IOMap[299]      /*Range 0 - 100*/
#define tonServScreen_VALUE              IOMap[300]      /*Range 0 - 5*/
#define tonLoPSIReset_VALUE              IOMap[301]      /*Range 0 - 5*/
#define tonHighTReset_VALUE              IOMap[302]      /*Range 0 - 5*/
#define tonDn1Deb_VALUE                  IOMap[303]      /*Range 0 - 100*/
#define tonUp2Deb_VALUE                  IOMap[304]      /*Range 0 - 100*/
#define tonDn2Deb_VALUE                  IOMap[305]      /*Range 0 - 100*/
#define tonButton1_STATUS                IOMap[306]      /*Range 0 - 1*/
#define tonMessage1_STATUS               IOMap[307]      /*Range 0 - 1*/
#define tonMessage2_STATUS               IOMap[308]      /*Range 0 - 1*/
#define tonMessage3_STATUS               IOMap[309]      /*Range 0 - 1*/
#define tonMessage4_STATUS               IOMap[310]      /*Range 0 - 1*/
#define tonMessage5_STATUS               IOMap[311]      /*Range 0 - 1*/
#define tonMessage6_STATUS               IOMap[312]      /*Range 0 - 1*/
#define tonMessage7_STATUS               IOMap[313]      /*Range 0 - 1*/
#define tonMessage8_STATUS               IOMap[314]      /*Range 0 - 1*/
#define tonMessage9_STATUS               IOMap[315]      /*Range 0 - 1*/
#define tonMessage10_STATUS              IOMap[316]      /*Range 0 - 1*/
#define tonMessage11_STATUS              IOMap[317]      /*Range 0 - 1*/
#define tonMessage12_STATUS              IOMap[318]      /*Range 0 - 1*/
#define tonMessage13_STATUS              IOMap[319]      /*Range 0 - 1*/
#define tonMessage14_STATUS              IOMap[320]      /*Range 0 - 1*/
#define tonMessage15_STATUS              IOMap[321]      /*Range 0 - 1*/
#define tonMessage16_STATUS              IOMap[322]      /*Range 0 - 1*/
#define tonMessage17_STATUS              IOMap[323]      /*Range 0 - 1*/
#define tonMessage18_STATUS              IOMap[324]      /*Range 0 - 1*/
#define tonMessage19_STATUS              IOMap[325]      /*Range 0 - 1*/
#define tonMessage20_STATUS              IOMap[326]      /*Range 0 - 1*/
#define tonMessage21_STATUS              IOMap[327]      /*Range 0 - 1*/
#define tonMessage22_STATUS              IOMap[328]      /*Range 0 - 1*/
#define tonMessage23_STATUS              IOMap[329]      /*Range 0 - 1*/
#define tonMessage24_STATUS              IOMap[330]      /*Range 0 - 1*/
#define tonMessage25_STATUS              IOMap[331]      /*Range 0 - 1*/
#define tonButton2_STATUS                IOMap[332]      /*Range 0 - 1*/
#define tonButton3_STATUS                IOMap[333]      /*Range 0 - 1*/
#define tonButton4_STATUS                IOMap[334]      /*Range 0 - 1*/
#define tonStop_STATUS                   IOMap[335]      /*Range 0 - 1*/
#define tonButtonUp_STATUS               IOMap[336]      /*Range 0 - 1*/
#define tonShutdown_STATUS               IOMap[337]      /*Range 0 - 1*/
#define tonMessage26_STATUS              IOMap[338]      /*Range 0 - 1*/
#define tonMessage27_STATUS              IOMap[339]      /*Range 0 - 1*/
#define tonMessage28_STATUS              IOMap[340]      /*Range 0 - 1*/
#define tonMessage29_STATUS              IOMap[341]      /*Range 0 - 1*/
#define tonMessage30_STATUS              IOMap[342]      /*Range 0 - 1*/
#define tonCOM1_STATUS                   IOMap[343]      /*Range 0 - 1*/
#define tonCOM2_STATUS                   IOMap[344]      /*Range 0 - 1*/
#define tonCOM3_STATUS                   IOMap[345]      /*Range 0 - 1*/
#define tonCOM4_STATUS                   IOMap[346]      /*Range 0 - 1*/
#define tonLowFuelDebounce_STATUS        IOMap[347]      /*Range 0 - 1*/
#define tonHiPSIReset_STATUS             IOMap[348]      /*Range 0 - 1*/
#define tonHydLevDebounce_STATUS         IOMap[349]      /*Range 0 - 1*/
#define tonMessage31_STATUS              IOMap[350]      /*Range 0 - 1*/
#define tonMessage32_STATUS              IOMap[351]      /*Range 0 - 1*/
#define tonFlowIncDec_STATUS             IOMap[352]      /*Range 0 - 1*/
#define tonEmptyDeb4_STATUS              IOMap[353]      /*Range 0 - 1*/
#define tonUp1Deb_STATUS                 IOMap[354]      /*Range 0 - 1*/
#define tonServScreen_STATUS             IOMap[355]      /*Range 0 - 1*/
#define tonLoPSIReset_STATUS             IOMap[356]      /*Range 0 - 1*/
#define tonHighTReset_STATUS             IOMap[357]      /*Range 0 - 1*/
#define tonDn1Deb_STATUS                 IOMap[358]      /*Range 0 - 1*/
#define tonUp2Deb_STATUS                 IOMap[359]      /*Range 0 - 1*/
#define tonDn2Deb_STATUS                 IOMap[360]      /*Range 0 - 1*/

/* Eeproms */
#define ee100HR                          *((UINT32 *far) &IOMap[247])  /*Range 0 - 5000000*/
#define ee250HR                          *((UINT32 *far) &IOMap[249])  /*Range 0 - 5000000*/

/* CAN Receives */
#define CAN_EngHours_VALUE               *((UINT32 *far) &IOMap[102])  /*Range 0 - 5000000*/
#define CAN_SPN_Least16_VALUE            *((UINT32 *far) &IOMap[104])  /*Range 0 - 65535*/
#define CAN_SPN_Most3_VALUE              *((UINT32 *far) &IOMap[106])  /*Range 0 - 4*/
#define CAN_FMI_VALUE                    *((UINT32 *far) &IOMap[108])  /*Range 0 - 16*/
#define CAN_Key1_1_Start_VALUE           IOMap[110]      /*Range 0 - 250*/
#define CAN_Key1_2_Stop_VALUE            IOMap[111]      /*Range 0 - 250*/
#define CAN_Key1_3_Up_VALUE              IOMap[112]      /*Range 0 - 250*/
#define CAN_Key1_4_Dn_VALUE              IOMap[113]      /*Range 0 - 250*/
#define CAN_Key2_1_Start_VALUE           IOMap[114]      /*Range 0 - 250*/
#define CAN_Key2_2_Stop_VALUE            IOMap[115]      /*Range 0 - 250*/
#define CAN_Key2_3_Up_VALUE              IOMap[116]      /*Range 0 - 250*/
#define CAN_Key2_4_Dn_VALUE              IOMap[117]      /*Range 0 - 250*/
#define CAN_Amber_VALUE                  IOMap[118]      /*Range 0 - 1*/
#define CAN_Red_VALUE                    IOMap[119]      /*Range 0 - 1*/
#define CAN_RPM_VALUE                    IOMap[120]      /*Range 0 - 65535*/
#define CAN_CoolT_VALUE                  IOMap[121]      /*Range 0 - 254*/
#define CAN_RC1_Data_VALUE               IOMap[122]      /*Range 0 - 3*/
#define CAN_RC1_Estop_VALUE              IOMap[123]      /*Range 0 - 3*/
#define CAN_RC1_Start_VALUE              IOMap[124]      /*Range 0 - 3*/
#define CAN_RC2_Data_VALUE               IOMap[125]      /*Range 0 - 3*/
#define CAN_RC2_Estop_VALUE              IOMap[126]      /*Range 0 - 3*/
#define CAN_RC2_Start_VALUE              IOMap[127]      /*Range 0 - 3*/
#define CAN_Regen_VALUE                  IOMap[128]      /*Range 0 - 1*/
#define CAN_HEGT_VALUE                   IOMap[129]      /*Range 0 - 1*/
#define CAN_DPFAck_VALUE                 IOMap[130]      /*Range 0 - 1*/
#define CAN_Preheat_VALUE                IOMap[131]      /*Range 0 - 1*/
#define CAN_Inhibit_VALUE                IOMap[132]      /*Range 0 - 1*/
#define CAN_EngHours_STATUS              IOMap[133]      /*Range 0 - 1*/
#define CAN_SPN_Least16_STATUS           IOMap[134]      /*Range 0 - 1*/
#define CAN_SPN_Most3_STATUS             IOMap[135]      /*Range 0 - 1*/
#define CAN_FMI_STATUS                   IOMap[136]      /*Range 0 - 1*/
#define CAN_Key1_1_Start_STATUS          IOMap[137]      /*Range 0 - 1*/
#define CAN_Key1_2_Stop_STATUS           IOMap[138]      /*Range 0 - 1*/
#define CAN_Key1_3_Up_STATUS             IOMap[139]      /*Range 0 - 1*/
#define CAN_Key1_4_Dn_STATUS             IOMap[140]      /*Range 0 - 1*/
#define CAN_Key2_1_Start_STATUS          IOMap[141]      /*Range 0 - 1*/
#define CAN_Key2_2_Stop_STATUS           IOMap[142]      /*Range 0 - 1*/
#define CAN_Key2_3_Up_STATUS             IOMap[143]      /*Range 0 - 1*/
#define CAN_Key2_4_Dn_STATUS             IOMap[144]      /*Range 0 - 1*/
#define CAN_Amber_STATUS                 IOMap[145]      /*Range 0 - 1*/
#define CAN_Red_STATUS                   IOMap[146]      /*Range 0 - 1*/
#define CAN_RPM_STATUS                   IOMap[147]      /*Range 0 - 1*/
#define CAN_CoolT_STATUS                 IOMap[148]      /*Range 0 - 1*/
#define CAN_RC1_Data_STATUS              IOMap[149]      /*Range 0 - 1*/
#define CAN_RC1_Estop_STATUS             IOMap[150]      /*Range 0 - 1*/
#define CAN_RC1_Start_STATUS             IOMap[151]      /*Range 0 - 1*/
#define CAN_RC2_Data_STATUS              IOMap[152]      /*Range 0 - 1*/
#define CAN_RC2_Estop_STATUS             IOMap[153]      /*Range 0 - 1*/
#define CAN_RC2_Start_STATUS             IOMap[154]      /*Range 0 - 1*/
#define CAN_Regen_STATUS                 IOMap[155]      /*Range 0 - 1*/
#define CAN_HEGT_STATUS                  IOMap[156]      /*Range 0 - 1*/
#define CAN_DPFAck_STATUS                IOMap[157]      /*Range 0 - 1*/
#define CAN_Preheat_STATUS               IOMap[158]      /*Range 0 - 1*/
#define CAN_Inhibit_STATUS               IOMap[159]      /*Range 0 - 1*/

/* Module Information */
#define Display_STATUS                   IOMap[98]       /*Range 0 - 9*/
#define IOModule_STATUS                  IOMap[99]       /*Range 0 - 9*/
#define Display_CAN_STATUS               IOMap[100]      /*Range 0 - 3*/
#define IOModule_CAN_STATUS              IOMap[101]      /*Range 0 - 3*/

/* Defines for Update Output function calls */
#define doCooler                         (UINT8)Display         , (UINT8)0
#define doStart                          (UINT8)Display         , (UINT8)1
#define doRegInterlock                   (UINT8)Display         , (UINT8)2
#define pwmBackLight                     (UINT8)Display         , (UINT8)5
#define ccFlow1                          (UINT8)IOModule        , (UINT8)0
#define ccFlow2                          (UINT8)IOModule        , (UINT8)1
#define doBypass1                        (UINT8)IOModule        , (UINT8)2
#define doBypass2                        (UINT8)IOModule        , (UINT8)3

/*  Screen Enumerations */
typedef enum
{
	Screen_Screen1 = 1,
	Screen_Screen2 = 2,
	Screen_Screen4 = 4,
	Screen_Screen3 = 6
} enum_Screens;

/*  Screen Layers Enumerations */




