/*--------------------------------------------------------------------
/* File name   : STC8Ax_CONF.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef __STC8Ax_CONF_H__
#define __STC8Ax_CONF_H__

/* 包含头文件 -------------------------------------------------------*/
/* None. */
/* 类型定义 ---------------------------------------------------------*/
/* None. */
/* 宏定义 -----------------------------------------------------------*/

/** MCU型号 */
#define  CONF_MCU_MODEL 	MCU_STC8H3K32S2 

/** 配置系统时钟,设置为0，则自动读取系统频率 */
//#define CONF_FOSC   		0UL				/*< MCU的运行频率 */
//#define CONF_FOSC				5529600UL
//#define CONF_FOSC				11059200UL
//#define CONF_FOSC				12000000UL
//#define CONF_FOSC				22118400UL
#define CONF_FOSC					24000000UL
//#define  CONF_FOSC      36864000UL  
#define  CONF_CLKDIV    	0x02  		/*< 以下参数均用于频率调整 */              
#define  CONF_IRCBAND   	0x03
#define  CONF_VRTRIM    	0x19
#define  CONF_IRTRIM    	0x28
#define  CONF_LIRTRIM   	0x00

/* 精准延时 */
#define CONF_DELAY_BASE   11000UL /*!< 计算延时时间系数 */

/* 扩展变量 ---------------------------------------------------------*/
/* None. */
/* 函数声明 ---------------------------------------------------------*/
/* None. */

#endif /* __STC8Ax_CONF_H__ */

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/

