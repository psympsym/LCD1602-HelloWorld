/*--------------------------------------------------------------------
/* File name   : STC8Ax_UART.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef __STC8Ax_UART_H_
#define __STC8Ax_UART_H_

/* ����ͷ�ļ� -------------------------------------------------------*/
#include "STC8Ax_REG.h"
#include "STC8Ax_CONF.h"
#include "STC8Ax_SYSCLK.h"

/* ���Ͷ��� ---------------------------------------------------------*/
/* ���ڹ���ģʽö���� */
typedef enum
{
    UART_SyncShift       = 0x00, /*!< ͬ����λ���й���ģʽ��*/
    UART_8bit_BRTx       = 0x01, /*!< 8λ�ɱ䲨���ʹ���ģʽ��*/
    UART_9bit_Fixed_BRTx = 0x02, /*!< 9λ�̶������ʹ���ģʽ��*/
    UART_9bit_BRTx       = 0x03  /*!< 9λ�ɱ䲨���ʹ���ģʽ��*/
} eUART_Mode;

/* ���ڲ����ʷ�����ö���� */
typedef enum
{
    UART_BRT_TIM1 = 0x00,  /*!< ��ʱ��1�������ʷ�������*/
    UART_BRT_TIM2 = 0x01,	 /*!< ��ʱ��2�������ʷ�������*/
    UART_BRT_TIM3 = 0x02,	 /*!< ��ʱ��3�������ʷ�������*/
    UART_BRT_TIM4 = 0x03 	 /*!< ��ʱ��4�������ʷ�������*/
} eUART_BRTGen;

/* ���ڲ����ʷ�����ָ������ö���� */
typedef enum
{
    UART_BRT_1T  = 0x00,  /*!< 1Tָ�����ڡ�*/
    UART_BRT_12T = 0x01   /*!< 12Tָ�����ڡ�*/
}	eUART_BRTMode;

/* ���ڳ�ʼ���ṹ��������ʼ��ʱ�붨��þ�����������ַ������ */
typedef struct
{
    eUART_Mode Mode;       		/*!< ģʽ��1Tָ�����ڡ�*/
    eUART_BRTGen BRTGen;  		/*!< ʹ�ò����ʣ�1Tָ�����ڡ�*/
    eUART_BRTMode BRTMode;  	/*!< �����ʷ�����ʱ��ģʽ��*/
    BOOL BRTDouble;           /*!< �����ʼӱ�����λ��*/
    uint32_t BaudRate;        /*!< ������ֵ��*/
		BOOL MulitComm;           /*!< ���ͨ�ſ���λ��*/
    BOOL Relay;               /*!< �м̹㲥����λ��*/
    BOOL RxEnable;            /*!< ���ڽ��տ���λ��*/
} UART_InitTypeDef;


/* �궨�� -----------------------------------------------------------*/
/* UART�жϿ��ؿ��ƺ꺯����run  ʹ�ܿ���λ�� */
#define NVIC_UART1_CTRL(run) 			do{ ES = run; }while(0)
#define NVIC_UART2_CTRL(run)  		do{ IE2 = (IE2 & 0xFE) | (run); }while(0)
#define NVIC_UART3_CTRL(run)  		do{ IE2 = (IE2 & 0xF7) | (run << 3); }while(0)
#define NVIC_UART4_CTRL(run)  		do{ IE2 = (IE2 & 0xEF) | (run << 4); }while(0)

/* UARTѡ���ж����ȼ��꺯�� ��pri �ж����ȼ��� */
#define NVIC_UART1_PRI(pri)  			do{IP  = (IP  & 0xEF) | ((pri & 0x01) << 4);}while(0)
#define NVIC_UART2_PRI(pri) 			do{IP2 = (IP2  & 0xFE) | (pri & 0x01);}while(0)


/* �����л�����IO�꺯�� ��port ����IOö���壩 */
#define GPIO_UART1_SWPort(port)  	do{P_SW1 = (P_SW1 & 0x3F) | (port << 6);}while(0)		/* UART1 ʹ��P30P31/P36P37/P16P17��(Ĭ��P30P31)		*/
#define GPIO_UART2_SWPort(port)  	do{P_SW2 = (P_SW2 & 0xFE) | (port);}while(0)				/* UART2 ʹ��P1/P4��(Ĭ��P1)	*/
#define GPIO_UART3_SWPort(port)  	do{P_SW2 = (P_SW2 & 0xFD) | (port << 1);}while(0)		/* UART3 ʹ��P0/P5��(Ĭ��P0)	*/
#define GPIO_UART4_SWPort(port)  	do{P_SW2 = (P_SW2 & 0xFB) | (port << 2);}while(0)		/* UART4 ʹ��P0/P5��(Ĭ��P0)	*/

/* ���ڻ�ȡæ��־λ�꺯�����Զ���ı�־λ����������Ӳ���Ĵ��� */
#define UART1_GET_BUSY_FLAG()    	(G_Uart_Busy_Flg & 0x01)
#define UART2_GET_BUSY_FLAG()    	(G_Uart_Busy_Flg & 0x02)
#define UART3_GET_BUSY_FLAG()    	(G_Uart_Busy_Flg & 0x04)
#define UART4_GET_BUSY_FLAG()    	(G_Uart_Busy_Flg & 0x08)

/* ��������æ��־λ�꺯�����Զ���ı�־λ����������Ӳ���Ĵ��� */
#define UART1_SET_BUSY_FLAG()    	do{G_Uart_Busy_Flg |= 0x01;}while(0)
#define UART2_SET_BUSY_FLAG()    	do{G_Uart_Busy_Flg |= 0x02;}while(0)
#define UART3_SET_BUSY_FLAG()    	do{G_Uart_Busy_Flg |= 0x04;}while(0)
#define UART4_SET_BUSY_FLAG()    	do{G_Uart_Busy_Flg |= 0x08;}while(0)

/* �������æ��־λ�꺯�����Զ���ı�־λ����������Ӳ���Ĵ��� */
#define UART1_CLEAR_BUSY_FLAG()   do{G_Uart_Busy_Flg &= 0xFE;}while(0)
#define UART2_CLEAR_BUSY_FLAG()   do{G_Uart_Busy_Flg &= 0xFD;}while(0)
#define UART3_CLEAR_BUSY_FLAG()   do{G_Uart_Busy_Flg &= 0xFB;}while(0)
#define UART4_CLEAR_BUSY_FLAG()   do{G_Uart_Busy_Flg &= 0xF7;}while(0)

/* ����1����һ���ֽں꺯����byte �ֽڣ�*/
#define UART1_RECEIVE_BYTE(byte) 	do{byte = SBUF;}while(0)
#define UART2_RECEIVE_BYTE(byte) 	do{byte = S2BUF;}while(0)
#define UART3_RECEIVE_BYTE(byte) 	do{byte = S3BUF;}while(0)
#define UART4_RECEIVE_BYTE(byte) 	do{byte = S4BUF;}while(0)

/* ���ڻ�ȡ���ձ�־λ�꺯�� */
#define UART1_GET_RX_FLAG()    		(SCON  & 0x01)
#define UART2_GET_RX_FLAG()    		(S2CON & 0x01)
#define UART3_GET_RX_FLAG()    		(S3CON & 0x01)
#define UART4_GET_RX_FLAG()    		(S4CON & 0x01)

/* ����������ձ�־λ�꺯�� */
#define	UART1_CLEAR_RX_FLAG()  		do{SCON  &= 0xFE;}while(0)
#define	UART2_CLEAR_RX_FLAG()  		do{S2CON &= 0xFE;}while(0)
#define	UART3_CLEAR_RX_FLAG()  		do{S3CON &= 0xFE;}while(0)
#define	UART4_CLEAR_RX_FLAG()  		do{S4CON &= 0xFE;}while(0)

/* ����1��ȡ���ͱ�־λ�꺯�� */
#define UART1_GET_TX_FLAG()    		(SCON  & 0x02)
#define UART2_GET_TX_FLAG()    		(S2CON & 0x02)
#define UART3_GET_TX_FLAG()    		(S3CON & 0x02)
#define UART4_GET_TX_FLAG()    		(S4CON & 0x02)

/* ����������ͱ�־λ�꺯�� */
#define	UART1_CLEAR_TX_FLAG()  		do{SCON  &= 0xFD;}while(0)
#define	UART2_CLEAR_TX_FLAG()  		do{S2CON &= 0xFD;}while(0)
#define	UART3_CLEAR_TX_FLAG()  		do{S3CON &= 0xFD;}while(0)
#define	UART4_CLEAR_TX_FLAG()  		do{S4CON &= 0xFD;}while(0)


/* ��չ���� ---------------------------------------------------------*/
/*  ����æ��־λ���Զ���ӷ�ֹ�മ�ڳ�ͻ�ı��� */
extern uint8_t G_Uart_Busy_Flg;

/* �������� ---------------------------------------------------------*/
/* ����1��ʼ������ */
ErrorStatus UART1_Init(const UART_InitTypeDef *uartx);
/* ����1�жϳ�ʼ������ */
ErrorStatus NVIC_UART1_Init(eNVIC_Pri pri, BOOL run);
/* ����1����һ���ֽں��� */
void UART1_Isr_Send_Byte(uint8_t dat);
/* ����1����һ���ַ������� */
void UART1_Isr_Send_String(const uint8_t *str);
/* ����1����һ�����麯�� */
void UART1_Isr_Send_Array(const uint8_t *str, uint16_t len);

/* ����2��ʼ������ */
ErrorStatus UART2_Init(const UART_InitTypeDef *uartx);
/* ����2�жϳ�ʼ������ */
ErrorStatus NVIC_UART2_Init(eNVIC_Pri pri, BOOL run);
/* ����2����һ���ֽں��� */
void UART2_Isr_Send_Byte(uint8_t dat);
/* ����2����һ���ַ������� */
void UART2_Isr_Send_String(const uint8_t *str);
/* ����2����һ�����麯�� */
void UART2_Isr_Send_Array(const uint8_t *str, uint16_t len);

/* ����3��ʼ������ */
ErrorStatus UART3_Init(const UART_InitTypeDef *uartx);
/* ����3�жϳ�ʼ������ */
ErrorStatus NVIC_UART3_Init(BOOL run);
/* ����3����һ���ֽں��� */
void UART3_Isr_Send_Byte(uint8_t dat);
/* ����3����һ���ַ������� */
void UART3_Isr_Send_String(const uint8_t *str);
/* ����3����һ�����麯�� */
void UART3_Isr_Send_Array(const uint8_t *str, uint16_t len);

/* ����4��ʼ������ */
ErrorStatus UART4_Init(const UART_InitTypeDef *uartx);
/* ����4�жϳ�ʼ������ */
ErrorStatus NVIC_UART4_Init(BOOL run);
/* ����4����һ���ֽں��� */
void UART4_Isr_Send_Byte(uint8_t dat);
/* ����4����һ���ַ������� */
void UART4_Isr_Send_String(const uint8_t *str);
/* ����4����һ�����麯�� */
void UART4_Isr_Send_Array(const uint8_t *str, uint16_t len);

#endif /* __STC8Ax_UART_H_ */

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
