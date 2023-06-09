/*-------------------------------------------------------------------
/*      (C) Copyright 2023, PSYM. All Rights Reserved 
/*-------------------------------------------------------------------
/* File name   : System_init.c
/* Description : 
/* Author      : PSYM
/*-------------------------------------------------------------------
/* Update note:
/* -----------   -----------   --------------------------------------
/*    Date         Author                       Note
/* -----------   -----------   --------------------------------------
/* 2023-05-25,     psym
/*   14:06
**/

/* 包含头文件 -------------------------------------------------------*/
#include "System_init.h"
#include "STC8Ax_GPIO.h"

/* 私有类型定义 -----------------------------------------------------*/
/* None. */

/* 私有宏定义 -------------------------------------------------------*/
/* None. */

/* 私有变量 ---------------------------------------------------------*/
/* None. */

/* 扩展变量 ---------------------------------------------------------*/
/* None. */

/* 私有函数原形 -----------------------------------------------------*/
/* None. */

/* 函数体 -----------------------------------------------------------*/

/* 第一区 初始化单片机 */
/**
 * 功能：初始化单片机引脚
 * 参数：None
 * 返回：None
 * 说明：初始化P1 P2 P5引脚
 */
void System_Init()
{
    GPIO_Init(GPIO_P0, Pin_All, GPIO_MODE_OUT_PP);

    // 将P1所有引脚配置为推挽输出模式
    GPIO_Init(GPIO_P1, Pin_All, GPIO_MODE_OUT_PP);

    // 将P2所有引脚配置为准双向口输出模式
    GPIO_Init(GPIO_P2, Pin_All, GPIO_MODE_WEAK_PULL);

    // 初始化LCD显示屏
    LCD1602_Init();
    Time0_Config();
}

/* 第二区 初始化外围 */
/**
* 功能：初始化定时器
* 参数：None
* 返回：None
* 说明：
*/
void Peripheral_Init() // 初始化外围
{
   AUXR &= 0x7F; // 定时器时钟12T模式
   EA = 1; // 开总中断
}
/*>>>>>>>>>> (C) COPYRIGHT PSYM <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
