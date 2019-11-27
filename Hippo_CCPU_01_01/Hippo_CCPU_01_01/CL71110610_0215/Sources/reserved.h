/*
** ###################################################################
**     Filename  : reserved.h
**     Processor : Not applicable
**     FileFormat: V1.00
**     Compiler  : Composer Version XX.XX.XX
**     Database  : Name.cdb_00_00
**     IOC       : Name.ioc
**     Date/Time : 07/11/08, 1:05
**     Abstract  :
**         This file defines values that are also defined in the precompiled firmware
**         Editing these values will cause unexpected operation
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
                             
#define  IO_MAP_SIZE                         1925     /*This is how big the IOmap is, holds all ins, outs, module status, J1939, J1939 Bam, Variables, EEPROMS*/
#define  CONFIGURATOR_FILES_WRITTEN_WORD     0x0101
#define  MAX_J1708_LENGTH                    30
#define  NUMBER_OF_STATE_MACHINES            100       /*Maximum number of State Machines that can be used */
#define  MAX_RX_MESSAGE_SIZE                 150      /*biggest message it can recieve, Conductor Max = , Programmer Max = */
#define  USE_PAGED_RAM
#define  NUMBER_OF_SCI_LINES                 1        /*this is the number of SCI Lines used on the chip for Sci*/
#define  TOTAL_SERIAL_RX_STRUCUTRES          NUMBER_OF_SCI_LINES + 1
#define  NUMBER_OF_BAM_MESSAGES              8
#define  NUMBER_SPN_PER_BAM                  16

/*Flash size for W25Q128*/
#define  EXTERNAL_FLASH_MAX_PROGRAM_SIZE        0x100
#define  EXTERNAL_FLASH_SECTOR_SIZE             0x1000    /*4KB*/
#define  EXTERNAL_FLASH_SIZE                    0x800000  /*8MB*/
#define  EXTERNAL_FLASH_START_ADDRESS           0x800000
#define  EXTERNAL_FLASH_END_ADDRESS             0xFFFFFF 