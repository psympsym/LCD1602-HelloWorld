/*--------------------------------------------------------------------
/* File name   : STC8Ax_CONF.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef __STC8Ax_CONF_H__
#define __STC8Ax_CONF_H__

/* ����ͷ�ļ� -------------------------------------------------------*/
/* None. */
/* ���Ͷ��� ---------------------------------------------------------*/
/* None. */
/* �궨�� -----------------------------------------------------------*/

/** MCU�ͺ� */
#define  CONF_MCU_MODEL 	MCU_STC8H3K32S2 

/** ����ϵͳʱ��,����Ϊ0�����Զ���ȡϵͳƵ�� */
//#define CONF_FOSC   		0UL				/*< MCU������Ƶ�� */
//#define CONF_FOSC				5529600UL
//#define CONF_FOSC				11059200UL
//#define CONF_FOSC				12000000UL
//#define CONF_FOSC				22118400UL
#define CONF_FOSC					24000000UL
//#define  CONF_FOSC      36864000UL  
#define  CONF_CLKDIV    	0x02  		/*< ���²���������Ƶ�ʵ��� */              
#define  CONF_IRCBAND   	0x03
#define  CONF_VRTRIM    	0x19
#define  CONF_IRTRIM    	0x28
#define  CONF_LIRTRIM   	0x00

/* ��׼��ʱ */
#define CONF_DELAY_BASE   11000UL /*!< ������ʱʱ��ϵ�� */

/* ��չ���� ---------------------------------------------------------*/
/* None. */
/* �������� ---------------------------------------------------------*/
/* None. */

#endif /* __STC8Ax_CONF_H__ */

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/

