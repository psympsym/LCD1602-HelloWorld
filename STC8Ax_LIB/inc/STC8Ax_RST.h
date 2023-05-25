/*--------------------------------------------------------------------
/* File name   : STC8Ax_RST.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef __STC8Ax_RST_H_
#define __STC8Ax_RST_H_

/* 包含头文件 -------------------------------------------------------*/
#include "STC8Ax_REG.h"

/* 类型定义 ---------------------------------------------------------*/

/* RST复位方式选择枚举体 */
typedef enum
{
    RST_USER_DATA_KEEP = 0x00,	/*!< 软件复位后，代码从用户程序区执行，
	                                   并且用户数据区中的数据保持不变。*/
    RST_USER_DATA_CLEAN = 0x01 	/*!< 软件复位后，代码从系统的ISP区域执行，
	                                   并且清除用户数据区域中的数据。*/
} eRST_Type;

/* 低压复位的电压临界点选择枚举体 */
typedef enum
{
    LVD_RST_2_2V = 0x00,  /*!< 2.2V */
    LVD_RST_2_4V = 0x01,  /*!< 2.4V */
    LVD_RST_2_7V = 0x02,  /*!< 2.7V */
    LVD_RST_3_0V = 0x03   /*!< 3.0V */
} eLVD_RstDiv;


/* 宏定义 -----------------------------------------------------------*/

/* 使能P54作为复位IO */
#define    RST_P54_ENABLE()      do{RSTCFG |= 0x10;}while(0)
/* 不使能P54作为复位IO */
#define    RST_P54_DISABLE()     do{RSTCFG &= 0xEF;}while(0)


/* 扩展变量 ---------------------------------------------------------*/
/* None. */

/* 函数声明 ---------------------------------------------------------*/

/* 低压复位函数，可以选择不同低压复位标准 */
ErrorStatus LVD_RST_Init(eLVD_RstDiv lvDiv, BOOL run);
/* 软件复位控制函数 */
ErrorStatus SFW_RST_Ctrl(eRST_Type choice, BOOL run);
/* 软件复位自动下载函数 */
void Auto_RST_download(void);

#endif /* __STC8Ax_RST_H_ */

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
