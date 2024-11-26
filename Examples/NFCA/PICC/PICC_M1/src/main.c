/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2024/07/22
 * Description        : NFC PCD Mifare Classic测试例程
 * Copyright (c) 2024 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include "CH58x_common.h"
#include "wch_nfca_picc_bsp.h"
#include "wch_nfca_picc_m1.h"

/* 每个文件单独debug打印的开关，置0可以禁止本文件内部打印 */
#define DEBUG_PRINT_IN_THIS_FILE 1
#if DEBUG_PRINT_IN_THIS_FILE
    #define PRINTF(...) PRINT(__VA_ARGS__)
#else
    #define PRINTF(...) do {} while (0)
#endif

/*********************************************************************
 * GLOBAL TYPEDEFS
 */

/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 */
int main(void)
{
    UINT16 x;
    uint8_t uid[4] = {0x12, 0x34, 0x56, 0x78};
//    uint8_t uid[4] = {0x78, 0x56, 0x34, 0x12};

    HSECFG_Capacitance(HSECap_18p);
    SetSysClock(CLK_SOURCE_HSE_PLL_78MHz);

#ifdef DEBUG
    GPIOA_SetBits(GPIO_Pin_14);
    GPIOPinRemap(ENABLE, RB_PIN_UART0);
    GPIOA_ModeCfg(GPIO_Pin_15, GPIO_ModeIN_PU);
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeOut_PP_5mA);
    UART0_BaudRateCfg(115200);
    R8_UART0_FCR = (2 << 6) | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN; // FIFO打开，触发点4字节
    R8_UART0_LCR = RB_LCR_WORD_SZ;
    R8_UART0_IER = RB_IER_TXD_EN;
    R8_UART0_DIV = 1;
#endif

    PRINT("NFCA PICC START\n");

    nfca_picc_init();
    PRINT("nfca_picc_init ok\n");

    nfca_picc_m1_enable(uid);

    nfca_picc_start();

    PRINT("wait pcd\n");

    while(1);

    nfca_picc_stop();

}

/******************************** endfile @ main ******************************/
