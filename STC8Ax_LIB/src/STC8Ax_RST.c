/*-------------------------------------------------------------------
/*      (C) Copyright 2021-2022, nbufe. All Rights Reserved 
/*-------------------------------------------------------------------
/* File name   : STC8Ax_RST.c
/* Description : STC8Ax RST函数库
/* Author      : nbufe
/* Update date : 2021.12.15
/*-------------------------------------------------------------------
/* Update note:
/* ---------   -----------   ----------------------------------------
/*   Date        Author                       Note
/* ---------   -----------   ----------------------------------------
/*  
/*
**/

/* 包含头文件 -------------------------------------------------------*/
#include	"STC8Ax_RST.h"

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
/**
 * 功能：低压复位函数，可以选择不同低压复位标准
 * 参数：lvDiv   低压复位标准
 *       run     使能控制位。
 * 返回：SUCCESS 返回成功
 *       FSC_FAIL    返回失败
 * 说明：
 */
ErrorStatus LVD_RST_Init(eLVD_RstDiv lvDiv, BOOL run)
{
    RSTCFG = (RSTCFG & 0xFC) | lvDiv;
    RSTCFG = (RSTCFG & 0xEF) | (run << 6);
    return SUCCESS;
}

/**
 * 功能：软件复位控制函数
 * 参数：choice   复位方式选择
 *       run      使能控制位。
 * 返回：SUCCESS 返回成功
 *       FSC_FAIL    返回失败
 * 说明：需要在串口中断里调用，需要在STC-ISP助手里设置下载口令：10个0x7F。
 */
ErrorStatus SFW_RST_Ctrl(eRST_Type choice, BOOL run)
{
    IAP_CONTR = (IAP_CONTR & 0xBF) | (choice << 6);
    IAP_CONTR = (IAP_CONTR & 0xDF) | (run << 5);
    return SUCCESS;
}

/**
 * 功能：软件复位自动下载函数
 * 参数：None.
 * 返回：None
 * 说明：需要在串口中断里调用，需要在STC-ISP助手里设置下载口令：10个0x7F。
 */
void Auto_RST_download(void)
{
    static uint8_t semCont = 0;
    if(SBUF == 0x7F || SBUF == 0x80)
    {
        if(++semCont >= 10)
        {
            semCont = 0;
            IAP_CONTR = 0x60;
        }
    }
    else
    {
        semCont = 0;
    }
}

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
