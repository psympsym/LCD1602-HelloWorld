/*--------------------------------------------------------------------
/* File name   : STC8Ax_GPIO.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef __STC8Ax_GPIO_H_
#define __STC8Ax_GPIO_H_

/* ����ͷ�ļ� -------------------------------------------------------*/
#include  "STC8Ax_REG.h"

/* ���Ͷ��� ---------------------------------------------------------*/
typedef enum
{		/* IO ģʽ */
    GPIO_MODE_WEAK_PULL 	= 0x00,	/*< ����׼˫��� 	*/
    GPIO_MODE_OUT_PP 			= 0x01,	/*< �������	*/
    GPIO_MODE_IN_FLOATING = 0x02,	/*< �������� 	*/
    GPIO_MODE_OUT_OD 			= 0x03,	/*< ��©��� 	*/
		/* IO ���� */
    GPIO_CTRL_PULLUP 			= 0x10,	/*< ��������	*/
    GPIO_CTRL_ST 					= 0x20,	/*< ʩ���ش�����	*/
    GPIO_CTRL_SPEED   		= 0x40,	/*< ��ƽ��ת�ٶ� 	*/
    GPIO_CTRL_DRIVE				= 0x80,	/*< �������� 	*/	
} eGPIO_Mode;

/* GPIO Bit SET��Bit RESETö�� */
typedef enum
{
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET = 1
} eGPIO_PinState;

/* �궨�� -----------------------------------------------------------*/
/* ## �ַ����Ӻ궨�� A(x) (T_##X) == A(1) --> T_1 	*/
#define GPIO_Px(x)  (P##x)			// GPIO_Px(1) --> P1
#define Px_M1(x) 		(P##x##M1)  // Px_M1(0) --> P0M1	//GPIO_P0M1 GPIO_P0M0
#define Px_M0(x) 		(P##x##M0)  // P0M1 P0M0
#define Px_PU(x)    (P##x##PU)
#define Px_NCS(x)   (P##x##NCS)
#define Px_SR(x)    (P##x##SR)
#define Px_DR(x)    (P##x##DR)
#define Px_IE(x)    (P##x##IE)

/* GPIO��ţ���GPIO����������ĵ�һ��������֧�ֶ����������ٷ�װ */
#define	GPIO_P0  0 /*!< IO P0. */
#define	GPIO_P1  1 /*!< IO P1. */
#define	GPIO_P2  2 /*!< IO P2. */
#define	GPIO_P3  3 /*!< IO P3. */
#define	GPIO_P4  4 /*!< IO P4. */
#define	GPIO_P5  5 /*!< IO P5. */
#define	GPIO_P6  6 /*!< IO P6. */
#define	GPIO_P7  7 /*!< IO P7. */

/* GPIO�˿ںţ���GPIO����������ĵڶ���������֧�ֶ������л����㣬ͬʱ���ö��IO */
#define	Pin_0    0x01  /*!< IO Pin Px.0 . */
#define	Pin_1    0x02  /*!< IO Pin Px.1 . */
#define	Pin_2    0x04  /*!< IO Pin Px.2 . */
#define	Pin_3    0x08  /*!< IO Pin Px.3 . */
#define	Pin_4    0x10  /*!< IO Pin Px.4 . */
#define	Pin_5    0x20  /*!< IO Pin Px.5 . */
#define	Pin_6    0x40  /*!< IO Pin Px.6 . */
#define	Pin_7    0x80  /*!< IO Pin Px.7 . */
#define	Pin_Low  0x0F  /*!< IO Pin Px.0~3 . */
#define	Pin_High 0xF0  /*!< IO Pin Px.4~7 . */
#define	Pin_All  0xFF  /*!< IO Pin All . */

/*
 * ����: GPIO    �˿ڳ�ʼ���꺯��
 * ����: gpio:   GPIO�˿�, GPIO_P0 - GPIO_P7
 *       pin:    I/O����,  GPIO_Pin_0 - GPIO_Pin_7 IO���� Px.0-7
 *                         GPIO_Pin_LNIB IO���ŵ� 4 λ
 *                         GPIO_Pin_HNIB IO���Ÿ� 4 λ
 *                         GPIO_Pin_All  IO��������
 *       mode: 	 ����ģʽ,ö���� eGPIO_Mode
 * ���أ�SUCCESS ���سɹ���
 * 			 ERROR   ����ʧ�ܡ�
 */
#define GPIO_Init(gpio_x, pin, mode)				  	\
do{ if(mode & BIT0)	Px_M0(gpio_x) |= (pin);			\
		else	Px_M0(gpio_x) &= ~(pin);							\
		if((mode & BIT1))	Px_M1(gpio_x) |= (pin);		\
		else	Px_M1(gpio_x) &= ~(pin);							\
																	\
}while(0)

#define HAL_GPIO_Init(gpio_x, pin, mode)	\
do{ Px_M0(gpio_x) = ((mode & BIT0)? Px_M0(gpio_x)|(pin) : Px_M0(gpio_x)&(~pin));\
		Px_M1(gpio_x) = ((mode & BIT1)? Px_M1(gpio_x)|(pin) : Px_M1(gpio_x)&(~pin));\	
		EAXSFR();	\
		Px_PU(gpio_x) = ((mode & BIT4)? Px_PU(gpio_x)|(pin) : Px_PU(gpio_x)&(~pin));\
		Px_NCS(gpio_x)=((mode & BIT5)? Px_NCS(gpio_x)|(pin) : Px_NCS(gpio_x)&(~pin));\
		Px_SR(gpio_x) = ((mode & BIT6)? Px_SR(gpio_x)|(pin) : Px_SR(gpio_x)&(~pin));\
		Px_DR(gpio_x) = ((mode & BIT7)? Px_DR(gpio_x)|(pin) : Px_DR(gpio_x)&(~pin));\
		EAXRAM();	\
}while(0)

/* GPIO��ת�˿ڵ�ƽ״̬�꺯�� */
#define GPIO_FLIP_PIN_LEVEL(gpio_x,pin)  do{GPIO_Px(gpio_x) ^= pin;}while(0)

/* GPIO�˿�����ߵ�ƽ�꺯�� */
#define GPIO_OUTPUT_HIGH(gpio_x,pin)  do{GPIO_Px(gpio_x) ^= (pin);}while(0)

/* GPIO�˿�����͵�ƽ�꺯�� */
#define GPIO_OUTPUT_LOW(gpio_x,pin)  do{GPIO_Px(gpio_x) |= ~(pin);}while(0)
				
/* ��չ���� ---------------------------------------------------------*/
/* None. */

/* �������� ---------------------------------------------------------*/
/* None. */
				
#endif /* __STC8Ax_GPIO_H_ */
