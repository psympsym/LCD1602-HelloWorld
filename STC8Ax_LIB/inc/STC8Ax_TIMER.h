/*--------------------------------------------------------------------
/* File name   : STC8Ax_TIMER.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef	__STC8Ax_TIMER_H__
#define	__STC8Ax_TIMER_H__

/* 包含头文件 -------------------------------------------------------*/
#include "STC8Ax_REG.h"
#include "STC8Ax_CONF.h"
#include "STC8Ax_SYSCLK.h"

/* 类型定义 ---------------------------------------------------------*/
/* 定时器通道 */
typedef enum
{
    TIM0   = 0x00,  /*!< 定时器通道 P34。*/
    TIM1   = 0x01,  /*!< 定时器通道 P35。*/
    TIM2   = 0x02,  /*!< 定时器通道 P12。*/
    TIM3   = 0x03,  /*!< 定时器通道 P04。*/
    TIM4   = 0x04,  /*!< 定时器通道 P06。*/
} eTIMER_ID;

/* 定时器类型状态枚举体 */
typedef enum
{
    TIMER_Type_Timer   = 0x00,  /*!< 工作在定时器类型。*/
    TIMER_Type_Counter = 0x01   /*!< 工作在计数器类型。*/
} eTIMER_Type;


/* 定时器工作模式枚举体 */
typedef enum
{
    TIMER_16BitAutoReload       = 0x00, /*!< 十六位自动重装载模式。*/
    TIMER_16Bit                 = 0x01, /*!< 十六位手动重装载模式。*/
    TIMER_8BitAutoReload        = 0x02, /*!< 八位自动重装载模式。*/
    TIMER_16BitAutoReloadNoMask = 0x03  /*!< 十六位自动重装载不可被打断模式。*/
}	eTIMER_Mode;

/* 定时器指令周期枚举体 */
typedef enum
{
    TIMER_Cycle_1T  = 0x00,	/*!< 1T指令周期。 */
    TIMER_Cycle_12T = 0x01,	/*!< 12T指令周期（其实是1T的十二分频）。*/
}	eTIMER_Cycle;

/* 定时器初始化结构体 */
typedef struct
{
    eTIMER_Type Type;      	/*!< 定时器类型状态。*/
    eTIMER_Mode Mode;      	/*!< 定时器工作模式。*/
    eTIMER_Cycle TCycle;  	/*!< 定时器指令周期。*/
    BOOL ClkOut;            /*!< 定时器可编程时钟输出控制位。*/
    uint32_t Time;          /*!< 定时器定时时间。*/
    BOOL Run;               /*!< 定时器运行控制位。*/
} TIMER_InitTypeDef;


/* 宏定义 -----------------------------------------------------------*/
/*  定时器2-4清除中断请求标志位宏函数 */
#define TIMER2_CLEAR_FLAG()   do{ AUXINTIF &= 0xFE; }while(0)
#define TIMER3_CLEAR_FLAG()   do{ AUXINTIF &= 0xFD; }while(0)
#define TIMER4_CLEAR_FLAG()   do{ AUXINTIF &= 0xFB; }while(0)

/* TIMER0-1选择中断优先级宏函数 */
#define NVIC_TIMER0_PRI(pri)  do{IP = (IP & 0xFD) | ((pri & 0x01) << 1);}while(0)
#define NVIC_TIMER1_PRI(pri) 	do{IP = (IP & 0xF7) | ((pri & 0x01) << 3);}while(0)

/* 定时器中断开关控制宏函数。 */
#define NVIC_TIMER0_CTRL(run) do{ ET0 = run; }while(0)
#define NVIC_TIMER1_CTRL(run) do{ ET1 = run; }while(0)
#define NVIC_TIMER2_CTRL(run) do{ IE2 = (IE2 & 0xFB) | (run << 2); }while(0)
#define NVIC_TIMER3_CTRL(run) do{ IE2 = (IE2 & 0xDF) | (run << 5); }while(0)
#define NVIC_TIMER4_CTRL(run) do{ IE2 = (IE2 & 0xBF) | (run << 6); }while(0)

/* 定时器工作开关控制宏函数 */
#define TIMER0_RUN_CTRL(run)  do{ TR0 = run; }while(0)
#define TIMER1_RUN_CTRL(run)  do{ TR1 = run; }while(0)
#define TIMER2_RUN_CTRL(run)  do{AUXR = (AUXR & 0xEF) | (run << 4);  }while(0)
#define TIMER3_RUN_CTRL(run)  do{ T4T3M = (T4T3M & 0xF7) | (run << 3); }while(0)
#define TIMER4_RUN_CTRL(run)  do{ T4T3M = (T4T3M & 0x7F) | (run << 7); }while(0)

/* 定时器作为外部计数初始化 */
#define TIMER0_COUNT_INIT()   do{TL0 = 0, TH0 = 0, TMOD |= 0x04,TR0 = 1;}while(0)		
#define TIMER1_COUNT_INIT()   do{TL1 = 0, TH1 = 0, TMOD |= 0x40,TR1 = 1;}while(0)		
#define TIMER2_COUNT_INIT()   do{T2L = 0, T2H = 0, AUXR |= 0x18;}while(0)		
#define TIMER3_COUNT_INIT()   do{T3L = 0, T3H = 0, T4T3M |= 0x0c;}while(0)		
#define TIMER4_COUNT_INIT()   do{T4L = 0, T4H = 0, T4T3M |= 0xc0;}while(0)		

/* 清除定时器外部计数值*/
#define TIMER0_CLEAR_COUNT()  do{TR0 = 0, TH0 = 0, TL0 = 0, TR0 = 1;}while(0)		
#define TIMER1_CLEAR_COUNT()  do{TR1 = 0, TH1 = 0, TL1 = 0, TR1 = 1;}while(0)		
#define TIMER2_CLEAR_COUNT()  do{AUXR &= ~(1 << 4), T2H = 0, T2L = 0, AUXR |= 1 << 4;}while(0)		
#define TIMER3_CLEAR_COUNT()  do{T4T3M &= ~(1 << 3), T3H = 0, T3L = 0, T4T3M |= (1 << 3);}while(0)		
#define TIMER4_CLEAR_COUNT()  do{T4T3M &= ~(1 << 7), T4H = 0, T4L = 0, T4T3M |= (1 << 7);}while(0)		

/* 定时器计数器重清零宏函数。 */
#define TIMER0_CLEAR_CNT()    do{T0L = 0;  T0H = 0;}while(0)
#define TIMER1_CLEAR_CNT()    do{T1L = 0;  T1H = 0;}while(0)
#define TIMER2_CLEAR_CNT()    do{T2L = 0;  T2H = 0;}while(0)
#define TIMER3_CLEAR_CNT()    do{T3L = 0;  T3H = 0;}while(0)
#define TIMER4_CLEAR_CNT()    do{T4L = 0;  T4H = 0;}while(0)

/* 定时器计数器重装载宏函数 */
#define TIMER0_RELOAD_CNT()  													\
				do{																						\
						T0L = (uint8_t)(G_Time0_CntValue); 				\
						T0H = (uint8_t)(G_Time0_CntValue >> 8);		\
					}while(0)
#define TIMER1_RELOAD_CNT()   												\
				do{																						\
						T1L = (uint8_t)(G_Time1_CntValue); 				\
						T1H = (uint8_t)(G_Time1_CntValue >> 8);		\
					}while(0)

/* 扩展变量 ---------------------------------------------------------*/
/* None. */

/* 函数声明 ---------------------------------------------------------*/
/* 定时器0初始化函数 */
ErrorStatus TIMER0_Init(const TIMER_InitTypeDef *timerx);
/* 定时器0中断初始化函数 */
ErrorStatus NVIC_TIMER0_Init(eNVIC_Pri pri, BOOL run);
/* 定时器0设置定时时间函数 */
ErrorStatus TIMER0_SetTime(uint32_t time);
/* 定时器0设为外部计数器 */
void 	TIMER0_CountInit(void);
uint16_t 	TIMER0_GetCount(void);
void 	TIMER0_CountClean(void);

/* 定时器1初始化函数 */
ErrorStatus TIMER1_Init(const TIMER_InitTypeDef *timerx);
/* 定时器1中断初始化函数 */
ErrorStatus NVIC_TIMER1_Init(eNVIC_Pri pri, BOOL run);
/* 定时器1设置定时时间函数 */
ErrorStatus TIMER1_SetTime(uint32_t time);
/* 定时器1设为外部计数器 */
void 	TIMER1_CountInit(void);
uint16_t 	TIMER1_GetCount(void);
void 	TIMER1_CountClean(void);

/* 定时器2初始化函数 */
ErrorStatus TIMER2_Init(const TIMER_InitTypeDef *timerx);
/* 定时器2中断初始化函数 */
ErrorStatus NVIC_TIMER2_Init(BOOL run);
/* 定时器2设置定时时间函数 */
ErrorStatus TIMER2_SetTime(uint32_t time);
/* 定时器2设为外部计数器 */
void 	TIMER2_CountInit(void);
uint16_t 	TIMER2_GetCount(void);
void 	TIMER2_CountClean(void);

/* 定时器3初始化函数 */
ErrorStatus TIMER3_Init(const TIMER_InitTypeDef *timerx);
/* 定时器3中断初始化函数 */
ErrorStatus NVIC_TIMER3_Init(BOOL run);
/* 定时器3设置定时时间函数 */
ErrorStatus TIMER3_SetTime(uint32_t time);
/* 定时器3设为外部计数器 */
void 	TIMER3_CountInit(void);
uint16_t 	TIMER3_GetCount(void);
void 	TIMER3_CountClean(void);

/* 定时器4初始化函数 */
ErrorStatus TIMER4_Init(const TIMER_InitTypeDef *timerx);
/* 定时器4中断初始化函数 */
ErrorStatus NVIC_TIMER4_Init(BOOL run);
/* 定时器4设置定时时间函数 */
ErrorStatus TIMER4_SetTime(uint32_t time);
/* 定时器4设为外部计数器 */
void 	TIMER4_CountInit(void);
uint16_t 	TIMER4_GetCount(void);
void 	TIMER4_CountClean(void);

#endif /* __STC8Ax_TIMER_H__ */

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
