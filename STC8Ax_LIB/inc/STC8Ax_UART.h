/*--------------------------------------------------------------------
/* File name   : STC8Ax_UART.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef __STC8Ax_UART_H_
#define __STC8Ax_UART_H_

/* 包含头文件 -------------------------------------------------------*/
#include "STC8Ax_REG.h"
#include "STC8Ax_CONF.h"
#include "STC8Ax_SYSCLK.h"

/* 类型定义 ---------------------------------------------------------*/
/* 串口工作模式枚举体 */
typedef enum
{
    UART_SyncShift       = 0x00, /*!< 同步移位串行工作模式。*/
    UART_8bit_BRTx       = 0x01, /*!< 8位可变波特率工作模式。*/
    UART_9bit_Fixed_BRTx = 0x02, /*!< 9位固定波特率工作模式。*/
    UART_9bit_BRTx       = 0x03  /*!< 9位可变波特率工作模式。*/
} eUART_Mode;

/* 串口波特率发生器枚举体 */
typedef enum
{
    UART_BRT_TIM1 = 0x00,  /*!< 定时器1做波特率发生器。*/
    UART_BRT_TIM2 = 0x01,	 /*!< 定时器2做波特率发生器。*/
    UART_BRT_TIM3 = 0x02,	 /*!< 定时器3做波特率发生器。*/
    UART_BRT_TIM4 = 0x03 	 /*!< 定时器4做波特率发生器。*/
} eUART_BRTGen;

/* 串口波特率发生器指令周期枚举体 */
typedef enum
{
    UART_BRT_1T  = 0x00,  /*!< 1T指令周期。*/
    UART_BRT_12T = 0x01   /*!< 12T指令周期。*/
}	eUART_BRTMode;

/* 串口初始化结构体句柄，初始化时请定义该句柄，并用其地址来传参 */
typedef struct
{
    eUART_Mode Mode;       		/*!< 模式，1T指令周期。*/
    eUART_BRTGen BRTGen;  		/*!< 使用波特率，1T指令周期。*/
    eUART_BRTMode BRTMode;  	/*!< 波特率发生器时钟模式。*/
    BOOL BRTDouble;           /*!< 波特率加倍控制位。*/
    uint32_t BaudRate;        /*!< 波特率值。*/
		BOOL MulitComm;           /*!< 多机通信控制位。*/
    BOOL Relay;               /*!< 中继广播控制位。*/
    BOOL RxEnable;            /*!< 串口接收控制位。*/
} UART_InitTypeDef;


/* 宏定义 -----------------------------------------------------------*/
/* UART中断开关控制宏函数（run  使能控制位） */
#define NVIC_UART1_CTRL(run) 			do{ ES = run; }while(0)
#define NVIC_UART2_CTRL(run)  		do{ IE2 = (IE2 & 0xFE) | (run); }while(0)
#define NVIC_UART3_CTRL(run)  		do{ IE2 = (IE2 & 0xF7) | (run << 3); }while(0)
#define NVIC_UART4_CTRL(run)  		do{ IE2 = (IE2 & 0xEF) | (run << 4); }while(0)

/* UART选择中断优先级宏函数 （pri 中断优先级） */
#define NVIC_UART1_PRI(pri)  			do{IP  = (IP  & 0xEF) | ((pri & 0x01) << 4);}while(0)
#define NVIC_UART2_PRI(pri) 			do{IP2 = (IP2  & 0xFE) | (pri & 0x01);}while(0)


/* 串口切换复用IO宏函数 （port 复用IO枚举体） */
#define GPIO_UART1_SWPort(port)  	do{P_SW1 = (P_SW1 & 0x3F) | (port << 6);}while(0)		/* UART1 使用P30P31/P36P37/P16P17口(默认P30P31)		*/
#define GPIO_UART2_SWPort(port)  	do{P_SW2 = (P_SW2 & 0xFE) | (port);}while(0)				/* UART2 使用P1/P4口(默认P1)	*/
#define GPIO_UART3_SWPort(port)  	do{P_SW2 = (P_SW2 & 0xFD) | (port << 1);}while(0)		/* UART3 使用P0/P5口(默认P0)	*/
#define GPIO_UART4_SWPort(port)  	do{P_SW2 = (P_SW2 & 0xFB) | (port << 2);}while(0)		/* UART4 使用P0/P5口(默认P0)	*/

/* 串口获取忙标志位宏函数，自定义的标志位变量，并非硬件寄存器 */
#define UART1_GET_BUSY_FLAG()    	(G_Uart_Busy_Flg & 0x01)
#define UART2_GET_BUSY_FLAG()    	(G_Uart_Busy_Flg & 0x02)
#define UART3_GET_BUSY_FLAG()    	(G_Uart_Busy_Flg & 0x04)
#define UART4_GET_BUSY_FLAG()    	(G_Uart_Busy_Flg & 0x08)

/* 串口设置忙标志位宏函数，自定义的标志位变量，并非硬件寄存器 */
#define UART1_SET_BUSY_FLAG()    	do{G_Uart_Busy_Flg |= 0x01;}while(0)
#define UART2_SET_BUSY_FLAG()    	do{G_Uart_Busy_Flg |= 0x02;}while(0)
#define UART3_SET_BUSY_FLAG()    	do{G_Uart_Busy_Flg |= 0x04;}while(0)
#define UART4_SET_BUSY_FLAG()    	do{G_Uart_Busy_Flg |= 0x08;}while(0)

/* 串口清除忙标志位宏函数，自定义的标志位变量，并非硬件寄存器 */
#define UART1_CLEAR_BUSY_FLAG()   do{G_Uart_Busy_Flg &= 0xFE;}while(0)
#define UART2_CLEAR_BUSY_FLAG()   do{G_Uart_Busy_Flg &= 0xFD;}while(0)
#define UART3_CLEAR_BUSY_FLAG()   do{G_Uart_Busy_Flg &= 0xFB;}while(0)
#define UART4_CLEAR_BUSY_FLAG()   do{G_Uart_Busy_Flg &= 0xF7;}while(0)

/* 串口1接收一个字节宏函数（byte 字节）*/
#define UART1_RECEIVE_BYTE(byte) 	do{byte = SBUF;}while(0)
#define UART2_RECEIVE_BYTE(byte) 	do{byte = S2BUF;}while(0)
#define UART3_RECEIVE_BYTE(byte) 	do{byte = S3BUF;}while(0)
#define UART4_RECEIVE_BYTE(byte) 	do{byte = S4BUF;}while(0)

/* 串口获取接收标志位宏函数 */
#define UART1_GET_RX_FLAG()    		(SCON  & 0x01)
#define UART2_GET_RX_FLAG()    		(S2CON & 0x01)
#define UART3_GET_RX_FLAG()    		(S3CON & 0x01)
#define UART4_GET_RX_FLAG()    		(S4CON & 0x01)

/* 串口清除接收标志位宏函数 */
#define	UART1_CLEAR_RX_FLAG()  		do{SCON  &= 0xFE;}while(0)
#define	UART2_CLEAR_RX_FLAG()  		do{S2CON &= 0xFE;}while(0)
#define	UART3_CLEAR_RX_FLAG()  		do{S3CON &= 0xFE;}while(0)
#define	UART4_CLEAR_RX_FLAG()  		do{S4CON &= 0xFE;}while(0)

/* 串口1获取发送标志位宏函数 */
#define UART1_GET_TX_FLAG()    		(SCON  & 0x02)
#define UART2_GET_TX_FLAG()    		(S2CON & 0x02)
#define UART3_GET_TX_FLAG()    		(S3CON & 0x02)
#define UART4_GET_TX_FLAG()    		(S4CON & 0x02)

/* 串口清除发送标志位宏函数 */
#define	UART1_CLEAR_TX_FLAG()  		do{SCON  &= 0xFD;}while(0)
#define	UART2_CLEAR_TX_FLAG()  		do{S2CON &= 0xFD;}while(0)
#define	UART3_CLEAR_TX_FLAG()  		do{S3CON &= 0xFD;}while(0)
#define	UART4_CLEAR_TX_FLAG()  		do{S4CON &= 0xFD;}while(0)


/* 扩展变量 ---------------------------------------------------------*/
/*  串口忙标志位，自定义从防止多串口冲突的变量 */
extern uint8_t G_Uart_Busy_Flg;

/* 函数声明 ---------------------------------------------------------*/
/* 串口1初始化函数 */
ErrorStatus UART1_Init(const UART_InitTypeDef *uartx);
/* 串口1中断初始化函数 */
ErrorStatus NVIC_UART1_Init(eNVIC_Pri pri, BOOL run);
/* 串口1发送一个字节函数 */
void UART1_Isr_Send_Byte(uint8_t dat);
/* 串口1发送一个字符串函数 */
void UART1_Isr_Send_String(const uint8_t *str);
/* 串口1发送一个数组函数 */
void UART1_Isr_Send_Array(const uint8_t *str, uint16_t len);

/* 串口2初始化函数 */
ErrorStatus UART2_Init(const UART_InitTypeDef *uartx);
/* 串口2中断初始化函数 */
ErrorStatus NVIC_UART2_Init(eNVIC_Pri pri, BOOL run);
/* 串口2发送一个字节函数 */
void UART2_Isr_Send_Byte(uint8_t dat);
/* 串口2发送一个字符串函数 */
void UART2_Isr_Send_String(const uint8_t *str);
/* 串口2发送一个数组函数 */
void UART2_Isr_Send_Array(const uint8_t *str, uint16_t len);

/* 串口3初始化函数 */
ErrorStatus UART3_Init(const UART_InitTypeDef *uartx);
/* 串口3中断初始化函数 */
ErrorStatus NVIC_UART3_Init(BOOL run);
/* 串口3发送一个字节函数 */
void UART3_Isr_Send_Byte(uint8_t dat);
/* 串口3发送一个字符串函数 */
void UART3_Isr_Send_String(const uint8_t *str);
/* 串口3发送一个数组函数 */
void UART3_Isr_Send_Array(const uint8_t *str, uint16_t len);

/* 串口4初始化函数 */
ErrorStatus UART4_Init(const UART_InitTypeDef *uartx);
/* 串口4中断初始化函数 */
ErrorStatus NVIC_UART4_Init(BOOL run);
/* 串口4发送一个字节函数 */
void UART4_Isr_Send_Byte(uint8_t dat);
/* 串口4发送一个字符串函数 */
void UART4_Isr_Send_String(const uint8_t *str);
/* 串口4发送一个数组函数 */
void UART4_Isr_Send_Array(const uint8_t *str, uint16_t len);

#endif /* __STC8Ax_UART_H_ */

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
