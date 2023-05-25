/*-----------------------------------------------------------------------------
/* File name   : STC8Ax_CORE.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*-----------------------------------------------------------------------------
**/
#ifndef __STC8Ax_CORE_H_
#define __STC8Ax_CORE_H_

/*  功能状态枚举体 */
typedef enum {FALSE = 0, TRUE = !FALSE} bool, BOOL;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

/* 函数返回状态枚举体 */
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;


/* 外设复用GPIO切换枚举体 */
typedef enum
{
	SW_Port1 = 0x00 ,
	SW_Port2 = 0x01 ,
	SW_Port3 = 0x02 ,
	SW_Port4 = 0x03 
} ePORT_SW;

/* 中断管理优先级枚举体 */
typedef enum
{
  NVIC_PR0  =  0x00,
  NVIC_PR1  =  0x01,
  NVIC_PR2  =  0x02,
  NVIC_PR3  =  0x03
} eNVIC_Pri;

extern void      _nop_     (void);

/*------------------------------------------------------------------*/
/* 中断回调函数         										  				    			*/
/*------------------------------------------------------------------*/
/* interrupt vector */
#define		INT0_VECTOR				0
#define		TIMER0_VECTOR			1
#define		INT1_VECTOR				2
#define		TIMER1_VECTOR			3
#define		UART1_VECTOR			4
#define		ADC_VECTOR				5
#define		LVD_VECTOR				6
#define		PCA_VECTOR				7
#define		UART2_VECTOR			8
#define		SPI_VECTOR				9
#define		INT2_VECTOR				10
#define		INT3_VECTOR				11
#define		TIMER2_VECTOR			12
#define		INT4_VECTOR				16
#define		UART3_VECTOR			17
#define		UART4_VECTOR			18
#define		TIMER3_VECTOR			19
#define		TIMER4_VECTOR			20
#define		CMP_VECTOR				21
#define		PWM_VECTOR				22
#define		PWMFD_VECTOR			23

#define 	I2C_VECTOR        24      //00C3H
#define 	P0INT_VECTOR      37      //012BH
#define 	P1INT_VECTOR      38      //0133H
#define 	P2INT_VECTOR      39      //013BH
#define 	P3INT_VECTOR      40      //0143H
#define 	P4INT_VECTOR      41      //014BH
#define 	P5INT_VECTOR      42      //0153H
#define 	P6INT_VECTOR      43      //015BH
#define 	P7INT_VECTOR      44      //0163H
#define 	M2MBMM_VECTOR     47      //017BH
#define 	ADCBMM_VECTOR     48      //0183H
#define 	SPIBMM_VECTOR     49      //018BH
#define 	U1TXBMM_VECTOR    50      //0193H
#define 	U1RXBMM_VECTOR    51      //019BH
#define 	U2TXBMM_VECTOR    52      //01A3H
#define 	U2RXBMM_VECTOR    53      //01ABH
#define 	U3TXBMM_VECTOR    54      //01B3H
#define 	U3RXBMM_VECTOR    55      //01BBH
#define 	U4TXBMM_VECTOR    56      //01C3H
#define 	U4RXBMM_VECTOR    57      //01CBH
#define 	LCMBMM_VECTOR     58      //01D3H
#define 	LCM_VECTOR        59      //01DBH

/* 使能总中断 */
#define   NVIC_GLOBAL_ENABLE()     		do{_nop_();EA = 1;_nop_();}while(0)

/* 不使能总中断 */
#define   NVIC_GLOBAL_DISABLE()    		do{_nop_();EA = 0;_nop_();}while(0)

#define	 	EXTI0_ISRQ_Handler(void)  	EXTI0_ISR(void) interrupt INT0_VECTOR
#define	 	EXTI1_ISRQ_Handler(void)  	EXTI1_ISR(void) interrupt	INT1_VECTOR
#define	 	EXTI2_ISRQ_Handler(void)  	EXTI2_ISR(void) interrupt	INT2_VECTOR
#define	 	EXTI3_ISRQ_Handler(void)  	EXTI3_ISR(void) interrupt	INT3_VECTOR
#define	 	EXTI4_ISRQ_Handler(void)  	EXTI4_ISR(void) interrupt	INT4_VECTOR

#define 	TIMER0_ISRQ_Handler(void)  	TIMER0_ISR(void) interrupt TIMER0_VECTOR
#define 	TIMER1_ISRQ_Handler(void)  	TIMER1_ISR(void) interrupt TIMER1_VECTOR
#define 	TIMER2_ISRQ_Handler(void)  	TIMER2_ISR(void) interrupt TIMER2_VECTOR
#define 	TIMER3_ISRQ_Handler(void)  	TIMER3_ISR(void) interrupt TIMER3_VECTOR
#define 	TIMER4_ISRQ_Handler(void)  	TIMER4_ISR(void) interrupt TIMER4_VECTOR

#define 	UART1_ISRQ_Handler(void)  	UART1_ISR(void) interrupt  UART1_VECTOR
#define 	UART2_ISRQ_Handler(void)  	UART2_ISR(void) interrupt  UART2_VECTOR
#define 	UART3_ISRQ_Handler(void)  	UART3_ISR(void) interrupt  UART3_VECTOR
#define 	UART4_ISRQ_Handler(void)  	UART4_ISR(void) interrupt  UART4_VECTOR

#define 	ADC_ISRQ_Handler(void)  		ADC_ISR(void) interrupt  	 ADC_VECTOR
#define 	LVD_ISRQ_Handler(void)  		LVD_ISR(void) interrupt  	 LVD_VECTOR
#define 	PCA_ISRQ_Handler(void)  		PCA_ISR(void) interrupt  	 PCA_VECTOR
#define 	SPI_ISRQ_Handler(void)      SPI_ISR(void) interrupt  	 SPI_VECTOR
#define 	CMP_ISRQ_Handler(void)  		CMP_ISR(void) interrupt 	 CMP_VECTOR
#define 	PWM_ISRQ_Handler(void)      PWM_ISR(void) interrupt 	 PWM_VECTOR
#define 	PWMFD_ISRQ_Handler(void)  	PWMFD_ISR(void) interrupt  PWMFD_VECTOR

#endif

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
