/*--------------------------------------------------------------------
/* File name   : STC8Ax_GPIO.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*--------------------------------------------------------------------
 */
#ifndef __STC8Ax_GPIO_H_
#define __STC8Ax_GPIO_H_

/* 包含头文件 -------------------------------------------------------*/
#include  "STC8Ax_REG.h"

/* 类型定义 ---------------------------------------------------------*/
typedef enum
{		/* IO 模式 */
    GPIO_MODE_WEAK_PULL 	= 0x00,	/*< 上拉准双向口 	*/
    GPIO_MODE_OUT_PP 			= 0x01,	/*< 推挽输出	*/
    GPIO_MODE_IN_FLOATING = 0x02,	/*< 浮空输入 	*/
    GPIO_MODE_OUT_OD 			= 0x03,	/*< 开漏输出 	*/
		/* IO 控制 */
    GPIO_CTRL_PULLUP 			= 0x10,	/*< 上拉电阻	*/
    GPIO_CTRL_ST 					= 0x20,	/*< 施密特触发器	*/
    GPIO_CTRL_SPEED   		= 0x40,	/*< 电平翻转速度 	*/
    GPIO_CTRL_DRIVE				= 0x80,	/*< 驱动电流 	*/	
} eGPIO_Mode;

/* GPIO Bit SET和Bit RESET枚举 */
typedef enum
{
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET = 1
} eGPIO_PinState;

/* 宏定义 -----------------------------------------------------------*/
/* ## 字符连接宏定义 A(x) (T_##X) == A(1) --> T_1 	*/
#define GPIO_Px(x)  (P##x)			// GPIO_Px(1) --> P1
#define Px_M1(x) 		(P##x##M1)  // Px_M1(0) --> P0M1	//GPIO_P0M1 GPIO_P0M0
#define Px_M0(x) 		(P##x##M0)  // P0M1 P0M0
#define Px_PU(x)    (P##x##PU)
#define Px_NCS(x)   (P##x##NCS)
#define Px_SR(x)    (P##x##SR)
#define Px_DR(x)    (P##x##DR)
#define Px_IE(x)    (P##x##IE)

/* GPIO组号，是GPIO宏操作函数的第一个参数，支持对这个宏进行再封装 */
#define	GPIO_P0  0 /*!< IO P0. */
#define	GPIO_P1  1 /*!< IO P1. */
#define	GPIO_P2  2 /*!< IO P2. */
#define	GPIO_P3  3 /*!< IO P3. */
#define	GPIO_P4  4 /*!< IO P4. */
#define	GPIO_P5  5 /*!< IO P5. */
#define	GPIO_P6  6 /*!< IO P6. */
#define	GPIO_P7  7 /*!< IO P7. */

/* GPIO端口号，是GPIO宏操作函数的第二个参数，支持多个宏进行或运算，同时配置多个IO */
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
 * 功能: GPIO    端口初始化宏函数
 * 参数: gpio:   GPIO端口, GPIO_P0 - GPIO_P7
 *       pin:    I/O引脚,  GPIO_Pin_0 - GPIO_Pin_7 IO引脚 Px.0-7
 *                         GPIO_Pin_LNIB IO引脚低 4 位
 *                         GPIO_Pin_HNIB IO引脚高 4 位
 *                         GPIO_Pin_All  IO所有引脚
 *       mode: 	 工作模式,枚举体 eGPIO_Mode
 * 返回：SUCCESS 返回成功。
 * 			 ERROR   返回失败。
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

/* GPIO翻转端口电平状态宏函数 */
#define GPIO_FLIP_PIN_LEVEL(gpio_x,pin)  do{GPIO_Px(gpio_x) ^= pin;}while(0)

/* GPIO端口输出高电平宏函数 */
#define GPIO_OUTPUT_HIGH(gpio_x,pin)  do{GPIO_Px(gpio_x) ^= (pin);}while(0)

/* GPIO端口输出低电平宏函数 */
#define GPIO_OUTPUT_LOW(gpio_x,pin)  do{GPIO_Px(gpio_x) |= ~(pin);}while(0)
				
/* 扩展变量 ---------------------------------------------------------*/
/* None. */

/* 函数声明 ---------------------------------------------------------*/
/* None. */
				
#endif /* __STC8Ax_GPIO_H_ */
