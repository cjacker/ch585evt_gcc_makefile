/********************************** (C) COPYRIGHT *******************************
 * File Name          : SW_CDROM.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2024/07/31
 * Description        : header file for CD-ROM.c
*********************************************************************************
* Copyright (c) 2024 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "stdio.h"
#include "stdlib.h"

#ifdef __cplusplus
 extern "C" {
#endif 

/******************************************************************************/
/* BulkOnly Mass Storage Class requst */
#define CMD_CDROM_RESET                 0xFF
#define CMD_CDROM_GET_MAX_LUN           0xFE

/******************************************************************************/
/* USB Mass Storage Class SCSI Command */
#define CMD_U_TEST_READY              	0x00
#define CMD_U_REZERO_UNIT             	0x01
#define CMD_U_REQUEST_SENSE           	0x03
#define CMD_U_FORMAT_UNIT             	0x04
#define CMD_U_INQUIRY             		0x12
#define CMD_U_MODE_SELECT             	0x15
#define CMD_U_RELEASE	             	0x17
#define CMD_U_MODE_SENSE	            0x1A
#define CMD_U_START_STOP	            0x1B
#define CMD_U_SEND_DIAG	  	 	        0x1D
#define CMD_U_PREVT_REMOVE	  	 	    0x1E
#define CMD_U_READ_FORMAT_CAPACITY	  	0x23
#define CMD_U_READ_CAPACITY	  	        0x25
#define CMD_U_READ10	  				0x28
#define CMD_U_WRITE10	  				0x2A
#define CMD_U_SEEK10	  				0x2B
#define CMD_U_WR_VERIFY10	  			0x2E
#define CMD_U_VERIFY10	  				0x2F
#define CMD_U_SYNC_CACHE	  			0x35
#define CMD_U_READ_TOC	  				0x43
#define CMD_U_MODE_SENSE2	  			0x5A
#define CMD_U_READ12	  				0xA8
#define CMD_U_WRITE12	  				0xAA

/******************************************************************************/
#define MY_CDROM_SIZE  0x00000040

/******************************************************************************/

#define DEF_DEBUG_PRINTF           1

#define DEF_CFG_DISK_SEC_SIZE          512                                          /* Disk sector size */
#define DEF_FLASH_SECTOR_SIZE          4096                                         /* flash sector size */
#define DEF_CDROM_SECTOR_SIZE          DEF_CFG_DISK_SEC_SIZE                        /* CDROM sector size */

#define DEF_CDROM_PACK_512    	       512
#define DEF_CDROM_PACK_64              64

/******************************************************************************/
/* Current cd-rom status related macro definition */
#define DEF_CDROM_EN_FLAG              0x01

/******************************************************************************/
/* Current cd-rom transfer status related macro definitions */
#define DEF_CDROM_BLUCK_UP_FLAG        0x01
#define DEF_CDROM_BLUCK_DOWN_FLAG      0x02
#define DEF_CDROM_CSW_UP_FLAG  	       0x04

/******************************************************************************/
/* BulkOnly */
typedef union _BULK_ONLY_CMD 
{
	uint8_t buf[ 31 ];
	struct 
	{
		uint8_t mCBW_Sig[ 4 ];
		uint8_t mCBW_Tag[ 4 ];
		uint8_t mCBW_DataLen[ 4 ];
		uint8_t mCBW_Flag;
		uint8_t mCBW_LUN;
		uint8_t mCBW_CB_Len;
		uint8_t mCBW_CB_Buf[ 16 ];
	} mCBW;
	struct
	{
		uint8_t mCSW_Sig[ 4 ];
		uint8_t mCSW_Tag[ 4 ];
		uint8_t mCSW_Residue[ 4 ];
		uint8_t mCSW_Status;
	} mCSW;
	struct 
	{
		uint8_t ErrorCode;
		uint8_t Reserved1;
		uint8_t SenseKey;
		uint8_t Information[ 4 ];
		uint8_t SenseLength;
		uint8_t Reserved2[ 4 ];
		uint8_t SenseCode;
		uint8_t SenseCodeQua;
		uint8_t Reserved3[ 4 ];
	}ReqSense;												 
} BULK_ONLY_CMD;

/******************************************************************************/
/* Variable Definition */
extern volatile uint8_t  CDROM_CBW_Tag_Save[ 4 ];
extern volatile uint8_t  CDROM_Sense_Key;
extern volatile uint8_t  CDROM_Sense_ASC;
extern volatile uint8_t  CDROM_CSW_Status;

extern volatile uint32_t CDROM_Transfer_DataLen;
extern volatile uint32_t CDROM_Cur_Sec_Lba;
extern volatile uint16_t CDROM_Sec_Pack_Count;
extern volatile uint16_t CDROM_Pack_Size;

extern BULK_ONLY_CMD	mBOC;

extern volatile uint8_t  CDROM_Status;
extern volatile uint8_t  CDROM_Transfer_Status;
extern volatile uint32_t CDROM_Capability;

extern uint8_t  CDROM_Inquity_Tab[ ];
extern uint8_t  CDROM_Rd_Format_Capacity[ ];
extern uint8_t  CDROM_Rd_Capacity[ ];
extern uint8_t  CDROM_Mode_Sense_1A[ ];
extern uint8_t  CDROM_Mode_Senese_5A[ ];

/******************************************************************************/
/* external functions */
extern void CDROM_CMD_Deal_Status( uint8_t key, uint8_t asc, uint8_t status );
extern void CDROM_CMD_Deal_Fail( void );
extern void CDROM_SCSI_CMD_Deal( void );
extern void CDROM_Bulk_UpData( void );
extern void CDROM_Up_CSW( void );
extern void CDROM_Up_OnePack( void );
extern void CDROM_Out_EP_Deal( uint8_t *pbuf, uint16_t packlen );
extern void CDROM_In_EP_Deal( void );
extern void CDROM_Down_OnePack( uint8_t *pbuf, uint16_t packlen );

#ifdef __cplusplus
}
#endif
