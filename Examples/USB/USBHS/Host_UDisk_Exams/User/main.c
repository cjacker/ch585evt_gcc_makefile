/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2024/07/31
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2024 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
   1,Exam 1 :
   USBHS host controller enumeration routines for byte manipulation of USB flash drives,
 including file creation, modification, reading and deletion.
   2,Exam 6 :
   USBHS host controller enumeration routines for sector manipulation of USB flash drives,
 including file creation, modification, reading and deletion
   3,Exam 9 :
   The USBHS host controller enumerates the USB flash drive to create folders on the drive,
 including the primary and secondary directories, and the demo files in the corresponding directories.
   4,Exam 11 :
   USBHS host controller enumerates USB flash drives, enabling the enumeration of
 the first 1000 files on the drive.
   5,Exam 13 :USBHS host controller enumerates USB drives to create long filename files,
 or to get long filename files.
  Important: Only FAT12/FAT16/FAT32 formats are supported:

 * If the USB is set to high-speed, an external crystal oscillator is recommended for the clock source.

*/

#include <ch585_usbhs_host.h>
#include "CH58x_common.h"
#include "string.h"
#include "stdio.h"
#include "Udisk_Operation.h"

/* USB Buffer Size */
#ifndef USBHS_MAX_PACKET_SIZE
#define USBHS_MAX_PACKET_SIZE      64
#endif


/* Switches for code demonstration, 1:Enable 0:Disable */
#define  DEF_TEST_FUNC_NUM                DEF_TEST_FUNC_1
#define  DEF_TEST_FUNC_1                  1                          /* Test 1 , Operation for Open/Read/Modify/Delete a file by bytes */
#define  DEF_TEST_FUNC_6                  6                          /* Test 6 , Operation for Open/Read/Modify/Delete a file by sectors */
#define  DEF_TEST_FUNC_9                  9                          /* Test 9 , Operation for creating folders */
#define  DEF_TEST_FUNC_11                 11                         /* Test 11 , Operation for enumeration of the first 1000 files */
#define  DEF_TEST_FUNC_13                 13                         /* Test 13 , Operation for creating long filename files */

void DebugInit( void )
{
    GPIOA_SetBits(GPIO_Pin_14);
    GPIOPinRemap(ENABLE, RB_PIN_UART0);
    GPIOA_ModeCfg(GPIO_Pin_15, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeOut_PP_5mA);
    UART0_DefInit();
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    SetSysClock( CLK_SOURCE_HSE_PLL_62_4MHz );
    DebugInit();

    /* General USB Host UDisk Operation Initialization */

    Udisk_USBH_Initialization( );
    UDisk_Opeation_Flag = 1;

    while( 1 )
    {
#if DEF_TEST_FUNC_NUM == DEF_TEST_FUNC_1
        UDisk_USBH_ByteOperation( );
#elif DEF_TEST_FUNC_NUM == DEF_TEST_FUNC_6
        UDisk_USBH_SectorOperation( );
#elif DEF_TEST_FUNC_NUM == DEF_TEST_FUNC_9
        UDisk_USBH_CreatDirectory( );
#elif DEF_TEST_FUNC_NUM == DEF_TEST_FUNC_11
        UDisk_USBH_EnumFiles( );
#elif DEF_TEST_FUNC_NUM == DEF_TEST_FUNC_13
        UDisk_USBH_Longname( );
#endif
    }
}
