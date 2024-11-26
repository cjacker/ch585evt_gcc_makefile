/********************************** (C) COPYRIGHT  *******************************
 * File Name          : usb_host_iap.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2024/07/31
 * Description        : IAP
*********************************************************************************
* Copyright (c) 2024 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#ifndef __USB_HOST_IAP_H
#define __USB_HOST_IAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CH58x_common.h"
#include "stdio.h"
#include "string.h"
#include <ch585_usbhs_host.h>
#include "usb_host_config.h"
#include "CHRV3UFI.h"

/*******************************************************************************/
/* File Descripton */
/*
 *@Note

    The iap flash. c/iap flash. h file includes the start and end definitions of iap region codes required for iap and apps, as well as the start and end definitions of app region codes,
    The operation function of chip flash.
    ***June 13, 2024***
    1. Version 0.1,
    The complete code includes flash words, half words, byte reads, iap specific flash erasure, writing, programming, reading, and verification.
    All operations involving flash reading, writing, and erasing are protected with DEF-FLASHT-OPERATION_KEY-CODE, DEF-FLASHT-OPERATION_KEY-CODE-0
    Write at the beginning of the main function, and DEF-FLASHT-OPERATION_KEY-CODE_1 is written before each flash operation.
    Use macro definitions to distinguish between iap code and app code, and unify the code for flash operations in iap and app into one file
    IAP code opens all function calls, while app code only opens IAP_VerifyCode-Erase(); Function.
*/

/*******************************************************************************/
/* IAP binary File */
#define DEF_IAP_FILE_NAME                 "/HOST_APP.BIN"

/* IAP Status Definitions */
#define DEF_IAP_SUCCESS                   0x00                                   /* IAP Operation Success */
#define DEF_IAP_DEFAULT                   0xFF                                   /* IAP Operation Default Status */
#define DEF_IAP_ERR_DETECT                0xF1                                   /* IAP Operation, USB device not detected */
#define DEF_IAP_ERR_ENUM                  0xF2                                   /* IAP Operation, Host enumeration failure */
#define DEF_IAP_ERR_FILE                  0xF3                                   /* IAP Operation, File name incorrect or no such file */
#define DEF_IAP_ERR_FLASH                 0xF4                                   /* IAP Operation, Flash operation failure */
#define DEF_IAP_ERR_VERIFY                0xF5                                   /* IAP Operation, Flash data verify error */
#define DEF_IAP_ERR_LENGTH                0xF6                                   /* IAP Operation, Flash data length verify error */

/* IAP Load buffer Definitions */
#define DEF_MAX_IAP_BUFFER_LEN            0x1000                                   /* IAP Load buffer size */

/* Flash page size */
#define DEF_FLASH_PAGE_SIZE               0x1000                                /* Flash Page size, refer to the data-sheet for details */

/* APP CODE ADDR Setting */
#define DEF_APP_CODE_START_ADDR           0x00007000                             /* IAP Flash Operation start address, user code start address */
#define DEF_APP_CODE_END_ADDR             0x00012000                             /* IAP Flash Operation end address, user code end address */
                                                                                 /* Please refer to link.ld file for accuracy flash size, the size here is the smallest available size */

#define DEF_APP_CODE_MAXLEN               (DEF_APP_CODE_END_ADDR-DEF_APP_CODE_START_ADDR) /* IAP Flash Operation size, user code max size */

/* Verify CODE ADDR Setting */
#define DEF_VERIFY_CODE_START_ADDR        0x00006000                             /* IAP Flash verify-code start address */
#define DEF_VERIFY_CODE_END_ADDR          0x00007000
#define DEF_VERIFY_CODE_MAXLEN            (DEF_VERIFY_CODE_END_ADDR-DEF_VERIFY_CODE_START_ADDR) /* IAP Flash verify-code max size */
#define DEF_VERIFY_CODE_LEN               0x10
/* Flash Operation Key Setting */
#define DEF_FLASH_OPERATION_KEY_CODE_0    0x1A86FF00                             /* IAP Flash operation Key-code 0 */
#define DEF_FLASH_OPERATION_KEY_CODE_1    0x55AA55AA                             /* IAP Flash operation Key-code 1 */

/*******************************************************************************/
/* Variable Extrapolation */
/* Flash Operation Key Variables, Operation with DEF_FLASH_OPERATION_KEY_CODE_x to ensure the correctness of flash operation*/
extern volatile uint32_t Flash_Operation_Key0;                                   /* IAP Flash operation Key-code Variables 0 */
extern volatile uint32_t Flash_Operation_Key1;                                   /* IAP Flash operation Key-code Variables 1 */

/*******************************************************************************/
/* Function Extrapolation */
/* Lower operation */
extern uint8_t  FLASH_ReadByte( uint32_t address );
extern uint8_t  IAP_Flash_Erase( uint32_t address, uint32_t length );
extern uint8_t  IAP_Flash_Read( uint32_t address, uint8_t *buff, uint32_t length );
extern uint8_t  IAP_Flash_Write( uint32_t address, uint8_t *buff, uint32_t length );
extern uint32_t IAP_Flash_Verify( uint32_t address, uint8_t *buff, uint32_t length );
extern uint32_t IAP_Flash_Program( uint32_t address, uint8_t *buff, uint32_t length );
extern uint8_t  IAP_VerifyCode_Erase( void );
extern uint32_t IAP_VerifyCode_Write( void );
extern uint32_t IAP_VerifyCode_Check( void );
extern void     IAP_Jump_APP( void );

/* upper operation */
extern void IAP_Main_Deal( void );
extern void IAP_Initialization( void );

#ifdef __cplusplus
}
#endif

#endif


