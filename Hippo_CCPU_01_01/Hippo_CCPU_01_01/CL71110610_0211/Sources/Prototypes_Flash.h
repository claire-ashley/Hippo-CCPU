/*
** ###################################################################
**     Filename  : Prototypes_Flas.h
**     Processor : Not applicable
**     FileFormat: V2.00
**     Abstract  :
**         This file contains all the function and structure prototypes 
**       for supporting a Flash for internal and external functions
**
**     (c) Copyright HED,Inc. 2006-2012
**     HED,Inc.
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

/* ##   Used for Processors: XDP512, DG128, C128, C32 ## */ 
/* Flash Error codes */
#define FLASH_COMMAND_SUCCESSFUL  1
#define Flash_Odd_Access         -1
#define Flash_Not_Erased         -2
#define Access_Error             -3
#define Protection_Error         -4
#define Not_StartofSector_Error  -5
#define Flash_Busy               -6
#define Flash_Address_Error      -7

/* ###   Used for Processors: XS128, XS256, XE100, XQ512 ### */
/* Flash Error codes */
#define Flash_Action_Successful   0
#define Flash_No_Divider          1
#define Command_In_Progress       2
#define Not_Start_Sector_Error    3
#define Address_Error             4
#define Flash_Not_ERASED          5
#define Flash_No_Data_Error       6


/* ###   Used for Processors: XS128, XS256, P128 ### */
/*
 * call this function to write a four words into flash
 * Note that the words have to be erased prior to writing
 * address = the global address to write to
 * data = word to be written at the address
 * return = the status of the write
 */
INT8 FlashWritePhrase(UINT16 *far address, UINT16 data1,UINT16 data2,UINT16 data3,UINT16 data4);

/*
 * call this function to write multiple words into flash
 * Note that the words have to be erased prior to writing
 * address_source = the address of the data to be written into Flash
 * far_address_destination = the global address to write to
 * count = the number of words to write
 * return = the status of the write
 */
INT8 FlashWriteBlock(UINT16 *far address_source, UINT16 *far far_address_destination, UINT16 count);

/*
 * call this function to erase a sector of flash
 * Note that the address needs to be at the start of the sector
 * address = the global address of the start of the sector to erase
 * return = the status of the erase
 */
INT8 FlashEraseSector(UINT16 *far far_address);

/*
 * call this function to erase multiple sectors of flash
 * Note that the address needs to be at the start of the sector
 * address = the global address of the start of the sector to erase
 * return = the status of the erase
 */
INT8 FlashEraseBlock(UINT16 *far start_address, UINT16 *far end_address);

/*************** ##   Used for Processors: DP512, DG128, C128, C32 ## *****************/
/*
 * call this function to write a word into flash
 * Note that the word has to be erased prior to writing
 * address = the global address to write to
 * data = word to be written at the address
 * return = the status of the write
 */
INT8 Flash_Write_Word(UINT16 *far address, UINT16 data);

/*
 * call this function to write multiple words into flash
 * Note that the words have to be erased prior to writing
 * address_source = the address of the data to be written into Flash
 * far_address_destination = the global address to write to
 * count = the number of words to write
 * return = the status of the write
 */
INT8 Flash_Write_Block(UINT16 *far address_source, UINT16 *far far_address_destination, UINT16 count);

/*
 * call this function to erase a sector of flash
 * Note that the address needs to be at the start of the sector
 * address = the global address of the start of the sector to erase
 * return = the status of the erase
 */
INT8 Flash_Erase_Sector(UINT16 *far far_address);

/*
 * call this function to erase multiple sectors of flash
 * Note that the address needs to be at the start of the sector
 * address = the global address of the start of the sector to erase
 * return = the status of the erase
 */
INT8 Flash_Erase_Block(UINT16 *far start_address, UINT16 *far end_address);

/*
 * call this function to read external sectors of flash
 * address = the global address of the start of the sector to read
 * data = is the byte value at the address
 * return = the status of the read 0 to -5
 */
int8_t FlashReadUINT8Data(uint32_t address, uint8_t *far data); 
/*
 * call this function to read external sectors of flash
 * address = the global address of the start of the sector to read
 * data = is the word value at the address
 * return = the status of the read 0 to -5
 */
int8_t FlashReadUINT16Data(uint32_t address, uint16_t *far data); 
/*
 * call this function to read external sectors of flash
 * address = the global address of the start of the sector to read
 * data = is the word value at the address
 * return = the status of the read 0 to -5
 */
int8_t FlashReadUINT32Data(uint32_t address, uint32_t *far data);  

