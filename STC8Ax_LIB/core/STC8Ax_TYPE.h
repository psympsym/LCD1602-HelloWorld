/*-----------------------------------------------------------------------------
/* File name   : STC8Ax_TYPE.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/*-----------------------------------------------------------------------------
**/
#ifndef __STC8Ax_TYPE_H_
#define __STC8Ax_TYPE_H_
					
typedef  signed char  			int8;				//  8 bits 
typedef  signed int  				int16;			// 16 bits 
typedef  signed long 				int32;			// 32 bits
typedef  signed char  			int8_t;			//  8 bits 
typedef  signed int  				int16_t;		// 16 bits 
typedef  signed long 				int32_t;		// 32 bits 			

typedef  volatile int8_t    vint8; 			//  8 bits 
typedef  volatile int16_t  	vint16; 		// 16 bits 
typedef  volatile int32_t  	vint32; 		// 32 bits 
typedef  volatile int8_t    vint8_t; 		//  8 bits 
typedef  volatile int16_t  	vint16_t; 	// 16 bits 
typedef  volatile int32_t  	vint32_t; 	// 32 bits 

typedef  unsigned char   		u8; 				//  8 bits 
typedef  unsigned int   		u16; 				// 16 bits 
typedef  unsigned long  		u32; 				// 32 bits 
typedef  unsigned char   		uint8; 			//  8 bits 
typedef  unsigned int   		uint16; 		// 16 bits 
typedef  unsigned long  		uint32; 		// 32 bits 
typedef  unsigned char   		uint8_t; 		//  8 bits 
typedef  unsigned int   		uint16_t; 	// 16 bits 
typedef  unsigned long  		uint32_t; 	// 32 bits 

typedef  volatile uint8_t   vu8; 				//  8 bits 
typedef  volatile uint16_t  vu16; 			// 16 bits 
typedef  volatile uint32_t  vu32; 			// 32 bits 
typedef  volatile uint8_t   vuint8; 		//  8 bits 
typedef  volatile uint16_t  vuint16; 		// 16 bits 
typedef  volatile uint32_t  vuint32; 		// 32 bits 
typedef  volatile uint8_t   vuint8_t; 	//  8 bits 
typedef  volatile uint16_t  vuint16_t; 	// 16 bits 
typedef  volatile uint32_t  vuint32_t; 	// 32 bits 

#define  __I     volatile const       	/*!< Defines 'read only' permissions    */
#define  __O     volatile             	/*!< Defines 'write only' permissions   */
#define  __IO    volatile             	/*!< Defines 'read / write' permissions */

/* 以掩码的形式向在指定寄存器写入一个值。*/
#define BIT0    0x01
#define BIT1    0x02
#define BIT2    0x04
#define BIT3    0x08
#define BIT4    0x10
#define BIT5    0x20
#define BIT6    0x40
#define BIT7    0x80
#define REG_WR_MASK(reg,mask,value)  reg=((reg&(~mask))|((uint8_t)(value)&mask))


#endif /* __STC8Ax_TYPE_H_ */

/*>>>>>>>>>> (C) COPYRIGHT NBUFE <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/


