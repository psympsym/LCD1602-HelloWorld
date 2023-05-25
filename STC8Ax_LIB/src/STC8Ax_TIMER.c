/*-------------------------------------------------------------------
/*      (C) Copyright 2021-2022, nbufe. All Rights Reserved 
/*-------------------------------------------------------------------
/* File name   : STC8Ax_TIMER.c
/* Description : STC8Ax 定时器函数库
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
#include	"STC8Ax_TIMER.h"

/* 私有类型定义 -----------------------------------------------------*/
/* None. */

/* 私有宏定义 -------------------------------------------------------*/

/* 定时器工作模式选择宏函数（mode 工作模式，作用域为本文件）*/
#define TIMER0_MODE_CFG(mode)  		do{TMOD = (TMOD & 0xFC) | (mode);}while(0)
#define TIMER1_MODE_CFG(mode)  		do{TMOD = (TMOD & 0xCF) | (mode << 4);}while(0)

/* 定时器指令周期选择宏函数（作用域为本文件）*/
#define TIMER0_TCLK_CFG(tCycle)  	do{AUXR  = (AUXR  & 0x7F) | ( !tCycle << 7 );}while(0)
#define TIMER1_TCLK_CFG(tCycle) 	do{AUXR  = (AUXR  & 0xBF) | ( !tCycle << 6 );}while(0)
#define TIMER2_TCLK_CFG(tCycle) 	do{AUXR  = (AUXR  & 0xFB) | ( !tCycle << 2 );}while(0)
#define TIMER3_TCLK_CFG(tCycle) 	do{T4T3M = (T4T3M & 0xFD) | ( !tCycle << 1 );}while(0)
#define TIMER4_TCLK_CFG(tCycle) 	do{T4T3M = (T4T3M & 0xDF) | ( !tCycle << 5 );}while(0)

/* 定时器定时时间设置函数（作用域为本文件）*/
#define TIMER0_TIM_CFG(time)                           \
    do{ time = (65536UL - (sysClk_FRE / (1000000UL /  time  * (11 * (!(AUXR & 0x80)) + 1)) ) );         \
        G_Time0_CntValue = time;                           \
    }while(0)
		
#define TIMER1_TIM_CFG(time)                           \
    do{ time = (65536UL - (sysClk_FRE / (1000000UL /  time  * (11 * (!(AUXR & 0x40)) + 1)) ) );         \
        G_Time1_CntValue = time;                           \
    }while(0)
		
#define TIMER2_TIM_CFG(time)                           \
    do{ time = (65536UL - (sysClk_FRE / (1000000UL /  time  * (11 * (!(AUXR & 0x04)) + 1)) ) );         \
    }while(0)
		
#define TIMER3_TIM_CFG(time)                           \
    do{ time = (65536UL - (sysClk_FRE / (1000000UL /  time  * (11 * (!(T4T3M & 0x02)) + 1)) ) );        \
    }while(0)
		
#define TIMER4_TIM_CFG(time)                           \
    do{ time = (65536UL - (sysClk_FRE / (1000000UL /  time  * (11 * (!(T4T3M & 0x20)) + 1)) ) );         \
    }while(0)

/* 私有变量 ---------------------------------------------------------*/
/* None. */

/* 扩展变量 ---------------------------------------------------------*/
uint32_t G_Time0_CntValue = 0;
uint32_t G_Time1_CntValue = 0;

/* 私有函数原形 -----------------------------------------------------*/
/* None. */

/* 函数体 -----------------------------------------------------------*/
/**
 * 功能：定时器0初始化函数。
 * 参数：timerx  定时器初始化结构体句柄，初始化时请定义该句柄，并将其地址传参。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus TIMER0_Init(const TIMER_InitTypeDef* timerx)
{
		TR0 = 0; //Turn off Timer0
		TMOD = (TMOD & 0xFB) | (timerx -> Type << 2);
		TIMER0_MODE_CFG(timerx -> Mode);
		TIMER0_TCLK_CFG(timerx -> TCycle);
		TIMER0_TIM_CFG(timerx -> Time);
		if(timerx -> Mode == TIMER_8BitAutoReload) 
				T0L = (uint8_t)(timerx -> Time), T0H = (uint8_t)(timerx -> Time); 
		else                                       
				T0L = (uint8_t)(timerx -> Time), T0H = (uint8_t)(timerx -> Time >> 8);
		INTCLKO = (INTCLKO & 0xFE) | (timerx -> ClkOut);
		TR0 = timerx -> Run;
		return SUCCESS;
}

/**
 * 功能：定时器0中断初始化函数。
 * 参数：pri 中断优先级。
 *       run 使能控制位。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus NVIC_TIMER0_Init(eNVIC_Pri pri, BOOL run)
{
		ET0 = run;
		NVIC_TIMER0_PRI(pri);
		return SUCCESS;
}

/**
 * 功能：定时器0设置定时时间函数。
 * 参数：time 定时时间。。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus TIMER0_SetTime(uint32_t time)
{
		TIMER0_TIM_CFG(time);
		if((TMOD & 0x03) == 0x02) T0L = (uint8_t)(time), T0H = (uint8_t)(time);
		else              T0L = (uint8_t)(time), T0H = (uint8_t)(time >> 8);
		return SUCCESS;
}


/**
 * 功能：获取定时器0外部计数值
 * 参数：None
 * 返回：[uint16_t]返回计数值
 * 说明：
 */
uint16_t TIMER0_GetCount(void)
{
		uint16 dat;
		dat = (uint8)T0H << 8, dat = ((uint8)T0L) | dat;
		return dat;
}

/**
 * 功能：定时器1初始化函数。
 * 参数：timerx  定时器初始化结构体句柄，初始化时请定义该句柄，并将其地址传参。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus TIMER1_Init(const TIMER_InitTypeDef* timerx)
{
		TR1 = 0; //Turn off Timer1
		if(timerx -> Mode != TIMER_16BitAutoReloadNoMask) TIMER1_MODE_CFG(timerx -> Mode);
		else return ERROR;
		TMOD = (TMOD & 0xBF) | (timerx -> Type << 6);
		TIMER1_TCLK_CFG(timerx -> TCycle);
		TIMER1_TIM_CFG(timerx -> Time);
		if(timerx -> Mode == TIMER_8BitAutoReload) 
				T1L = (uint8_t)(timerx -> Time), T1H = (uint8_t)(timerx -> Time);
		else                                       
				T1L = (uint8_t)(timerx -> Time), T1H = (uint8_t)(timerx -> Time >> 8);
		INTCLKO = (INTCLKO & 0xFD) | (timerx -> ClkOut << 1);
		TF1 = 0; //Clear Flag
		TR1 = timerx -> Run;
		return SUCCESS;
}

/**
 * 功能：定时器1中断初始化函数。
 * 参数：pri 中断优先级。
 *       run 使能控制位。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus NVIC_TIMER1_Init(eNVIC_Pri pri, BOOL run)
{
		ET1 = run;
		NVIC_TIMER1_PRI(pri);
		return SUCCESS;
}

/**
 * 功能：定时器1设置定时时间函数。
 * 参数：time 定时时间。。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus TIMER1_SetTime(uint32_t time)
{
		TIMER0_TIM_CFG(time);
		if((TMOD & 0x30) == 0x20) T1L = (uint8_t)(time), T1H = (uint8_t)(time);
		else              T1L = (uint8_t)(time), T1H = (uint8_t)(time >> 8);
		return SUCCESS;
}

/**
 * 功能：获取定时器1外部计数值
 * 参数：None
 * 返回：[uint16_t]返回计数值
 * 说明：
 */
uint16_t TIMER1_GetCount(void)
{
		uint16 dat;
		dat = (uint8)T1H << 8, dat = ((uint8)T1L) | dat;
		return dat;
}	

/**
 * 功能：定时器2初始化函数。
 * 参数：timerx  定时器初始化结构体句柄，初始化时请定义该句柄，并将其地址传参。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus TIMER2_Init(const TIMER_InitTypeDef* timerx)
{
		AUXR &= 0xEF; //Turn off timer2
		AUXR = (AUXR & 0xF7) | (timerx -> Type << 3);
		TIMER2_TCLK_CFG(timerx -> TCycle);
		TIMER2_TIM_CFG(timerx -> Time);
		T2L = (uint8_t)(timerx -> Time);
		T2H = (uint8_t)(timerx -> Time >> 8);
		INTCLKO = (INTCLKO & 0xFB) | (timerx -> ClkOut << 2);
		AUXR = (AUXR & 0xEF) | (timerx -> Run << 4);
		return SUCCESS;
}

/**
 * 功能：定时器2中断初始化函数。
 * 参数：pri 中断优先级。
 *       run 使能控制位。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus NVIC_TIMER2_Init(BOOL run)
{
		IE2 = (IE2 & 0xFB) | (run << 2);
		return SUCCESS;
}

/**
 * 功能：定时器2设置定时时间函数。
 * 参数：time 定时时间。。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus TIMER2_SetTime(uint32_t time)
{
		TIMER2_TIM_CFG(time);
		T2L = (uint8_t)(time), T2H = (uint8_t)(time >> 8);
		return SUCCESS;
}
	

/**
 * 功能：获取定时器2外部计数值
 * 参数：None
 * 返回：[uint16_t]返回计数值
 * 说明：
 */
uint16_t TIMER2_GetCount(void)
{
		uint16 dat;
		dat = (uint8)T2H << 8, dat = ((uint8)T2L) | dat;
		return dat;
}

/**
 * 功能：定时器3初始化函数。
 * 参数：timerx  定时器初始化结构体句柄，初始化时请定义该句柄，并将其地址传参。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus TIMER3_Init(const TIMER_InitTypeDef* timerx)
{
		T4T3M &= 0XF7;//Turn off timer3
		T4T3M = (T4T3M & 0xFB) | (timerx -> Type << 2);
		TIMER3_TCLK_CFG(timerx -> TCycle);
		TIMER3_TIM_CFG(timerx -> Time);
		T3L = (uint8_t)(timerx -> Time);
		T3H = (uint8_t)(timerx -> Time >> 8);
		T4T3M = (T4T3M & 0xFE) | (timerx -> ClkOut);
		T4T3M = (T4T3M & 0xF7) | (timerx -> Run << 3);
		return SUCCESS;
}

/**
 * 功能：定时器3中断初始化函数。
 * 参数：pri 中断优先级。
 *       run 使能控制位。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus NVIC_TIMER3_Init(BOOL run)
{
		IE2 = (IE2 & 0xDF) | (run << 5);
		return SUCCESS;
}

/**
 * 功能：定时器3设置定时时间函数。
 * 参数：time 定时时间。。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus TIMER3_SetTime(uint32_t time)
{
		TIMER3_TIM_CFG(time);
		T3L = (uint8_t)(time), T3H = (uint8_t)(time >> 8);
		return SUCCESS;
}

/**
 * 功能：获取定时器3外部计数值
 * 参数：None
 * 返回：None
 * 说明：
 */
uint16_t TIMER3_GetCount(void)
{
		uint16 dat;

		dat = (uint8)T3H << 8, dat = ((uint8)T3L) | dat;
		return dat;
}

/**
 * 功能：定时器4初始化函数。
 * 参数：timerx  定时器初始化结构体句柄，初始化时请定义该句柄，并将其地址传参。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus TIMER4_Init(const TIMER_InitTypeDef* timerx)
{
		T4T3M &= 0X7F; //Turn off timer4
		T4T3M = (T4T3M & 0xBF) | (timerx -> Type << 6);
		TIMER4_TCLK_CFG(timerx -> TCycle);
		TIMER4_TIM_CFG(timerx -> Time);
		T4L = (uint8_t)(timerx -> Time);
		T4H = (uint8_t)(timerx -> Time >> 8);
		T4T3M = (T4T3M & 0xEF) | (timerx -> ClkOut << 4);
		T4T3M = (T4T3M & 0x7F) | (timerx -> Run << 7);
		return SUCCESS;
}

/**
 * 功能：定时器4中断初始化函数。
 * 参数：pri 中断优先级。
 *       run 使能控制位。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus NVIC_TIMER4_Init(BOOL run)
{
		IE2 = (IE2 & 0xBF) | (run << 6);
		return SUCCESS;
}

/**
 * 功能：定时器4设置定时时间函数。
 * 参数：time 定时时间。。
 * 返回：SUCCESS 返回成功。
 *       ERROR   返回失败。
 * 说明：
 */
ErrorStatus TIMER4_SetTime(uint32_t time)
{
		TIMER4_TIM_CFG(time);
		T4L = (uint8_t)(time), T4H = (uint8_t)(time >> 8);
		return SUCCESS;
}

/**
 * 功能：获取定时器4外部计数值
 * 参数：None
 * 返回：[uint16_t]返回计数值
 * 说明：
 */
uint16_t TIMER4_GetCount(void)
{
		uint16 dat;

		dat = (uint8)T4H << 8, dat = ((uint8)T4L) | dat;
		return dat;
}


/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
