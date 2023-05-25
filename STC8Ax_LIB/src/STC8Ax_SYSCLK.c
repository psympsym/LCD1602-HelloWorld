/*-------------------------------------------------------------------
/*      (C) Copyright 2021-2022, nbufe. All Rights Reserved 
/*-------------------------------------------------------------------
/* File name   : STC8Ax_SYSCLK.c
/* Description : STC8Ax 系统时钟函数库
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
#include "STC8Ax_SYSCLK.h"

/* 私有类型定义 -----------------------------------------------------*/
/* None. */

/* 私有宏定义 -------------------------------------------------------*/
/* None. */

/* 私有变量 ---------------------------------------------------------*/
/* None. */

/* 扩展变量 ---------------------------------------------------------*/
/* 系统频率变量 */
uint32_t sysClk_FRE = 0;

/* 私有函数原形 -----------------------------------------------------*/
/* None. */

/* 函数体 -----------------------------------------------------------*/
/**
 * 功能：获取系统时钟频率函数，用于定时器、串口、EEPROM等进行时钟计算。
 * 参数：None
 * 返回：[uint32_t] 时钟频率
 * 说明：这个函数只能获取内部IRC做时钟源时的系统频率，如果你使用的是外部晶振，
 *       请在STC8Ax_CONF.h中配置CFG_SYSCLK_VALUE宏，填写系统时钟频率。
 */
uint32_t Get_SysClk_FRE(void)
{
		uint32_t count;

		EAXSFR();
		/* 频率的偏差,计算出大概数据 */
		count = 24000000UL + ((int32_t)((int32_t)IRTRIM - (int32_t)IRC_24M) * 0xD2F0UL);
		/* 频率太低需要分频 */
		count /= CLKDIV;
		EAXRAM();
		return count;
}

/**
 * 功能：系统时钟配置
 * 参数：None
 * 返回：None
 * 说明：
 */
void STC8Ax_SYSCLK_Config(void)
{
/* 获取系统频率 */
#if (0 == CONF_FOSC)
		sysClk_FRE = Get_SysClk_FRE();
#else
		sysClk_FRE = CONF_FOSC;
	  EAXSFR();
		CLKDIV = 0x00; 							/*< 时钟不分频   */
		CKSEL = 0x01; 							/*< 选择外部晶振 */
		XOSCCR = 0xC0; 							/*< 启动外部晶振 */
		while (!(XOSCCR & 0x01)); 	/*< 等待时钟稳定 */
		EAXRAM();
#endif
}

/**
 * 功能：系统时钟初始化函数
 * 参数：sysClkn 系统时钟初始化结构体句柄，需要在初始化时定义它，并用其地址传参。
 * 返回：None
 * 说明：
 */
void STC8Ax_SYSCLK_Init(const SYSCLK_InitTypeDef* sysClkn)
{
    EAXSFR();
    {
        if(sysClkn -> MCLKSrc != AUTO)
        {
            IRC24MCR &= 0xFE;
            IRC32KCR &= 0x7E;
            XOSCCR &= 0x1E;
            switch(sysClkn -> MCLKSrc)
            {
                case HIRC:
                    CKSEL = 0x00;
                    IRC24MCR |= 0x80;
                    break;
                case XOSC:
                    CKSEL = 0x01;
                    XOSCCR |= 0xC0;
                    break;
                case LIRC:
                    CKSEL = 0x03;
                    IRC32KCR |= 0x80;
                    break;
            }
            while(!((IRC24MCR & 0x01) || (IRC32KCR & 0x01) || (XOSCCR & 0x01)));
            IRTRIM = sysClkn -> IRCTrim;
            LIRTRIM = sysClkn -> LIRCTrim;
            if(sysClkn -> MCLKDiv == 0) sysClkn -> MCLKDiv += 1;
            CLKDIV = sysClkn -> MCLKDiv;
        }
        CKSEL |= sysClkn -> SCLKDiv;
        CKSEL |= sysClkn -> SCLKOutPin << 3;
    }
    EAXRAM();
}

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
