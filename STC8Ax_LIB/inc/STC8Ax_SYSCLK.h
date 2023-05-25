/*--------------------------------------------------------------------
/* File name   : STC8Ax_SYSCLK.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef __STC8Ax_SYSCLK_H_
#define __STC8Ax_SYSCLK_H_

/* 包含头文件 -------------------------------------------------------*/
#include "STC8Ax_REG.h"
#include "STC8Ax_CONF.h"

/* 类型定义 ---------------------------------------------------------*/
/* 系统主时钟源枚举体 */
typedef enum
{
	AUTO = 0x00,   /*!< 由STC-ISP助手设置   */
	HIRC = 0x01,   /*!< 选择内部高速IRC时钟 */
	LIRC = 0x02,   /*!< 选择内部32K时钟     */
  XOSC = 0x04    /*!< 选择外部晶振        */
} eSCLK_Type;

/* IRC频率微调枚举体 */
typedef enum
{
	TRIM0 = 0x00, /*!< 微调等级0 */
	TRIM1 = 0x01, /*!< 微调等级1 */
	TRIM2 = 0x02, /*!< 微调等级2 */
  TRIM3 = 0x03  /*!< 微调等级3 */
} eLIRC_Trim;

/* 系统时钟输出引脚枚举体 */
typedef enum
{
	SCLK_OUT_P54 = 0x00, /*!< 输出时钟到P54 */
	SCLK_OUT_P16 = 0x01  /*!< 输出时钟到P16 */
} eSCLK_OutPin;

/* 系统时钟初始化结构体句柄，需要在函数初始化时定义它，并用其地址传参 */
typedef struct
{
    eSCLK_Type 			MCLKSrc;  		/*!< 主时钟源 					*/
    uint8_t 				IRCTrim;   		/*!< IRC时钟频率调整  	*/
    eLIRC_Trim 			LIRCTrim;  		/*!< IRC时钟频率微调 		*/
    uint8_t 				MCLKDiv;  		/*!< 主时钟分频 				*/
    uint8_t 				SCLKDiv;  		/*!< 系统时钟分频 			*/
    eSCLK_OutPin 		SCLKOutPin; 	/*!< 选择系统时钟输出脚 */

} SYSCLK_InitTypeDef;

/* 宏定义 -----------------------------------------------------------*/
//TIM_Clock_Division_CKD
#define     SYSCLK_DIV1     0x10
#define     SYSCLK_DIV2     0x20
#define     SYSCLK_DIV4     0x40
#define     SYSCLK_DIV8     0x70
#define    SYSCLK_DIV16     0x90
#define    SYSCLK_DIV32     0xB0
#define    SYSCLK_DIV64     0xD0
#define   SYSCLK_DIV128     0xF0

/* 扩展变量 ---------------------------------------------------------*/
/* 系统频率变量 */
extern uint32_t sysClk_FRE;

/* 函数声明 ---------------------------------------------------------*/
/* 系统时钟初始化函数 */
void STC8Ax_SYSCLK_Init(const SYSCLK_InitTypeDef *sysClkn);
/* 获取系统时钟频率函数 */
uint32_t Get_SysClk_FRE(void);
/* 系统时钟配置函数 */
void STC8Ax_SYSCLK_Config(void);
#endif /* __STC8Ax_SYSCLK_H_ */

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
