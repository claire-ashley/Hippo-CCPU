/*
** #########################################################################
**     File Name   : Constants.h
**     Processor   : Not applicable
**     File Format : Version 00.01
**     Composer    : Version 17.2.7.1144
**     Database    : Hippo_CCPU_01_01.sdf
**     IOC         : Hippo_CCPU_01_01.ioc
**     App version : Version 00.00
**     Date/Time   : 3/20/2017, 4:32 AM UTC
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
#define I_RTCyear                        IOMap[10]       /*Range 0 - 5000*/
#define I_RTCmonth                       IOMap[11]       /*Range 0 - 5000*/
#define I_RTCdate                        IOMap[12]       /*Range 0 - 5000*/
#define I_RTChour                        IOMap[14]       /*Range 0 - 5000*/
#define I_RTCminute                      IOMap[15]       /*Range 0 - 5000*/
#define I_RTCsecond                      IOMap[16]       /*Range 0 - 5000*/
#define I_Error_Bits                     IOMap[28]       /*Range 0 - 5000*/
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
#define doIgnition_VALUE                 IOMap[61]       /*Range 0 - 1000*/
#define pwmButtonLED_VALUE               IOMap[62]       /*Range 0 - 1000*/
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
#define doIgnition_FLASH                 IOMap[71]       /*Range 0 - 1*/
#define pwmButtonLED_FLASH               IOMap[72]       /*Range 0 - 1*/
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
#define doIgnition_STATUS                IOMap[81]       /*Range 0 - 4*/
#define pwmButtonLED_STATUS              IOMap[82]       /*Range 0 - 4*/
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
#define doIgnition_CURRENT               IOMap[91]       /*Range 0 - 2000*/
#define pwmButtonLED_CURRENT             IOMap[92]       /*Range 0 - 10*/
#define pwmBackLight_CURRENT             IOMap[93]       /*Range 0 - 10*/

/*  Current Outputs assigned to module IOModule */
#define ccFlow1_CURRENT                  IOMap[94]       /*Range 0 - 3000*/
#define ccFlow2_CURRENT                  IOMap[95]       /*Range 0 - 3000*/
#define doBypass1_CURRENT                IOMap[96]       /*Range 0 - 3000*/
#define doBypass2_CURRENT                IOMap[97]       /*Range 0 - 3000*/

/* Variables */
#define vRPM                             IOMap[178]      /*Range 0 - 5000*/
#define vTempP                           IOMap[179]      /*Range 0 - 300*/
#define V_Screen_Number                  IOMap[180]      /*Range 0 - 20*/
#define qPSI_P_Fault                     IOMap[181]      /*Range 0 - 1*/
#define qPSI_LS_Fault                    IOMap[182]      /*Range 0 - 1*/
#define qTemp_P_Fault                    IOMap[183]      /*Range 0 - 1*/
#define qTemp_LS_Fault                   IOMap[184]      /*Range 0 - 1*/
#define qFuelFault                       IOMap[185]      /*Range 0 - 1*/
#define qHydLevelFault                   IOMap[186]      /*Range 0 - 1*/
#define qOutputFault                     IOMap[187]      /*Range 0 - 1*/
#define qRC1Fault                        IOMap[188]      /*Range 0 - 1*/
#define qRC2Fault                        IOMap[189]      /*Range 0 - 1*/
#define qIO_COM_Fault                    IOMap[190]      /*Range 0 - 1*/
#define qLowFuel                         IOMap[191]      /*Range 0 - 1*/
#define qLowHydOil                       IOMap[192]      /*Range 0 - 1*/
#define qHighHydTemp                     IOMap[193]      /*Range 0 - 1*/
#define qHighHydPSI                      IOMap[194]      /*Range 0 - 1*/
#define qHighLevel5                      IOMap[195]      /*Range 0 - 1*/
#define vFlow2Stat                       IOMap[196]      /*Range 0 - 16*/
#define vFlow1Stat                       IOMap[197]      /*Range 0 - 16*/
#define V_WarningNumber                  IOMap[198]      /*Range 0 - 100*/
#define V_WarningColor                   IOMap[199]      /*Range 0 - 100*/
#define qTool1Shot                       IOMap[200]      /*Range 0 - 1*/
#define vFlow1                           IOMap[201]      /*Range 0 - 500*/
#define vFlow2                           IOMap[202]      /*Range 0 - 500*/
#define qUp1shot                         IOMap[203]      /*Range 0 - 1*/
#define qDown1Shot                       IOMap[204]      /*Range 0 - 1*/
#define qRC1Active                       IOMap[205]      /*Range 0 - 1*/
#define qRC2Active                       IOMap[206]      /*Range 0 - 1*/
#define qRC1Estop                        IOMap[207]      /*Range 0 - 10*/
#define qRC2Estop                        IOMap[208]      /*Range 0 - 10*/
#define qRegenLamp                       IOMap[209]      /*Range 0 - 2*/
#define wMod1Stat                        IOMap[210]      /*Range 0 - 16*/
#define qCOM4Fault                       IOMap[211]      /*Range 0 - 1*/
#define vTool2Key                        IOMap[212]      /*Range 0 - 16*/
#define vNavKey                          IOMap[213]      /*Range 0 - 1*/
#define vTool1Key                        IOMap[214]      /*Range 0 - 16*/
#define vTempLS                          IOMap[215]      /*Range 0 - 300*/
#define vPsiP                            IOMap[216]      /*Range 0 - 5000*/
#define vPsiLS                           IOMap[217]      /*Range 0 - 5000*/
#define qLowHydPSI                       IOMap[218]      /*Range 0 - 1*/
#define qScreen1Shot                     IOMap[219]      /*Range 0 - 1*/
#define vFuelLevel                       IOMap[220]      /*Range 0 - 5000*/
#define vHydLevel                        IOMap[221]      /*Range 0 - 5000*/
#define vWaterT                          IOMap[222]      /*Range 0 - 5000*/
#define qInhibit                         IOMap[223]      /*Range 0 - 1*/
#define qRegenReq                        IOMap[224]      /*Range 0 - 1*/
#define qRC1Start                        IOMap[225]      /*Range 0 - 1*/
#define qRC1Stop                         IOMap[226]      /*Range 0 - 1*/
#define qRC1Up                           IOMap[227]      /*Range 0 - 1*/
#define qRC1Down                         IOMap[228]      /*Range 0 - 1*/
#define qRC2Start                        IOMap[229]      /*Range 0 - 1*/
#define qRC2Stop                         IOMap[230]      /*Range 0 - 1*/
#define qRC2Up                           IOMap[231]      /*Range 0 - 1*/
#define qRC2Down                         IOMap[232]      /*Range 0 - 1*/
#define vReqEngSpeed                     IOMap[233]      /*Range 0 - 65535*/
#define vIdleMode                        IOMap[234]      /*Range 0 - 2*/
#define qHighIdle                        IOMap[235]      /*Range 0 - 2*/
#define vTest2                           IOMap[236]      /*Range 0 - 5000*/
#define qIdleSet                         IOMap[237]      /*Range 0 - 2*/
#define qUp1Shot2                        IOMap[238]      /*Range 0 - 1*/
#define qDown1Shot2                      IOMap[239]      /*Range 0 - 1*/
#define qSetKey                          IOMap[240]      /*Range 0 - 1*/
#define vSPN_Display                     *((UINT32 *far) &IOMap[241])  /*Range 0 - 555000*/
#define vFMI_Display                     IOMap[243]      /*Range 0 - 255*/
#define qEngineStop                      IOMap[244]      /*Range 0 - 1*/
#define qEngineRunning                   IOMap[245]      /*Range 0 - 1*/
#define qDisplayStart                    IOMap[246]      /*Range 0 - 1*/
#define qDisplayStop                     IOMap[247]      /*Range 0 - 1*/
#define qEngComFault                     IOMap[248]      /*Range 0 - 16*/
#define qService100                      IOMap[249]      /*Range 0 - 1*/
#define qService250                      IOMap[250]      /*Range 0 - 1*/
#define qReset100                        IOMap[251]      /*Range 0 - 1*/
#define qReset250                        IOMap[252]      /*Range 0 - 1*/
#define vEngHours                        *((UINT32 *far) &IOMap[253])  /*Range 0 - 4000000*/
#define vPresDiff                        IOMap[255]      /*Range 0 - 5000*/
#define vBypass1Stat                     IOMap[256]      /*Range 0 - 4*/
#define vBypass2Stat                     IOMap[257]      /*Range 0 - 4*/
#define vCoolerStat                      IOMap[258]      /*Range 0 - 4*/
#define vStartStat                       IOMap[259]      /*Range 0 - 4*/
#define vAllRegenStat                    IOMap[260]      /*Range 0 - 4*/
#define vECUStat                         IOMap[261]      /*Range 0 - 16*/
#define vRC1ComStat                      IOMap[262]      /*Range 0 - 16*/
#define vRC2ComStat                      IOMap[263]      /*Range 0 - 16*/
#define vMPIndex                         IOMap[264]      /*Range 0 - 16*/
#define vEngStopInd                      IOMap[265]      /*Range 0 - 16*/
#define vEngWarnInd                      IOMap[266]      /*Range 0 - 16*/
#define qNoDM1                           IOMap[267]      /*Range 0 - 1*/
#define qNoBAM                           IOMap[268]      /*Range 0 - 1*/
#define vBAM_PGN                         IOMap[269]      /*Range 0 - 65535*/
#define vBAMnoSPN                        IOMap[270]      /*Range 0 - 65535*/
#define vSPNState                        IOMap[271]      /*Range 0 - 65535*/
#define vOCount                          IOMap[272]      /*Range 0 - 65535*/
#define vNewSPN                          IOMap[273]      /*Range 0 - 65535*/
#define vConv                            IOMap[274]      /*Range 0 - 65535*/
#define vSPNCount                        IOMap[275]      /*Range 0 - 65535*/
#define vTestA                           *((UINT32 *far) &IOMap[276])  /*Range 0 - 65535*/
#define vTestB                           *((UINT32 *far) &IOMap[278])  /*Range 0 - 65535*/
#define vTestC                           *((UINT32 *far) &IOMap[280])  /*Range 0 - 65535*/
#define vTestD                           *((UINT32 *far) &IOMap[282])  /*Range 0 - 65535*/
#define vTestE                           *((UINT32 *far) &IOMap[284])  /*Range 0 - 65535*/
#define vTestF                           *((UINT32 *far) &IOMap[286])  /*Range 0 - 65535*/
#define vIOmodStat                       IOMap[288]      /*Range 0 - 16*/
#define vIgnStat                         IOMap[289]      /*Range 0 - 4*/
#define qInhibitFault                    IOMap[290]      /*Range 0 - 4*/
#define V_Log_ptr                        IOMap[291]      /*Range 0 - 65535*/
#define arrayEvent                       ((UINT16 *far) &IOMap[292])  /*Range 0 - 65535*/
#define arrayMonth                       ((UINT16 *far) &IOMap[302])  /*Range 0 - 65535*/
#define arrayDate                        ((UINT16 *far) &IOMap[312])  /*Range 0 - 65535*/
#define arrayHour                        ((UINT16 *far) &IOMap[322])  /*Range 0 - 65535*/
#define arrayMinute                      ((UINT16 *far) &IOMap[332])  /*Range 0 - 65535*/
#define arrayTool                        ((UINT16 *far) &IOMap[342])  /*Range 0 - 65535*/
#define arrayFlow                        ((UINT16 *far) &IOMap[352])  /*Range 0 - 65535*/
#define arrayPSI                         ((UINT16 *far) &IOMap[362])  /*Range 0 - 65535*/
#define vTable                           IOMap[372]      /*Range 0 - 65535*/
#define qSetDate                         IOMap[373]      /*Range 0 - 4*/
#define qSetHour                         IOMap[374]      /*Range 0 - 4*/
#define qSetMinute                       IOMap[375]      /*Range 0 - 4*/
#define vNewDate                         IOMap[376]      /*Range 0 - 100*/
#define vNewHours                        IOMap[377]      /*Range 0 - 100*/
#define vNewMinutes                      IOMap[378]      /*Range 0 - 100*/
#define qClearLog                        IOMap[379]      /*Range 0 - 4*/
#define vTableTotal                      IOMap[380]      /*Range 0 - 65535*/
#define qSetKeyPage6                     IOMap[381]      /*Range 0 - 1*/
#define qSetDateLatch                    IOMap[382]      /*Range 0 - 1*/
#define qSetHourLatch                    IOMap[383]      /*Range 0 - 1*/
#define qSetMinuteLatch                  IOMap[384]      /*Range 0 - 1*/
#define vMaxFlow1                        IOMap[385]      /*Range 0 - 65535*/
#define vMaxFlow2                        IOMap[386]      /*Range 0 - 65535*/
#define vMaxPSI1                         IOMap[387]      /*Range 0 - 65535*/
#define vMaxPSI2                         IOMap[388]      /*Range 0 - 65535*/
#define vTest1                           IOMap[389]      /*Range 0 - 5000*/
#define vTest3                           IOMap[390]      /*Range 0 - 5000*/
#define vTest4                           *((UINT32 *far) &IOMap[391])  /*Range 0 - 5000*/
#define vTest5                           IOMap[393]      /*Range 0 - 5000*/
#define V_Execute_USB_Update             IOMap[394]      /*Range 0 - 5000*/
#define V_USB_Select                     IOMap[395]      /*Range 0 - 5000*/
#define vCAN2Stat                        IOMap[396]      /*Range 0 - 16*/
#define vEngBat                          IOMap[397]      /*Range 0 - 65535*/
#define vHiPSIStop                       IOMap[398]      /*Range 0 - 65535*/
#define arrayTestWr                      ((UINT16 *far) &IOMap[399])  /*Range 0 - 65535*/
#define vFlowLatch                       IOMap[409]      /*Range 0 - 16*/
#define vFlowLatch2                      IOMap[410]      /*Range 0 - 16*/
#define vReadChart2                      IOMap[411]      /*Range 0 - 16*/
#define vYanmarDPFMode                   IOMap[412]      /*Range 0 - 16*/
#define vMaxFlowSet2                     IOMap[413]      /*Range 0 - 1000*/
#define vMaxFlowSet1                     IOMap[414]      /*Range 0 - 1000*/
#define vRegenHours                      *((UINT32 *far) &IOMap[415])  /*Range 0 - 4000000000*/
#define vLowIdleSpd                      IOMap[417]      /*Range 0 - 8000*/
#define vLowRegenTemp                    IOMap[418]      /*Range 0 - 16*/
#define vRegenIdle                       IOMap[419]      /*Range 0 - 16*/
#define vRegenCond                       IOMap[420]      /*Range 0 - 16*/
#define vEmergencyReg                    IOMap[421]      /*Range 0 - 16*/
#define vRecoveryReg                     IOMap[422]      /*Range 0 - 16*/
#define vPressYes                        IOMap[423]      /*Range 0 - 16*/
#define vYesPress                        IOMap[424]      /*Range 0 - 16*/

/* State Machines Enumeration */

/* Timers */
#define tonButton1_VALUE                 IOMap[432]      /*Range 0 - 20*/
#define tonMessage1_VALUE                IOMap[433]      /*Range 0 - 43*/
#define tonMessage2_VALUE                IOMap[434]      /*Range 0 - 43*/
#define tonMessage3_VALUE                IOMap[435]      /*Range 0 - 43*/
#define tonMessage4_VALUE                IOMap[436]      /*Range 0 - 43*/
#define tonMessage5_VALUE                IOMap[437]      /*Range 0 - 43*/
#define tonMessage6_VALUE                IOMap[438]      /*Range 0 - 43*/
#define tonMessage7_VALUE                IOMap[439]      /*Range 0 - 43*/
#define tonMessage8_VALUE                IOMap[440]      /*Range 0 - 43*/
#define tonMessage9_VALUE                IOMap[441]      /*Range 0 - 43*/
#define tonMessage10_VALUE               IOMap[442]      /*Range 0 - 43*/
#define tonMessage11_VALUE               IOMap[443]      /*Range 0 - 43*/
#define tonMessage12_VALUE               IOMap[444]      /*Range 0 - 43*/
#define tonMessage13_VALUE               IOMap[445]      /*Range 0 - 43*/
#define tonMessage14_VALUE               IOMap[446]      /*Range 0 - 43*/
#define tonMessage15_VALUE               IOMap[447]      /*Range 0 - 43*/
#define tonMessage16_VALUE               IOMap[448]      /*Range 0 - 43*/
#define tonMessage17_VALUE               IOMap[449]      /*Range 0 - 43*/
#define tonMessage18_VALUE               IOMap[450]      /*Range 0 - 43*/
#define tonMessage19_VALUE               IOMap[451]      /*Range 0 - 43*/
#define tonMessage20_VALUE               IOMap[452]      /*Range 0 - 43*/
#define tonMessage21_VALUE               IOMap[453]      /*Range 0 - 43*/
#define tonMessage22_VALUE               IOMap[454]      /*Range 0 - 43*/
#define tonMessage23_VALUE               IOMap[455]      /*Range 0 - 43*/
#define tonMessage24_VALUE               IOMap[456]      /*Range 0 - 43*/
#define tonButton2_VALUE                 IOMap[457]      /*Range 0 - 20*/
#define tonButton3_VALUE                 IOMap[458]      /*Range 0 - 20*/
#define tonButton4_VALUE                 IOMap[459]      /*Range 0 - 20*/
#define tonStop_VALUE                    IOMap[460]      /*Range 0 - 20*/
#define tonButtonUp_VALUE                IOMap[461]      /*Range 0 - 20*/
#define tonShutdown_VALUE                IOMap[462]      /*Range 0 - 200*/
#define tonCheckActive_VALUE             IOMap[463]      /*Range 0 - 100*/
#define tonLowFuelDebounce_VALUE         IOMap[464]      /*Range 0 - 5*/
#define tonHiPSIReset_VALUE              IOMap[465]      /*Range 0 - 5*/
#define tonHydLevDebounce_VALUE          IOMap[466]      /*Range 0 - 5*/
#define tonMessage25_VALUE               IOMap[467]      /*Range 0 - 43*/
#define tonFlowIncDec_VALUE              IOMap[468]      /*Range 0 - 100*/
#define tonEmptyDeb4_VALUE               IOMap[469]      /*Range 0 - 5*/
#define tonUp1Deb_VALUE                  IOMap[470]      /*Range 0 - 100*/
#define tonServScreen_VALUE              IOMap[471]      /*Range 0 - 10*/
#define tonLoPSIReset_VALUE              IOMap[472]      /*Range 0 - 5*/
#define tonHighTReset_VALUE              IOMap[473]      /*Range 0 - 5*/
#define tonDn1Deb_VALUE                  IOMap[474]      /*Range 0 - 100*/
#define tonUp2Deb_VALUE                  IOMap[475]      /*Range 0 - 100*/
#define tonDn2Deb_VALUE                  IOMap[476]      /*Range 0 - 100*/
#define tonLoPSISet_VALUE                IOMap[477]      /*Range 0 - 5*/
#define tonEngCOM_VALUE                  IOMap[478]      /*Range 0 - 3*/
#define tonHiPSISet_VALUE                IOMap[479]      /*Range 0 - 5*/
#define tonMessage27_VALUE               IOMap[480]      /*Range 0 - 43*/
#define tonMessage26_VALUE               IOMap[481]      /*Range 0 - 43*/
#define tonWarnDisable_VALUE             IOMap[482]      /*Range 0 - 43*/
#define tonButton1_STATUS                IOMap[483]      /*Range 0 - 1*/
#define tonMessage1_STATUS               IOMap[484]      /*Range 0 - 1*/
#define tonMessage2_STATUS               IOMap[485]      /*Range 0 - 1*/
#define tonMessage3_STATUS               IOMap[486]      /*Range 0 - 1*/
#define tonMessage4_STATUS               IOMap[487]      /*Range 0 - 1*/
#define tonMessage5_STATUS               IOMap[488]      /*Range 0 - 1*/
#define tonMessage6_STATUS               IOMap[489]      /*Range 0 - 1*/
#define tonMessage7_STATUS               IOMap[490]      /*Range 0 - 1*/
#define tonMessage8_STATUS               IOMap[491]      /*Range 0 - 1*/
#define tonMessage9_STATUS               IOMap[492]      /*Range 0 - 1*/
#define tonMessage10_STATUS              IOMap[493]      /*Range 0 - 1*/
#define tonMessage11_STATUS              IOMap[494]      /*Range 0 - 1*/
#define tonMessage12_STATUS              IOMap[495]      /*Range 0 - 1*/
#define tonMessage13_STATUS              IOMap[496]      /*Range 0 - 1*/
#define tonMessage14_STATUS              IOMap[497]      /*Range 0 - 1*/
#define tonMessage15_STATUS              IOMap[498]      /*Range 0 - 1*/
#define tonMessage16_STATUS              IOMap[499]      /*Range 0 - 1*/
#define tonMessage17_STATUS              IOMap[500]      /*Range 0 - 1*/
#define tonMessage18_STATUS              IOMap[501]      /*Range 0 - 1*/
#define tonMessage19_STATUS              IOMap[502]      /*Range 0 - 1*/
#define tonMessage20_STATUS              IOMap[503]      /*Range 0 - 1*/
#define tonMessage21_STATUS              IOMap[504]      /*Range 0 - 1*/
#define tonMessage22_STATUS              IOMap[505]      /*Range 0 - 1*/
#define tonMessage23_STATUS              IOMap[506]      /*Range 0 - 1*/
#define tonMessage24_STATUS              IOMap[507]      /*Range 0 - 1*/
#define tonButton2_STATUS                IOMap[508]      /*Range 0 - 1*/
#define tonButton3_STATUS                IOMap[509]      /*Range 0 - 1*/
#define tonButton4_STATUS                IOMap[510]      /*Range 0 - 1*/
#define tonStop_STATUS                   IOMap[511]      /*Range 0 - 1*/
#define tonButtonUp_STATUS               IOMap[512]      /*Range 0 - 1*/
#define tonShutdown_STATUS               IOMap[513]      /*Range 0 - 1*/
#define tonCheckActive_STATUS            IOMap[514]      /*Range 0 - 1*/
#define tonLowFuelDebounce_STATUS        IOMap[515]      /*Range 0 - 1*/
#define tonHiPSIReset_STATUS             IOMap[516]      /*Range 0 - 1*/
#define tonHydLevDebounce_STATUS         IOMap[517]      /*Range 0 - 1*/
#define tonMessage25_STATUS              IOMap[518]      /*Range 0 - 1*/
#define tonFlowIncDec_STATUS             IOMap[519]      /*Range 0 - 1*/
#define tonEmptyDeb4_STATUS              IOMap[520]      /*Range 0 - 1*/
#define tonUp1Deb_STATUS                 IOMap[521]      /*Range 0 - 1*/
#define tonServScreen_STATUS             IOMap[522]      /*Range 0 - 1*/
#define tonLoPSIReset_STATUS             IOMap[523]      /*Range 0 - 1*/
#define tonHighTReset_STATUS             IOMap[524]      /*Range 0 - 1*/
#define tonDn1Deb_STATUS                 IOMap[525]      /*Range 0 - 1*/
#define tonUp2Deb_STATUS                 IOMap[526]      /*Range 0 - 1*/
#define tonDn2Deb_STATUS                 IOMap[527]      /*Range 0 - 1*/
#define tonLoPSISet_STATUS               IOMap[528]      /*Range 0 - 1*/
#define tonEngCOM_STATUS                 IOMap[529]      /*Range 0 - 1*/
#define tonHiPSISet_STATUS               IOMap[530]      /*Range 0 - 1*/
#define tonMessage27_STATUS              IOMap[531]      /*Range 0 - 1*/
#define tonMessage26_STATUS              IOMap[532]      /*Range 0 - 1*/
#define tonWarnDisable_STATUS            IOMap[533]      /*Range 0 - 1*/

/* Eeproms */
#define ee100HR                          *((UINT32 *far) &IOMap[425])  /*Range 0 - 5000000*/
#define ee250HR                          *((UINT32 *far) &IOMap[427])  /*Range 0 - 5000000*/
#define eeRunCount                       IOMap[429]      /*Range 0 - 99*/
#define eeEvent                          IOMap[430]      /*Range 0 - 99*/
#define eeChart2                         IOMap[431]      /*Range 0 - 99*/

/* CAN Receives */
#define CAN_EngHours_VALUE               *((UINT32 *far) &IOMap[102])  /*Range 0 - 5000000*/
#define CAN_SPN_Least16_VALUE            *((UINT32 *far) &IOMap[104])  /*Range 0 - 65535*/
#define CAN_SPN_Most3_VALUE              *((UINT32 *far) &IOMap[106])  /*Range 0 - 4*/
#define CAN_FMI_VALUE                    *((UINT32 *far) &IOMap[108])  /*Range 0 - 16*/
#define CAN_RegenMode_VALUE              *((UINT32 *far) &IOMap[110])  /*Range 0 - 15*/
#define CAN_RgnReqFlag_VALUE             *((UINT32 *far) &IOMap[112])  /*Range 0 - 15*/
#define CAN_RgnActiveStat_VALUE          *((UINT32 *far) &IOMap[114])  /*Range 0 - 3*/
#define CAN_RegenHours_VALUE             *((UINT32 *far) &IOMap[116])  /*Range 0 - 4294967294*/
#define CAN_Key1_1_Start_VALUE           IOMap[118]      /*Range 0 - 250*/
#define CAN_Key1_2_Stop_VALUE            IOMap[119]      /*Range 0 - 250*/
#define CAN_Key1_3_Up_VALUE              IOMap[120]      /*Range 0 - 250*/
#define CAN_Key1_4_Dn_VALUE              IOMap[121]      /*Range 0 - 250*/
#define CAN_Key2_1_Start_VALUE           IOMap[122]      /*Range 0 - 250*/
#define CAN_Key2_2_Stop_VALUE            IOMap[123]      /*Range 0 - 250*/
#define CAN_Key2_3_Up_VALUE              IOMap[124]      /*Range 0 - 250*/
#define CAN_Key2_4_Dn_VALUE              IOMap[125]      /*Range 0 - 250*/
#define CAN_Amber_VALUE                  IOMap[126]      /*Range 0 - 1*/
#define CAN_Red_VALUE                    IOMap[127]      /*Range 0 - 1*/
#define CAN_RPM_VALUE                    IOMap[128]      /*Range 0 - 65535*/
#define CAN_CoolT_VALUE                  IOMap[129]      /*Range 0 - 254*/
#define CAN_RC1_Data_VALUE               IOMap[130]      /*Range 0 - 3*/
#define CAN_RC1_Estop_VALUE              IOMap[131]      /*Range 0 - 3*/
#define CAN_RC1_Start_VALUE              IOMap[132]      /*Range 0 - 3*/
#define CAN_RC2_Data_VALUE               IOMap[133]      /*Range 0 - 3*/
#define CAN_RC2_Estop_VALUE              IOMap[134]      /*Range 0 - 3*/
#define CAN_RC2_Start_VALUE              IOMap[135]      /*Range 0 - 3*/
#define CAN_Regen_VALUE                  IOMap[136]      /*Range 0 - 1*/
#define CAN_HEGT_VALUE                   IOMap[137]      /*Range 0 - 1*/
#define CAN_DPFAck_VALUE                 IOMap[138]      /*Range 0 - 1*/
#define CAN_Preheat_VALUE                IOMap[139]      /*Range 0 - 1*/
#define CAN_Inhibit_VALUE                IOMap[140]      /*Range 0 - 1*/
#define CAN_RC1_Reason_VALUE             IOMap[141]      /*Range 0 - 15*/
#define CAN_RC2_Reason_VALUE             IOMap[142]      /*Range 0 - 15*/
#define CAN_LowIdle_VALUE                IOMap[143]      /*Range 0 - 65535*/
#define CAN_EngHours_STATUS              IOMap[144]      /*Range 0 - 1*/
#define CAN_SPN_Least16_STATUS           IOMap[145]      /*Range 0 - 1*/
#define CAN_SPN_Most3_STATUS             IOMap[146]      /*Range 0 - 1*/
#define CAN_FMI_STATUS                   IOMap[147]      /*Range 0 - 1*/
#define CAN_RegenMode_STATUS             IOMap[148]      /*Range 0 - 1*/
#define CAN_RgnReqFlag_STATUS            IOMap[149]      /*Range 0 - 1*/
#define CAN_RgnActiveStat_STATUS         IOMap[150]      /*Range 0 - 1*/
#define CAN_RegenHours_STATUS            IOMap[151]      /*Range 0 - 1*/
#define CAN_Key1_1_Start_STATUS          IOMap[152]      /*Range 0 - 1*/
#define CAN_Key1_2_Stop_STATUS           IOMap[153]      /*Range 0 - 1*/
#define CAN_Key1_3_Up_STATUS             IOMap[154]      /*Range 0 - 1*/
#define CAN_Key1_4_Dn_STATUS             IOMap[155]      /*Range 0 - 1*/
#define CAN_Key2_1_Start_STATUS          IOMap[156]      /*Range 0 - 1*/
#define CAN_Key2_2_Stop_STATUS           IOMap[157]      /*Range 0 - 1*/
#define CAN_Key2_3_Up_STATUS             IOMap[158]      /*Range 0 - 1*/
#define CAN_Key2_4_Dn_STATUS             IOMap[159]      /*Range 0 - 1*/
#define CAN_Amber_STATUS                 IOMap[160]      /*Range 0 - 1*/
#define CAN_Red_STATUS                   IOMap[161]      /*Range 0 - 1*/
#define CAN_RPM_STATUS                   IOMap[162]      /*Range 0 - 1*/
#define CAN_CoolT_STATUS                 IOMap[163]      /*Range 0 - 1*/
#define CAN_RC1_Data_STATUS              IOMap[164]      /*Range 0 - 1*/
#define CAN_RC1_Estop_STATUS             IOMap[165]      /*Range 0 - 1*/
#define CAN_RC1_Start_STATUS             IOMap[166]      /*Range 0 - 1*/
#define CAN_RC2_Data_STATUS              IOMap[167]      /*Range 0 - 1*/
#define CAN_RC2_Estop_STATUS             IOMap[168]      /*Range 0 - 1*/
#define CAN_RC2_Start_STATUS             IOMap[169]      /*Range 0 - 1*/
#define CAN_Regen_STATUS                 IOMap[170]      /*Range 0 - 1*/
#define CAN_HEGT_STATUS                  IOMap[171]      /*Range 0 - 1*/
#define CAN_DPFAck_STATUS                IOMap[172]      /*Range 0 - 1*/
#define CAN_Preheat_STATUS               IOMap[173]      /*Range 0 - 1*/
#define CAN_Inhibit_STATUS               IOMap[174]      /*Range 0 - 1*/
#define CAN_RC1_Reason_STATUS            IOMap[175]      /*Range 0 - 1*/
#define CAN_RC2_Reason_STATUS            IOMap[176]      /*Range 0 - 1*/
#define CAN_LowIdle_STATUS               IOMap[177]      /*Range 0 - 1*/

/* Module Information */
#define Display_STATUS                   IOMap[98]       /*Range 0 - 9*/
#define IOModule_STATUS                  IOMap[99]       /*Range 0 - 9*/
#define Display_CAN_STATUS               IOMap[100]      /*Range 0 - 3*/
#define IOModule_CAN_STATUS              IOMap[101]      /*Range 0 - 3*/

/* Defines for Update Output function calls */
#define doCooler                         (UINT8)Display         , (UINT8)0
#define doStart                          (UINT8)Display         , (UINT8)1
#define doRegInterlock                   (UINT8)Display         , (UINT8)2
#define doIgnition                       (UINT8)Display         , (UINT8)3
#define pwmButtonLED                     (UINT8)Display         , (UINT8)4
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
	Screen_Screen5 = 3,
	Screen_Screen4 = 4,
	Screen_Screen6 = 5,
	Screen_Screen3 = 6
} enum_Screens;

/*  Screen Layers Enumerations */






