/*-------------------------------------------------------------------
/*      (C) Copyright 2021-2022, nbufe. All Rights Reserved 
/*-------------------------------------------------------------------
/* File name   : STC8Ax_UART.c
/* Description : STC8Ax 串口函数库
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
#include "STC8Ax_UART.h"

/* 私有类型定义 -----------------------------------------------------*/
/* None. */

/* 私有宏定义 -------------------------------------------------------*/
/* None. */

/* 私有变量 ---------------------------------------------------------*/
/* None. */

/* 扩展变量 ---------------------------------------------------------*/
/* 串口忙标志位，自定义，防止多串口冲突的变量 */
uint8_t G_Uart_Busy_Flg = 0; //Busy flag of receive

/* 私有函数原形 -----------------------------------------------------*/
/* None. */

/* 函数体 -----------------------------------------------------------*/
/**
 * 功能：串口1初始化函数
 * 参数：uartx  串口初始化结构体句柄，初始化时请定义该句柄，并将其地址传参。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus UART1_Init(const UART_InitTypeDef* uartx)
{
    SM0 = uartx -> Mode >> 1, SM1 = uartx -> Mode;
    switch(uartx -> BRTGen)
    {
        case UART_BRT_TIM1:
        {
            TR1 = 0;        //Turn off timer0
            ET1 = 0;        //Ban timer0 interrupt
            AUXR &= 0xFE;   //Select timer 1 as baud rate generator
            TMOD &= 0x0F; 	//Timer 1 is fixed to 16 bit auto reload mode
            AUXR = (AUXR & 0xBF) | ( !uartx -> BRTMode << 6 );
            T1L = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x40)) + 1 )));
            T1H = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x40)) + 1 ))) >> 8;
            TR1 = 1;        //Turn on timer0
            break;
        }
        case UART_BRT_TIM2:
        {
            AUXR &= 0xEF;  //Turn off timer2
            IE2 &= 0xFB;   //Ban timer2 interrupt
            AUXR |= 0x01;  //Select timer2 as baud rate generator
            AUXR = (AUXR & 0xFB) | ( !uartx -> BRTMode << 2 );
            T2L = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x04)) + 1 )));
            T2H = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x04)) + 1 ))) >> 8;
            AUXR |= 0X10;  //Turn on timer2
            break;
        }
        default:
            return ERROR;
    }
    AUXR = (AUXR & 0xDF) | (uartx -> BRTDouble << 5);
    SCON = (SCON & 0xDF) | (uartx -> MulitComm << 5);
    SCON = (SCON & 0xEF) | (uartx -> RxEnable << 4);
    AUXR2 = (AUXR2 & 0xEF) | (uartx -> Relay << 4);
    UART1_CLEAR_BUSY_FLAG();
    return SUCCESS;
}

/**
 * 功能：串口中断初始化函数。
 * 参数：pri 中断优先级。
 *       run 使能控制位。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus NVIC_UART1_Init(eNVIC_Pri pri, BOOL run)
{
    ES = run;
    NVIC_UART1_PRI(pri);
    return SUCCESS;
}

/**
 * 功能：串口发送一个字节函数，
 * 参数：dat 要发送的字节数据。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART1_Send_Byte(uint8_t dat)
{
    while(UART1_GET_BUSY_FLAG());
    UART1_SET_BUSY_FLAG();
    SBUF = dat;
}
/**
 * 功能：串口发送字符串函数
 * 参数： str 要发送的字符串地址。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART1_Send_String(const uint8_t *str)
{
    while(*str != '\0')
    {
        UART1_Send_Byte(*(str++));
    }
}

/**
 * 功能：串口发送数组函数
 * 参数：arry 要发送的数组地址。
 *       len  要发送的数组长度。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART1_Send_Array(const uint8_t *arry, uint16_t len)
{
    while(len--)
    {
        UART1_Send_Byte(*(arry++));
    }
}

/**
 * 功能：串口2初始化函数
 * 参数：uartx  串口初始化结构体句柄，初始化时请定义该句柄，并将其地址传参。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus UART2_Init(const UART_InitTypeDef* uartx)
{
    S2CON = (S2CON & 0x3F) | ((uartx -> Mode & 0x02) << 6);
    if(uartx -> BRTGen == UART_BRT_TIM2)
    {
        AUXR &= 0xEF;  //Turn off timer2
        IE2 &= 0xFB;   //Ban timer2 interrupt
        AUXR = (AUXR & 0xFB) | ( !uartx -> BRTMode << 2 );
        T2L = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x04)) + 1 )));
        T2H = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x04)) + 1 ))) >> 8;
        AUXR |= 0X10;  //Turn on timer2
    }
    else return ERROR;
    S2CON = (S2CON & 0xDF) | (uartx -> MulitComm << 5);
    S2CON = (S2CON & 0xEF) | (uartx -> RxEnable << 4);
    UART2_CLEAR_BUSY_FLAG();
    return SUCCESS;
}

/**
 * 功能：串口中断初始化函数。
 * 参数：pri 中断优先级。
 *       run 使能控制位。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus NVIC_UART2_Init(eNVIC_Pri pri, BOOL run)
{
    IE2 = (IE2 & 0xFE) | (run);
    NVIC_UART2_PRI(pri);
    return SUCCESS;
}

/**
 * 功能：串口发送一个字节函数，
 * 参数：dat 要发送的字节数据。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART2_Send_Byte(uint8_t dat)
{
    while(UART2_GET_BUSY_FLAG());
    UART2_SET_BUSY_FLAG();
    S2BUF = dat;
}
/**
 * 功能：串口发送字符串函数
 * 参数： str 要发送的字符串地址。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART2_Send_String(const uint8_t *str)
{
    while(*str != '\0')
    {
        UART2_Send_Byte(*(str++));
    }
}

/**
 * 功能：串口发送数组函数
 * 参数：arry 要发送的数组地址。
 *       len  要发送的数组长度。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART2_Send_Array(const uint8_t *arry, uint16_t len)
{
    while(len--)
    {
        UART2_Send_Byte(*(arry++));
    }
}

/**
 * 功能：串口3初始化函数
 * 参数：uartx  串口初始化结构体句柄，初始化时请定义该句柄，并将其地址传参。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus UART3_Init(const UART_InitTypeDef* uartx)
{
    S3CON = (S3CON & 0x3F) | ((uartx -> Mode & 0x02) << 6);
    switch(uartx -> BRTGen)
    {
        case UART_BRT_TIM2:
        {
            AUXR &= 0xEF;  //Turn off timer2
            IE2 &= 0xFB;   //Ban timer2 interrupt
            S3CON &= 0xBF;  //Select timer2 as baud rate generator
            AUXR = (AUXR & 0xFB) | ( !uartx -> BRTMode << 2 );
            T2L = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x04)) + 1 )));
            T2H = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x04)) + 1 ))) >> 8;
            AUXR |= 0X10;  //Turn on timer2
            break;
        }
        case UART_BRT_TIM3:
        {
            T4T3M &= 0xF7;  //Turn off timer3
            IE2 &= 0xDF;  //Ban timer3 interrupt
            S3CON |= 0x40;    //Select timer3 as baud rate generator
            T4T3M = (T4T3M & 0xFD) | ( !uartx -> BRTMode << 1 );
            T3L = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(T4T3M & 0x02)) + 1 )));
            T3H = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(T4T3M & 0x02)) + 1 ))) >> 8;
            T4T3M |= 0x08; //Turn on timer3
            break;
        }
        default:
            return ERROR;
    }
    S3CON = (S3CON & 0xDF) | (uartx -> MulitComm << 5);
    S3CON = (S3CON & 0xEF) | (uartx -> RxEnable << 4);
    UART3_CLEAR_BUSY_FLAG();
    return SUCCESS;
}

/**
 * 功能：串口中断初始化函数。
 * 参数：pri 中断优先级。
 *       run 使能控制位。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus NVIC_UART3_Init(BOOL run)
{
    IE2 = (IE2 & 0xF7) | (run << 3);
    return SUCCESS;
}

/**
 * 功能：串口发送一个字节函数，
 * 参数：dat 要发送的字节数据。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART3_Send_Byte(uint8_t dat)
{
    while(UART3_GET_BUSY_FLAG());
    UART3_SET_BUSY_FLAG();
    S3BUF = dat;
}

/**
 * 功能：串口发送字符串函数
 * 参数： str 要发送的字符串地址。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART3_Send_String(const uint8_t *str)
{
    while(*str != '\0')
    {
        UART3_Send_Byte(*(str++));
    }
}

/**
 * 功能：串口发送数组函数
 * 参数：arry 要发送的数组地址。
 *       len  要发送的数组长度。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART3_Send_Array(const uint8_t *arry, uint16_t len)
{
    while(len--)
    {
        UART3_Send_Byte(*(arry++));
    }
}


/**
 * 功能：串口4初始化函数
 * 参数：uartx  串口初始化结构体句柄，初始化时请定义该句柄，并将其地址传参。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus UART4_Init(const UART_InitTypeDef* uartx)
{
    S4CON = (S4CON & 0x3F) | ((uartx -> Mode & 0x02) << 6);
    switch(uartx -> BRTGen)
    {
        case UART_BRT_TIM2:
        {
            AUXR &= 0xEF;  //Turn off timer2
            IE2 &= 0xFB;   //Ban timer2 interrupt
            S4CON &= 0xBF;  //Select timer2 as baud rate generator
            AUXR = (AUXR & 0xFB) | ( !uartx -> BRTMode << 2 );
            T2L = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x04)) + 1 )));
            T2H = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(AUXR & 0x04)) + 1 ))) >> 8;
            AUXR |= 0X10;  //Turn on timer2
            break;
        }
        case UART_BRT_TIM4:
        {
            T4T3M &= 0x7F;  //Turn off timer3
            IE2 &= 0xBF;  //Ban timer4 interrupt
            S4CON |= 0x40;   //Select timer3 as baud rate generator
            T4T3M = (T4T3M & 0xDF) | ( !uartx -> BRTMode << 5 );
            T4L = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(T4T3M & 0x20)) + 1 )));
            T4H = (65536UL - CONF_FOSC / (uartx -> BaudRate * 4 * (11 * (!(T4T3M & 0x20)) + 1 ))) >> 8;
            T4T3M |= 0x80; //Turn on timer4
            break;
        }
        default:
            return ERROR;
    }
    S4CON = (S4CON & 0xDF) | (uartx -> MulitComm << 5);
    S4CON = (S4CON & 0xEF) | (uartx -> RxEnable << 4);
    UART4_CLEAR_BUSY_FLAG();
    return SUCCESS;
}

/**
 * 功能：串口中断初始化函数。
 * 参数：pri 中断优先级。
 *       run 使能控制位。
 * 返回：SUCCESS 返回成功。
 *       ERROR    返回失败。
 * 说明：
 */
ErrorStatus NVIC_UART4_Init(BOOL run)
{
    IE2 = (IE2 & 0xEF) | (run << 4);
    return SUCCESS;
}

/**
 * 功能：串口发送一个字节函数，
 * 参数：dat 要发送的字节数据。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART4_Send_Byte(uint8_t dat)
{
    while(UART4_GET_BUSY_FLAG());
    UART4_SET_BUSY_FLAG();
    S4BUF = dat;
}

/**
* 功能：串口发送字符串函数
* 参数： str 要发送的字符串地址。
* 返回：None.
* 说明：需要开启中断，并在中断服务函数中清除发送标志位。
*/
void UART4_Send_String(const uint8_t *str)
{
    while(*str != '\0')
    {
        UART4_Send_Byte(*(str++));
    }
}

/**
 * 功能：串口发送数组函数
 * 参数：arry 要发送的数组地址。
 *       len  要发送的数组长度。
 * 返回：None.
 * 说明：需要开启中断，并在中断服务函数中清除发送标志位。
 */
void UART4_Send_Array(const uint8_t *arry, uint16_t len)
{
    while(len--)
    {
        UART4_Send_Byte(*(arry++));
    }
}

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
