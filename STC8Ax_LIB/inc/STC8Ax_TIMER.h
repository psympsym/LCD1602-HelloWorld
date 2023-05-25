/*--------------------------------------------------------------------
/* File name   : STC8Ax_TIMER.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef	__STC8Ax_TIMER_H__
#define	__STC8Ax_TIMER_H__

/* ����ͷ�ļ� -------------------------------------------------------*/
#include "STC8Ax_REG.h"
#include "STC8Ax_CONF.h"
#include "STC8Ax_SYSCLK.h"

/* ���Ͷ��� ---------------------------------------------------------*/
/* ��ʱ��ͨ�� */
typedef enum
{
    TIM0   = 0x00,  /*!< ��ʱ��ͨ�� P34��*/
    TIM1   = 0x01,  /*!< ��ʱ��ͨ�� P35��*/
    TIM2   = 0x02,  /*!< ��ʱ��ͨ�� P12��*/
    TIM3   = 0x03,  /*!< ��ʱ��ͨ�� P04��*/
    TIM4   = 0x04,  /*!< ��ʱ��ͨ�� P06��*/
} eTIMER_ID;

/* ��ʱ������״̬ö���� */
typedef enum
{
    TIMER_Type_Timer   = 0x00,  /*!< �����ڶ�ʱ�����͡�*/
    TIMER_Type_Counter = 0x01   /*!< �����ڼ��������͡�*/
} eTIMER_Type;


/* ��ʱ������ģʽö���� */
typedef enum
{
    TIMER_16BitAutoReload       = 0x00, /*!< ʮ��λ�Զ���װ��ģʽ��*/
    TIMER_16Bit                 = 0x01, /*!< ʮ��λ�ֶ���װ��ģʽ��*/
    TIMER_8BitAutoReload        = 0x02, /*!< ��λ�Զ���װ��ģʽ��*/
    TIMER_16BitAutoReloadNoMask = 0x03  /*!< ʮ��λ�Զ���װ�ز��ɱ����ģʽ��*/
}	eTIMER_Mode;

/* ��ʱ��ָ������ö���� */
typedef enum
{
    TIMER_Cycle_1T  = 0x00,	/*!< 1Tָ�����ڡ� */
    TIMER_Cycle_12T = 0x01,	/*!< 12Tָ�����ڣ���ʵ��1T��ʮ����Ƶ����*/
}	eTIMER_Cycle;

/* ��ʱ����ʼ���ṹ�� */
typedef struct
{
    eTIMER_Type Type;      	/*!< ��ʱ������״̬��*/
    eTIMER_Mode Mode;      	/*!< ��ʱ������ģʽ��*/
    eTIMER_Cycle TCycle;  	/*!< ��ʱ��ָ�����ڡ�*/
    BOOL ClkOut;            /*!< ��ʱ���ɱ��ʱ���������λ��*/
    uint32_t Time;          /*!< ��ʱ����ʱʱ�䡣*/
    BOOL Run;               /*!< ��ʱ�����п���λ��*/
} TIMER_InitTypeDef;


/* �궨�� -----------------------------------------------------------*/
/*  ��ʱ��2-4����ж������־λ�꺯�� */
#define TIMER2_CLEAR_FLAG()   do{ AUXINTIF &= 0xFE; }while(0)
#define TIMER3_CLEAR_FLAG()   do{ AUXINTIF &= 0xFD; }while(0)
#define TIMER4_CLEAR_FLAG()   do{ AUXINTIF &= 0xFB; }while(0)

/* TIMER0-1ѡ���ж����ȼ��꺯�� */
#define NVIC_TIMER0_PRI(pri)  do{IP = (IP & 0xFD) | ((pri & 0x01) << 1);}while(0)
#define NVIC_TIMER1_PRI(pri) 	do{IP = (IP & 0xF7) | ((pri & 0x01) << 3);}while(0)

/* ��ʱ���жϿ��ؿ��ƺ꺯���� */
#define NVIC_TIMER0_CTRL(run) do{ ET0 = run; }while(0)
#define NVIC_TIMER1_CTRL(run) do{ ET1 = run; }while(0)
#define NVIC_TIMER2_CTRL(run) do{ IE2 = (IE2 & 0xFB) | (run << 2); }while(0)
#define NVIC_TIMER3_CTRL(run) do{ IE2 = (IE2 & 0xDF) | (run << 5); }while(0)
#define NVIC_TIMER4_CTRL(run) do{ IE2 = (IE2 & 0xBF) | (run << 6); }while(0)

/* ��ʱ���������ؿ��ƺ꺯�� */
#define TIMER0_RUN_CTRL(run)  do{ TR0 = run; }while(0)
#define TIMER1_RUN_CTRL(run)  do{ TR1 = run; }while(0)
#define TIMER2_RUN_CTRL(run)  do{AUXR = (AUXR & 0xEF) | (run << 4);  }while(0)
#define TIMER3_RUN_CTRL(run)  do{ T4T3M = (T4T3M & 0xF7) | (run << 3); }while(0)
#define TIMER4_RUN_CTRL(run)  do{ T4T3M = (T4T3M & 0x7F) | (run << 7); }while(0)

/* ��ʱ����Ϊ�ⲿ������ʼ�� */
#define TIMER0_COUNT_INIT()   do{TL0 = 0, TH0 = 0, TMOD |= 0x04,TR0 = 1;}while(0)		
#define TIMER1_COUNT_INIT()   do{TL1 = 0, TH1 = 0, TMOD |= 0x40,TR1 = 1;}while(0)		
#define TIMER2_COUNT_INIT()   do{T2L = 0, T2H = 0, AUXR |= 0x18;}while(0)		
#define TIMER3_COUNT_INIT()   do{T3L = 0, T3H = 0, T4T3M |= 0x0c;}while(0)		
#define TIMER4_COUNT_INIT()   do{T4L = 0, T4H = 0, T4T3M |= 0xc0;}while(0)		

/* �����ʱ���ⲿ����ֵ*/
#define TIMER0_CLEAR_COUNT()  do{TR0 = 0, TH0 = 0, TL0 = 0, TR0 = 1;}while(0)		
#define TIMER1_CLEAR_COUNT()  do{TR1 = 0, TH1 = 0, TL1 = 0, TR1 = 1;}while(0)		
#define TIMER2_CLEAR_COUNT()  do{AUXR &= ~(1 << 4), T2H = 0, T2L = 0, AUXR |= 1 << 4;}while(0)		
#define TIMER3_CLEAR_COUNT()  do{T4T3M &= ~(1 << 3), T3H = 0, T3L = 0, T4T3M |= (1 << 3);}while(0)		
#define TIMER4_CLEAR_COUNT()  do{T4T3M &= ~(1 << 7), T4H = 0, T4L = 0, T4T3M |= (1 << 7);}while(0)		

/* ��ʱ��������������꺯���� */
#define TIMER0_CLEAR_CNT()    do{T0L = 0;  T0H = 0;}while(0)
#define TIMER1_CLEAR_CNT()    do{T1L = 0;  T1H = 0;}while(0)
#define TIMER2_CLEAR_CNT()    do{T2L = 0;  T2H = 0;}while(0)
#define TIMER3_CLEAR_CNT()    do{T3L = 0;  T3H = 0;}while(0)
#define TIMER4_CLEAR_CNT()    do{T4L = 0;  T4H = 0;}while(0)

/* ��ʱ����������װ�غ꺯�� */
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

/* ��չ���� ---------------------------------------------------------*/
/* None. */

/* �������� ---------------------------------------------------------*/
/* ��ʱ��0��ʼ������ */
ErrorStatus TIMER0_Init(const TIMER_InitTypeDef *timerx);
/* ��ʱ��0�жϳ�ʼ������ */
ErrorStatus NVIC_TIMER0_Init(eNVIC_Pri pri, BOOL run);
/* ��ʱ��0���ö�ʱʱ�亯�� */
ErrorStatus TIMER0_SetTime(uint32_t time);
/* ��ʱ��0��Ϊ�ⲿ������ */
void 	TIMER0_CountInit(void);
uint16_t 	TIMER0_GetCount(void);
void 	TIMER0_CountClean(void);

/* ��ʱ��1��ʼ������ */
ErrorStatus TIMER1_Init(const TIMER_InitTypeDef *timerx);
/* ��ʱ��1�жϳ�ʼ������ */
ErrorStatus NVIC_TIMER1_Init(eNVIC_Pri pri, BOOL run);
/* ��ʱ��1���ö�ʱʱ�亯�� */
ErrorStatus TIMER1_SetTime(uint32_t time);
/* ��ʱ��1��Ϊ�ⲿ������ */
void 	TIMER1_CountInit(void);
uint16_t 	TIMER1_GetCount(void);
void 	TIMER1_CountClean(void);

/* ��ʱ��2��ʼ������ */
ErrorStatus TIMER2_Init(const TIMER_InitTypeDef *timerx);
/* ��ʱ��2�жϳ�ʼ������ */
ErrorStatus NVIC_TIMER2_Init(BOOL run);
/* ��ʱ��2���ö�ʱʱ�亯�� */
ErrorStatus TIMER2_SetTime(uint32_t time);
/* ��ʱ��2��Ϊ�ⲿ������ */
void 	TIMER2_CountInit(void);
uint16_t 	TIMER2_GetCount(void);
void 	TIMER2_CountClean(void);

/* ��ʱ��3��ʼ������ */
ErrorStatus TIMER3_Init(const TIMER_InitTypeDef *timerx);
/* ��ʱ��3�жϳ�ʼ������ */
ErrorStatus NVIC_TIMER3_Init(BOOL run);
/* ��ʱ��3���ö�ʱʱ�亯�� */
ErrorStatus TIMER3_SetTime(uint32_t time);
/* ��ʱ��3��Ϊ�ⲿ������ */
void 	TIMER3_CountInit(void);
uint16_t 	TIMER3_GetCount(void);
void 	TIMER3_CountClean(void);

/* ��ʱ��4��ʼ������ */
ErrorStatus TIMER4_Init(const TIMER_InitTypeDef *timerx);
/* ��ʱ��4�жϳ�ʼ������ */
ErrorStatus NVIC_TIMER4_Init(BOOL run);
/* ��ʱ��4���ö�ʱʱ�亯�� */
ErrorStatus TIMER4_SetTime(uint32_t time);
/* ��ʱ��4��Ϊ�ⲿ������ */
void 	TIMER4_CountInit(void);
uint16_t 	TIMER4_GetCount(void);
void 	TIMER4_CountClean(void);

#endif /* __STC8Ax_TIMER_H__ */

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
