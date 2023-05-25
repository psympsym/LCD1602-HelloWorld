/*-----------------------------------------------------------------------------
/* File name   : STC8Ax_REG.h
/* Author      : nbufe
/* Copyright(C): 2021-2022 nbufe. All rights reserved.
/* Update date : 2021.12.15 
/*-----------------------------------------------------------------------------
**/
#ifndef __STC8Ax_REG_H_
#define __STC8Ax_REG_H_

/* 包含头文件 -------------------------------------------------------*/
#include "STC8Ax_TYPE.h"
#include "STC8Ax_CORE.h"

/*-------------------------------------------------------------------*/
/* 内核特殊功能寄存器 		  																	  		 */
/*-------------------------------------------------------------------*/
														// 复位值   	描述
sfr ACC       	=		0xE0;   //0000,0000 累加器Accumulator
sfr B         	=   0xF0;   //0000,0000 B寄存器
sfr SP        	=   0x81;   //0000,0111 堆栈指针
sfr PSW       	=   0xD0;   //0000,0000 程序状态字
	sbit CY       =   PSW^7;
	sbit AC       =   PSW^6;
	sbit F0       =   PSW^5;
	sbit RS1      =   PSW^4;
	sbit RS0      =   PSW^3;
	sbit OV       =   PSW^2;
	sbit P        =   PSW^0;
sfr DPL       	=   0x82;   //0000,0000 数据指针低字节
sfr DPH       	=   0x83;   //0000,0000 数据指针高字节

/*-------------------------------------------------------------------*/
/* 系统管理特殊功能寄存器 															  					 */
/*-------------------------------------------------------------------*/
sfr AUXR        =   0x8E;   //0000,0000 辅助寄存器
sfr AUXR1       =   0xA2;   //0000,0000 辅助寄存器1
sfr P_SW1       =   0xA2;   //0000,0000 外设端口切换寄存器1
sfr P_SW2       =   0xBA;   //0xxx,x000 外设端口切换寄存器
sfr CLK_DIV     =   0x97;   //0000,0000 时钟分频控制寄存器
sfr PCON2       =   0x97;   
sfr P1ASF       =   0x9D;   //0000,0000 端口1模拟功能配置寄存器
sfr BUS_SPEED   =   0xA1;   //xx10,x011 总线速度控制寄存器
sfr	AUXR2    		= 	0x8F;
sfr WAKE_CLKO 	= 	0x8F;

#define EAXSFR()  P_SW2 |= 0x80 	/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
#define EAXRAM() 	P_SW2 &= ~0x80	/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */


/* 系统时钟 */
sfr IRTRIM      =   0x9F;
sfr LIRTRIM     =   0x9E;
sfr IRCBAND     =   0x9D;

#define CKSEL       	(*(__IO uint8_t  xdata *)0xFE00)
	#define MCK_IRC24M  0x00
	#define MCK_XOSC    0x01
	#define MCK_IRC32K  0x03
#define CLKDIV      	(*(__IO uint8_t  xdata *)0xFE01)
#define IRC24MCR    	(*(__IO uint8_t  xdata *)0xFE02)
	#define ENIRC24M    0x80
	#define IRC24MST    0x01
#define XOSCCR      	(*(__IO uint8_t  xdata *)0xFE03)
	#define ENXOSC      0x80
	#define XITYPE      0x40
	#define XOSCST      0x01
#define IRC32KCR    	(*(__IO uint8_t  xdata *)0xFE04)
	#define ENIRC32K    0x80
	#define IRC32KST    0x01
#define MCLKOCR     	(*(__IO uint8_t xdata *)0xFE05)
	#define MCLKO_S     0x80
#define IRCDB       	(*(__IO uint8_t xdata *)0xFE06)	

#define IRC_24M 			(*(__I uint8_t idata *)0xFB)

/*------------------------------------------------------------------*/
/* 电源管理特殊功能寄存器 																					*/
/*------------------------------------------------------------------*/
/* Power register */
sfr PCON 				= 0x87;
sfr VOCTRL 			= 0xBB;

sfr RSTCFG 			= 0xFF;
	#define ENLVR       0x40
	#define P54RST      0x10
	#define LVD_S1      0x00
	#define LVD_S2      0x01
	#define LVD_S3      0x02
	#define LVD_S4      0x03
	
/*------------------------------------------------------------------*/
/* I/O 口特殊功能寄存器 																						*/
/*------------------------------------------------------------------*/
sfr P0     =   0x80;
sfr P1     =   0x90;
sfr P2     =   0xa0;
sfr P3     =   0xb0;
sfr P4     =   0xc0;
sfr P5     =   0xc8;
sfr P6     =   0xe8;
sfr P7     =   0xf8;
/* P0 */
sbit P00   =   P0^0;
sbit P01   =   P0^1;
sbit P02   =   P0^2;
sbit P03   =   P0^3;
sbit P04   =   P0^4;
sbit P05   =   P0^5;
sbit P06   =   P0^6;
sbit P07   =   P0^7;
/* P1 */
sbit P10   =   P1^0;
sbit P11   =   P1^1;
sbit P12   =   P1^2;
sbit P13   =   P1^3;
sbit P14   =   P1^4;
sbit P15   =   P1^5;
sbit P16   =   P1^6;
sbit P17   =   P1^7;
/* P2 */
sbit P20   =   P2^0;
sbit P21   =   P2^1;
sbit P22   =   P2^2;
sbit P23   =   P2^3;
sbit P24   =   P2^4;
sbit P25   =   P2^5;
sbit P26   =   P2^6;
sbit P27   =   P2^7;
/* P3 */
sbit P30   =   P3^0;
sbit P31   =   P3^1;
sbit P32   =   P3^2;
sbit P33   =   P3^3;
sbit P34   =   P3^4;
sbit P35   =   P3^5;
sbit P36   =   P3^6;
sbit P37   =   P3^7;
/* P4 */
sbit P40   =   P4^0;
sbit P41   =   P4^1;
sbit P42   =   P4^2;
sbit P43   =   P4^3;
sbit P44   =   P4^4;
sbit P45   =   P4^5;
sbit P46   =   P4^6;
sbit P47   =   P4^7;
/* P5 */
sbit P50   =   P5^0;
sbit P51   =   P5^1;
sbit P52   =   P5^2;
sbit P53   =   P5^3;
sbit P54   =   P5^4;
sbit P55   =   P5^5;
sbit P56   =   P5^6;
sbit P57   =   P5^7;
/* P6 */
sbit P60   =   P6^0;
sbit P61   =   P6^1;
sbit P62   =   P6^2;
sbit P63   =   P6^3;
sbit P64   =   P6^4;
sbit P65   =   P6^5;
sbit P66   =   P6^6;
sbit P67   =   P6^7;
/* P7 */
sbit P70   =   P7^0;
sbit P71   =   P7^1;
sbit P72   =   P7^2;
sbit P73   =   P7^3;
sbit P74   =   P7^4;
sbit P75   =   P7^5;
sbit P76   =   P7^6;
sbit P77   =   P7^7;

/* GPIO mode register  */
sfr P0M1   =   0x93;   //0000,0000 端口0模式寄存器1
sfr P1M1   =   0x91;   //0000,0000 端口1模式寄存器1
sfr P2M1   =   0x95;   //0000,0000 端口2模式寄存器1
sfr P3M1   =   0xB1;   //0000,0000 端口3模式寄存器1
sfr P4M1   =   0xB3;   //0000,0000 端口4模式寄存器1
sfr P5M1   =   0xC9;   //0000,0000 端口5模式寄存器1
sfr P6M1   =   0xCB;   //0000,0000 端口6模式寄存器1
sfr P7M1   =   0xE1;   //0000,0000 端口7模式寄存器1

sfr P0M0   =   0x94;   //0000,0000 端口0模式寄存器0
sfr P1M0   =   0x92;   //0000,0000 端口1模式寄存器0
sfr P2M0   =   0x96;   //0000,0000 端口2模式寄存器0
sfr P3M0   =   0xB2;   //0000,0000 端口3模式寄存器0
sfr P4M0   =   0xB4;   //0000,0000 端口4模式寄存器0
sfr P5M0   =   0xCA;   //0000,0000 端口5模式寄存器0
sfr P6M0   =   0xCC;   //0000,0000 端口6模式寄存器0
sfr P7M0   =   0xE2;   //0000,0000 端口7模式寄存器0

/* GPIO Driver register */
#define   P0PU    ( *(__IO uint8_t xdata *) 0xFE10)
#define   P1PU    ( *(__IO uint8_t xdata *) 0xFE11)
#define   P2PU    ( *(__IO uint8_t xdata *) 0xFE12)
#define   P3PU    ( *(__IO uint8_t xdata *) 0xFE13)
#define   P4PU    ( *(__IO uint8_t xdata *) 0xFE14)
#define   P5PU    ( *(__IO uint8_t xdata *) 0xFE15)
#define   P6PU    ( *(__IO uint8_t xdata *) 0xFE16)
#define   P7PU    ( *(__IO uint8_t xdata *) 0xFE17)

#define   P0NCS  ( *(__IO uint8_t xdata *) 0xFE18)
#define   P1NCS  ( *(__IO uint8_t xdata *) 0xFE19)
#define   P2NCS  ( *(__IO uint8_t xdata *) 0xFE1A)
#define   P3NCS  ( *(__IO uint8_t xdata *) 0xFE1B)
#define   P4NCS  ( *(__IO uint8_t xdata *) 0xFE1C)
#define   P5NCS  ( *(__IO uint8_t xdata *) 0xFE1D)
#define   P6NCS  ( *(__IO uint8_t xdata *) 0xFE1E)
#define   P7NCS  ( *(__IO uint8_t xdata *) 0xFE1F)

#define   P0SR   ( *(__IO uint8_t xdata *) 0xFE20)
#define   P1SR   ( *(__IO uint8_t xdata *) 0xFE21)
#define   P2SR   ( *(__IO uint8_t xdata *) 0xFE22)
#define   P3SR   ( *(__IO uint8_t xdata *) 0xFE23)
#define   P4SR   ( *(__IO uint8_t xdata *) 0xFE24)
#define   P5SR   ( *(__IO uint8_t xdata *) 0xFE25)
#define   P6SR   ( *(__IO uint8_t xdata *) 0xFE26)
#define   P7SR   ( *(__IO uint8_t xdata *) 0xFE27)

#define   P0DR   ( *(__IO uint8_t xdata *) 0xFE28)
#define   P1DR   ( *(__IO uint8_t xdata *) 0xFE29)
#define   P2DR   ( *(__IO uint8_t xdata *) 0xFE2A)
#define   P3DR   ( *(__IO uint8_t xdata *) 0xFE2B)
#define   P4DR   ( *(__IO uint8_t xdata *) 0xFE2C)
#define   P5DR   ( *(__IO uint8_t xdata *) 0xFE2D)
#define   P6DR   ( *(__IO uint8_t xdata *) 0xFE2E)
#define   P7DR   ( *(__IO uint8_t xdata *) 0xFE2F)							   
					   
#define   P0IE   ( *(__IO uint8_t xdata *) 0xFE30)
#define   P1IE   ( *(__IO uint8_t xdata *) 0xFE31)
#define   P3IE   ( *(__IO uint8_t xdata *) 0xFE32)
#define   P2IE   ( *(__IO uint8_t xdata *) 0xFE33)
#define   P4IE   ( *(__IO uint8_t xdata *) 0xFE34)
#define   P5IE   ( *(__IO uint8_t xdata *) 0xFE35)
#define   P6IE   ( *(__IO uint8_t xdata *) 0xFE36)
#define   P7IE   ( *(__IO uint8_t xdata *) 0xFE37)

/*------------------------------------------------------------------*/
/* 中断特殊功能寄存器 																								*/
/*------------------------------------------------------------------*/
/* Base address define */
sfr IE        =   	0xA8;   //0000,0000 中断控制寄存器
	sbit EA   	= 		IE^7;		//中断允许总控制位
	sbit ELVD 	= 		IE^6;		//低压监测中断允许位
	sbit EADC 	= 		IE^5;		//ADC 中断 允许位
	sbit ES   	= 		IE^4;		//串行中断 允许控制位
	sbit ET1  	= 		IE^3;		//定时中断1允许控制位
	sbit EX1  	= 		IE^2;		//外部中断1允许控制位
	sbit ET0  	= 		IE^1;		//定时中断0允许控制位
	sbit EX0  	= 		IE^0;		//外部中断0允许控制位
sfr IP        =   	0xB8;   //0000,0000 中断优先级寄存器
	sbit PPCA		= 		IP^7;		//PCA 模块中断优先级
	sbit PLVD		= 		IP^6;		//低压监测中断优先级
	sbit PADC		= 		IP^5;		//ADC 中断优先级
	sbit PS   	= 		IP^4;		//串行中断0优先级设定位
	sbit PT1		= 		IP^3;		//定时中断1优先级设定位
	sbit PX1		= 		IP^2;		//外部中断1优先级设定位
	sbit PT0		= 		IP^1;		//定时中断0优先级设定位
	sbit PX0		= 		IP^0;		//外部中断0优先级设定位
sfr IE2       =   	0xAF;   //0000,0000 中断控制寄存器2
	#define ET4       0x40	//bit6
	#define ET3       0x20	//bit5
	#define ES4       0x10	//bit4
	#define ES3       0x08	//bit3
	#define ET2       0x04	//bit2
	#define ESPI      0x02	//bit1
	#define ES2       0x01		//bit0
sfr IP2       =   	0xB5;   //xxxx,xx00 中断优先级寄存器2
	#define PI2C      0x40	//bit6
	#define PCMP      0x20	//bit5
	#define PX4       0x10	//bit4
	#define PPWMFD    0x08	//bit3
	#define PPWM      0x04	//bit2
	#define PSPI      0x02	//bit1
	#define PS2       0x01	//bit0
sfr INTCLKO  =   		0x8F;   //0000,0000 外部中断与时钟输出控制寄存器
	#define EX4       0x40	//bit6
	#define EX3       0x20	//bit5
	#define EX2       0x10	//bit4
	#define T2CLKO    0x04	//bit2
	#define T1CLKO    0x02	//bit1
	#define T0CLKO    0x01	//bit0
sfr IP2H  		= 		0xB6;		//STC12C5A60S2系列
	#define PI2CH     0x40	//bit6
	#define PCMPH     0x20	//bit5
	#define PX4H      0x10	//bit4
	#define PPWMFDH   0x08	//bit3
	#define PPWMH     0x04	//bit2
	#define PSPIH     0x02	//bit1
	#define PS2H      0x01	//bit0
sfr IPH   = 0xB7;
	#define PPCAH     0x80	//bit7
	#define PLVDH     0x40	//bit6
	#define PADCH     0x20	//bit5
	#define PSH       0x10	//bit4
	#define PT1H      0x08	//bit3
	#define PX1H      0x04	//bit2
	#define PT0H      0x02	//bit1
	#define PX0H      0x01	//bit0
sfr AUXINTIF = 0xEF;

/*------------------------------------------------------------------*/
/* 定时器特殊功能寄存器 																						*/
/*------------------------------------------------------------------*/
sfr TCON        =   0x88;   //0000,0000 T0/T1控制寄存器
	sbit TF1      =   TCON^7;
	sbit TR1      =   TCON^6;
	sbit TF0      =   TCON^5;
	sbit TR0      =   TCON^4;
	sbit IE1      =   TCON^3;
	sbit IT1      =   TCON^2;
	sbit IE0      =   TCON^1;
	sbit IT0      =   TCON^0;
sfr TMOD        =   0x89;   //0000,0000 T0/T1模式寄存器
	#define T1_GATE   0x80	//bit7
	#define T1_CT     0x40	//bit6
	#define T1_M1     0x20	//bit5
	#define T1_M0     0x10	//bit4
	#define T0_GATE   0x08	//bit3
	#define T0_CT     0x04	//bit2
	#define T0_M1     0x02	//bit1
	#define T0_M0     0x01	//bit0
sfr TL0         =   0x8A;   //0000,0000 T0低字节
sfr T0L         =   0x8A;   //0000,0000 T0低字节
sfr TL1         =   0x8B;   //0000,0000 T1低字节
sfr T1L         =   0x8B;   //0000,0000 T0低字节
sfr TH0         =   0x8C;   //0000,0000 T0高字节
sfr T0H         =   0x8C;   //0000,0000 T0高字节
sfr TH1         =   0x8D;   //0000,0000 T1高字节
sfr T1H         =   0x8D;   //0000,0000 T1高字节
sfr T4T3M       =   0xD1;   //0000,0000 T3/T4模式寄存器
	#define T4R       0x80		//bit6
	#define T4_CT     0x40	//bit6
	#define T4x12     0x20	//bit5
	#define T4CLKO    0x10	//bit4
	#define T3R       0x08	//bit3
	#define T3_CT     0x04	//bit2
	#define T3x12     0x02	//bit1
	#define T3CLKO    0x01	//bit0
sfr T4H         =   0xD2;   //0000,0000 T4高字节
sfr T4L         =   0xD3;   //0000,0000 T4低字节
sfr T3H         =   0xD4;   //0000,0000 T3高字节
sfr T3L         =   0xD5;   //0000,0000 T3低字节
sfr T2H         =   0xD6;   //0000,0000 T2高字节
sfr T2L         =   0xD7;   //0000,0000 T2低字节

/*------------------------------------------------------------------*/
/* 掉电唤醒定时器特殊功能寄存器 																		*/
/*------------------------------------------------------------------*/
sfr WKTCL       =   0xAA;   //0000,0000 掉电唤醒定时器低字节
sfr WKTCH       =   0xAB;   //0000,0000 掉电唤醒定时器高字节
//	B7		 B6	B5	B4	B3	B2	B1	B0		B7	B6	B5	B4	B3	B2	B1	B0
//	WKTEN	 - 	-	  -   S11	S10	S9	S8		S7	S6	S5	S4	S3	S2	S1	S0	 n * 560us	#define WKTEN     0x80
	#define WKTEN     0x80	

/*------------------------------------------------------------------*/
/* WDT 看门狗特殊功能寄存器 																				*/
/*------------------------------------------------------------------*/
sfr WDT_CONTR =   	0xC1;  //0000,0000 看门狗控制寄存器
	#define WDT_FLAG  0x80	//bit7
	#define EN_WDT    0x20	//bit5
	#define CLR_WDT   0x10	//bit4
	#define IDEL_WDT  0x08	//bit3

/*------------------------------------------------------------------*/
/* 串行口特殊功能寄存器 																							*/
/*------------------------------------------------------------------*/
//串行口特殊功能寄存器
sfr SCON        =   0x98;   //0000,0000 串口1控制寄存器
	sbit SM0      =   SCON^7;
	sbit SM1      =   SCON^6;
	sbit SM2      =   SCON^5;
	sbit REN      =   SCON^4;
	sbit TB8      =   SCON^3;
	sbit RB8      =   SCON^2;
	sbit TI       =   SCON^1;
	sbit RI       =   SCON^0;
sfr SBUF        =   0x99; 	//xxxx,xxxx 串口1数据寄存器
sfr S2CON       =   0x9A; 	//0000,0000 串口2控制寄存器
	#define S2SM0     0x80		//bit7
	#define S2ST4     0x40		//bit6
	#define S2SM2     0x04		//bit5
	#define S2REN     0x10		//bit4
	#define S2TB8     0x08		//bit3
	#define S2RB8     0x04		//bit2
	#define S2TI      0x02		//bit1
	#define S2RI      0x01		//bit0
sfr S2BUF       =   0x9B; 	//xxxx,xxxx 串口2数据寄存器
sfr S3CON       =   0xAC; 	//0000,0000 串口3控制寄存器
	#define S3SM0     0x80		//bit7
	#define S3ST4     0x40		//bit6
	#define S3SM2     0x04		//bit5
	#define S3REN     0x10		//bit4
	#define S3TB8     0x08		//bit3
	#define S3RB8     0x04		//bit2
	#define S3TI      0x02		//bit1
	#define S3RI      0x01		//bit0
sfr S3BUF       =   0xAD; 	//xxxx,xxxx 串口3数据寄存器
sfr S4CON       =   0x84; 	//0000,0000 串口4控制寄存器
	#define S4SM0     0x80		//bit7
	#define S4ST4     0x40		//bit6
	#define S4SM2     0x04		//bit5
	#define S4REN     0x10		//bit4
	#define S4TB8     0x08		//bit3
	#define S4RB8     0x04		//bit2
	#define S4TI      0x02		//bit1
	#define S4RI      0x01		//bit0
sfr S4BUF       =   0x85; 	//xxxx,xxxx 串口4数据寄存器
sfr SADDR       =   0xA9; 	//0000,0000 从机地址寄存器
sfr SADEN       =   0xB9; 	//0000,0000 从机地址屏蔽寄存器

/*------------------------------------------------------------------*/
/* ADC 特殊功能寄存器   																							*/
/*------------------------------------------------------------------*/
sfr ADC_CONTR   =   	0xBC; //0000,0000 A/D转换控制寄存器
	#define ADC_POWER 	0x80	//bit7
	#define ADC_START 	0x40	//bit6
	#define ADC_FLAG  	0x20	//bit5
sfr ADC_RES     =   	0xBD; //0000,0000 A/D转换结果高8位
sfr ADC_RESL    =   	0xBE; //0000,0000 A/D转换结果低2位

/*------------------------------------------------------------------*/
/* IAP/ISP 特殊功能寄存器     																				*/
/*------------------------------------------------------------------*/
//IAP/ISP 特殊功能寄存器
sfr IAP_DATA    =   0xC2;   //0000,0000 EEPROM数据寄存器
sfr IAP_ADDRH   =   0xC3;   //0000,0000 EEPROM地址高字节
sfr IAP_ADDRL   =   0xC4;   //0000,0000 EEPROM地址第字节
sfr IAP_CMD     =   0xC5;   //xxxx,xx00 EEPROM命令寄存器
	#define IAP_IDL   0x00
	#define IAP_READ  0x01
	#define IAP_WRITE 0x02
	#define IAP_ERASE 0x03
sfr IAP_TRIG    =   0xC6;   //0000,0000 EEPRPM命令触发寄存器
sfr IAP_CONTR   =   0xC7;   //0000,x000 EEPROM控制寄存器
	#define IAPEN     0x80		//bit7
	#define SWBS      0x40		//bit6
	#define SWRST     0x20		//bit5
	#define CMD_FAIL  0x10		//bit4

/*------------------------------------------------------------------*/
/* SPI 特殊功能寄存器     																	    		*/
/*------------------------------------------------------------------*/
sfr SPSTAT      =   0xCD;   //00xx,xxxx SPI状态寄存器
	#define SPIF    	0x80		//bit7
	#define WCOL    	0x40		//bit6
sfr SPCTL       =   0xCE;   //0000,0100 SPI控制寄存器
	#define SSIG    	0x80		//bit7
	#define SPEN    	0x40		//bit6
	#define DORD    	0x80		//bit5
	#define MSTR    	0x10		//bit4
	#define CPOL    	0x08		//bit3
	#define CPHA    	0x04		//bit2
sfr SPDAT       =   0xCF;   //0000,0000 SPI数据寄存器

/*------------------------------------------------------------------*/
/* I2C 特殊功能寄存器     																    			*/
/*------------------------------------------------------------------*/
#define I2CCFG      (*(__IO uint8_t xdata *) 0xFE80)
#define I2CMSCR     (*(__IO uint8_t xdata *) 0xFE81)
#define I2CMSST     (*(__IO uint8_t xdata *) 0xFE82)
#define I2CSLCR     (*(__IO uint8_t xdata *) 0xFE83)
#define I2CSLST     (*(__IO uint8_t xdata *) 0xFE84)
#define I2CSLADR    (*(__IO uint8_t xdata *) 0xFE85)
#define I2CTXD      (*(__IO uint8_t xdata *) 0xFE86)
#define I2CRXD      (*(__IO uint8_t xdata *) 0xFE87)
#define I2CMSAUX    (*(__IO uint8_t xdata *) 0xFE88)
/* I2CCFG */
#define ENI2C       0x80
#define I2CMASTER   0x40
#define I2CSLAVE    0x00
/* I2CMSCR */
#define EMSI        0x80
#define MS_IDLE                     0x00
#define MS_START                    0x01
#define MS_SENDDAT                  0x02
#define MS_RECVACK                  0x03
#define MS_RECVDAT                  0x04
#define MS_SENDACK                  0x05
#define MS_STOP                     0x06
#define MS_START_SENDDAT_RECVACK    0x09
#define MS_SENDDAT_RECVACK          0x0a
#define MS_RECVDAT_SENDACK          0x0b
#define MS_RECVDAT_SENDNAK          0x0c
/* I2CMSST */
#define MSBUSY      0x80
#define MSIF        0x40
#define MSACKI      0x02
#define MSACKO      0x01
/* I2CSLCR */
#define ESTAI       0x40
#define ERXI        0x20
#define ETXI        0x10
#define ESTOI       0x08
#define SLRST       0x01
/* I2CSLST */
#define SLBUSY      0x80
#define STAIF       0x40
#define RXIF        0x20
#define TXIF        0x10
#define STOIF       0x08
#define TXING       0x04
#define SLACKI      0x02
#define SLACKO      0x01
/* I2CMSAUX */
#define WDTA        0x01

/*------------------------------------------------------------------*/
/* 比较器特殊功能寄存器        										  				    		*/
/*------------------------------------------------------------------*/
sfr CMPCR1      =   0xE6;//0000,0000 比较器控制寄存器1
	#define	CMPEN			0x80	//bit7	1: 允许比较器, 0: 禁止,关闭比较器电源
	#define	CMPIF			0x40	//bit6	比较器中断标志, 包括上升沿或下降沿中断, 软件清0
	#define	PIE				0x20	//bit5	1: 比较结果由0变1, 产生上升沿中断
	#define	NIE				0x10	//bit4	1: 比较结果由1变0, 产生下降沿中断
	#define	PIS				0x08	//bit3	输入正极性选择, 0: 选择内部P5.5做正输入,           1: 由ADCIS[2:0]所选择的ADC输入端做正输入.
	#define	NIS				0x04	//bit2	输入负极性选择, 0: 选择内部BandGap电压BGv做负输入, 1: 选择外部P5.4做输入.
	#define	CMPOE			0x02	//bit1	1: 允许比较结果输出到P1.2, 0: 禁止.
	#define	CMPRES		0x01	//bit0	比较结果, 1: CMP+电平高于CMP-,  0: CMP+电平低于CMP-,  只读
sfr CMPCR2      =   0xE7;//0000,0000 比较器控制寄存器2
	#define	INVCMPO		0x80	//bit7	1: 比较器输出取反,  0: 不取反
	#define	DISFLT		0x40	//bit6	1: 关闭0.1uF滤波,  0: 允许
	#define	LCDTY			0x00	//bit5-0	0~63, 比较结果变化延时周期数

/*------------------------------------------------------------------*/
/* PCA 特殊功能寄存器         										  			    			*/
/*------------------------------------------------------------------*/
sfr CCON        =   0xD8;   //00xx,xx00 PCA控制寄存器
	sbit CF       =   CCON^7;
	sbit CR       =   CCON^6;
	sbit CCF2     =   CCON^2;
	sbit CCF1     =   CCON^1;
	sbit CCF0     =   CCON^0;
sfr CMOD        =   0xD9;   //0xxx,x000 PCA 工作模式寄存器
	#define CIDL      0x80	//bit7
	#define ECF       0x01	//bit0 
sfr CL          =   0xE9;   //0000,0000 PCA计数器低字节
sfr CH          =   0xF9;   //0000,0000 PCA计数器高字节
sfr CCAPM0      =   0xDA;   //0000,0000 PCA模块0的PWM寄存器
	#define ECOM0     0x40	//bit6
	#define CCAPP0    0x20	//bit5
	#define CCAPN0    0x10	//bit4
	#define MAT0      0x08	//bit3
	#define TOG0      0x04	//bit2
	#define PWM0      0x02	//bit1
	#define ECCF0     0x01	//bit0
sfr CCAPM1      =   0xDB;   //0000,0000 PCA模块1的PWM寄存器
	#define ECOM1     0x40	//bit6
	#define CCAPP1    0x20	//bit5
	#define CCAPN1    0x10	//bit4
	#define MAT1      0x08	//bit3
	#define TOG1      0x04	//bit2
	#define PWM1      0x02	//bit1
	#define ECCF1     0x01	//bit0
sfr CCAPM2      =   0xDC;   //0000,0000 PCA模块2的PWM 寄存器
	#define ECOM2     0x40	//bit6
	#define CCAPP2    0x20	//bit5
	#define CCAPN2    0x10	//bit4
	#define MAT2      0x08	//bit3
	#define TOG2      0x04	//bit2
	#define PWM2      0x02	//bit1
	#define ECCF2     0x01	//bit0
sfr CCAPM3      =   0xDD;
	#define ECOM3     0x40
	#define CCAPP3    0x20
	#define CCAPN3    0x10
	#define MAT3      0x08
	#define TOG3      0x04
	#define PWM3      0x02
	#define ECCF3     0x01	
sfr CCAP0L      =   0xEA;   //0000,0000 PCA模块0的捕捉/比较寄存器低字节
sfr CCAP1L      =   0xEB;   //0000,0000 PCA模块1的捕捉/比较寄存器低字节
sfr CCAP2L      =   0xEC;   //0000,0000 PCA模块2的捕捉/比较寄存器低字节
sfr CCAP3L      =   0xED;   //0000,0000 PCA模块3的捕捉/比较寄存器低字节
sfr CCAP0H      =   0xFA;   //0000,0000 PCA模块0的捕捉/比较寄存器高字节
sfr CCAP1H      =   0xFB;   //0000,0000 PCA模块1的捕捉/比较寄存器高字节
sfr CCAP2H      =   0xFC;   //0000,0000 PCA模块2的捕捉/比较寄存器高字节
sfr CCAP3H      =   0xFD;   //0000,0000 PCA模块3的捕捉/比较寄存器高字节
sfr PCA_PWM0    =   0xF2;   //xxxx,xx00 PCA模块0的PWM寄存器
sfr PCA_PWM1    =   0xF3;   //xxxx,xx00 PCA模块1的PWM寄存器
sfr PCA_PWM2    =   0xF4;   //xxxx,xx00 PCA模块1的PWM寄存器
sfr PCA_PWM3    =   0xF5;

/*------------------------------------------------------------------*/
/* PWM 特殊功能寄存器         										  				    			*/
/*------------------------------------------------------------------*/
sfr PWMCFG      =   0xF1;   //x000,0000 PWM配置寄存器
	#define CBIF      0x80	//bit7
	#define ETADC     0x40	//bit6
sfr PWMCR       =   0xF5;   //0000,0000 PWM控制寄存器
	#define ENPWM     0x80	//bit7
	#define ECBI      0x40	//bit6
sfr PWMIF       =   0xF6;   //x000,0000 PWM中断标志寄存器
	#define C7IF      0x80	//bit7
	#define C6IF      0x40	//bit6
	#define C5IF      0x20	//bit5
	#define C4IF      0x10	//bit4
	#define C3IF      0x08	//bit3
	#define C2IF      0x04	//bit2
	#define C1IF      0x02	//bit1
	#define C0IF      0x01	//bit0
sfr PWMFDCR     =   0xF7;   //xx00,0000 PWM外部异常检测控制寄存器
#define INVCMP      0x80	//bit7
#define INVIO       0x40	//bit6
#define ENFD        0x20	//bit5
#define FLTFLIO     0x10	//bit4
#define EFDI        0x08	//bit3
#define FDCMP       0x04	//bit2
#define FDIO        0x02	//bit1
#define FDIF        0x01	//bit0

/* 如下特殊功能寄存器位于扩展RAM区域,访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写 */
#define PWMC        (*(__IO uint16_t xdata *)0xFFF0)
#define PWMCH       (*(__IO uint8_t  xdata *)0xFFF0)
#define PWMCL       (*(__IO uint8_t  xdata *)0xFFF1)
#define PWMCKS      (*(__IO uint8_t  xdata *)0xFFF2)
#define TADCP       (*(__IO uint8_t  xdata *)0xFFF3)
#define TADCPH      (*(__IO uint8_t  xdata *)0xFFF3)
#define TADCPL      (*(__IO uint8_t  xdata *)0xFFF4)
#define PWM0T1      (*(__IO uint16_t xdata *)0xFF00)
#define PWM0T1H     (*(__IO uint8_t  xdata *)0xFF00)
#define PWM0T1L     (*(__IO uint8_t  xdata *)0xFF01)
#define PWM0T2      (*(__IO uint16_t xdata *)0xFF02)
#define PWM0T2H     (*(__IO uint8_t  xdata *)0xFF02)
#define PWM0T2L     (*(__IO uint8_t  xdata *)0xFF03)
#define PWM0CR      (*(__IO uint8_t  xdata *)0xFF04)
#define PWM0HLD     (*(__IO uint8_t  xdata *)0xFF05)
#define PWM1T1      (*(__IO uint16_t xdata *)0xFF10)
#define PWM1T1H     (*(__IO uint8_t  xdata *)0xFF10)
#define PWM1T1L     (*(__IO uint8_t  xdata *)0xFF11)
#define PWM1T2      (*(__IO uint16_t xdata *)0xFF12)
#define PWM1T2H     (*(__IO uint8_t  xdata *)0xFF12)
#define PWM1T2L     (*(__IO uint8_t  xdata *)0xFF13)
#define PWM1CR      (*(__IO uint8_t  xdata *)0xFF14)
#define PWM1HLD     (*(__IO uint8_t  xdata *)0xFF15)
#define PWM2T1      (*(__IO uint16_t xdata *)0xFF20)
#define PWM2T1H     (*(__IO uint8_t  xdata *)0xFF20)
#define PWM2T1L     (*(__IO uint8_t  xdata *)0xFF21)
#define PWM2T2      (*(__IO uint16_t xdata *)0xFF22)
#define PWM2T2H     (*(__IO uint8_t  xdata *)0xFF22)
#define PWM2T2L     (*(__IO uint8_t  xdata *)0xFF23)
#define PWM2CR      (*(__IO uint8_t  xdata *)0xFF24)
#define PWM2HLD     (*(__IO uint8_t  xdata *)0xFF25)
#define PWM3T1      (*(__IO uint16_t xdata *)0xFF30)
#define PWM3T1H     (*(__IO uint8_t  xdata *)0xFF30)
#define PWM3T1L     (*(__IO uint8_t  xdata *)0xFF31)
#define PWM3T2      (*(__IO uint16_t xdata *)0xFF32)
#define PWM3T2H     (*(__IO uint8_t  xdata *)0xFF32)
#define PWM3T2L     (*(__IO uint8_t  xdata *)0xFF33)
#define PWM3CR      (*(__IO uint8_t  xdata *)0xFF34)
#define PWM3HLD     (*(__IO uint8_t  xdata *)0xFF35)
#define PWM4T1      (*(__IO uint16_t xdata *)0xFF40)
#define PWM4T1H     (*(__IO uint8_t  xdata *)0xFF40)
#define PWM4T1L     (*(__IO uint8_t  xdata *)0xFF41)
#define PWM4T2      (*(__IO uint16_t xdata *)0xFF42)
#define PWM4T2H     (*(__IO uint8_t  xdata *)0xFF42)
#define PWM4T2L     (*(__IO uint8_t  xdata *)0xFF43)
#define PWM4CR      (*(__IO uint8_t  xdata *)0xFF44)
#define PWM4HLD     (*(__IO uint8_t  xdata *)0xFF45)
#define PWM5T1      (*(__IO uint16_t xdata *)0xFF50)
#define PWM5T1H     (*(__IO uint8_t  xdata *)0xFF50)
#define PWM5T1L     (*(__IO uint8_t  xdata *)0xFF51)
#define PWM5T2      (*(__IO uint16_t xdata *)0xFF52)
#define PWM5T2H     (*(__IO uint8_t  xdata *)0xFF52)
#define PWM5T2L     (*(__IO uint8_t  xdata *)0xFF53)
#define PWM5CR      (*(__IO uint8_t  xdata *)0xFF54)
#define PWM5HLD     (*(__IO uint8_t  xdata *)0xFF55)
#define PWM6T1      (*(__IO uint16_t xdata *)0xFF60)
#define PWM6T1H     (*(__IO uint8_t  xdata *)0xFF60)
#define PWM6T1L     (*(__IO uint8_t  xdata *)0xFF61)
#define PWM6T2      (*(__IO uint16_t xdata *)0xFF62)
#define PWM6T2H     (*(__IO uint8_t  xdata *)0xFF62)
#define PWM6T2L     (*(__IO uint8_t  xdata *)0xFF63)
#define PWM6CR      (*(__IO uint8_t  xdata *)0xFF64)
#define PWM6HLD     (*(__IO uint8_t  xdata *)0xFF65)
#define PWM7T1      (*(__IO uint16_t xdata *)0xFF70)
#define PWM7T1H     (*(__IO uint8_t  xdata *)0xFF70)
#define PWM7T1L     (*(__IO uint8_t  xdata *)0xFF71)
#define PWM7T2      (*(__IO uint16_t xdata *)0xFF72)
#define PWM7T2H     (*(__IO uint8_t  xdata *)0xFF72)
#define PWM7T2L     (*(__IO uint8_t  xdata *)0xFF73)
#define PWM7CR      (*(__IO uint8_t  xdata *)0xFF74)
#define PWM7HLD     (*(__IO uint8_t  xdata *)0xFF75)

/* LCM */
#define LCMIFCFG    (*(__IO uint8_t  xdata *)0xFE50)
#define LCMIFCFG2   (*(__IO uint8_t  xdata *)0xFE51)
#define LCMIFCR     (*(__IO uint8_t  xdata *)0xFE52)
#define LCMIFSTA    (*(__IO uint8_t  xdata *)0xFE53)
#define LCMIFDATL   (*(__IO uint8_t  xdata *)0xFE54)
#define LCMIFDATH   (*(__IO uint8_t  xdata *)0xFE55)

#define TM2PS       (*(__IO uint8_t  xdata *)0xFEA2)
#define TM3PS       (*(__IO uint8_t  xdata *)0xFEA3)
#define TM4PS       (*(__IO uint8_t  xdata *)0xFEA4)
#define ADCTIM      (*(__IO uint8_t  xdata *)0xFEA8)
#define ADCEXCFG    (*(__IO uint8_t  xdata *)0xFEAD)
#define CMPEXCFG    (*(__IO uint8_t  xdata *)0xFEAE)

/////////////////////////////////////////////////
//FC00H-FCFFH
/////////////////////////////////////////////////

#define MD3         (*(__IO uint8_t  xdata *)0xFCF0)
#define MD2         (*(__IO uint8_t  xdata *)0xFCF1)
#define MD1         (*(__IO uint8_t  xdata *)0xFCF2)
#define MD0         (*(__IO uint8_t  xdata *)0xFCF3)
#define MD5         (*(__IO uint8_t  xdata *)0xFCF4)
#define MD4         (*(__IO uint8_t  xdata *)0xFCF5)
#define dwOP1       (*(__IO uint32_t xdata *)0xFCF0)
#define wOP1        (*(__IO uint16_t xdata *)0xFCF2)
#define wOP2        (*(__IO uint16_t xdata *)0xFCF4)
#define ARCON       (*(__IO uint8_t  xdata *)0xFCF6)
#define MDU16_OP_RSHIFT     (1 << 5)
#define MDU16_OP_LSHIFT     (2 << 5)
#define MDU16_OP_NORMALIZE  (3 << 5)
#define MDU16_OP_16MUL16    (4 << 5)
#define MDU16_OP_16DIV16    (5 << 5)
#define MDU16_OP_32DIV16    (6 << 5)
#define OPCON       (*(__IO uint8_t  xdata *)0xFCF7)
#define MDU16_START         0x01
#define MDU16_BUSY          0x01
#define MDU16_RESET         0x02

#define P0INTE      (*(__IO uint8_t  xdata *)0xFD00)
#define P1INTE      (*(__IO uint8_t  xdata *)0xFD01)
#define P2INTE      (*(__IO uint8_t  xdata *)0xFD02)
#define P3INTE      (*(__IO uint8_t  xdata *)0xFD03)
#define P4INTE      (*(__IO uint8_t  xdata *)0xFD04)
#define P5INTE      (*(__IO uint8_t  xdata *)0xFD05)
#define P6INTE      (*(__IO uint8_t  xdata *)0xFD06)
#define P7INTE      (*(__IO uint8_t  xdata *)0xFD07)
#define P0INTF      (*(__IO uint8_t  xdata *)0xFD10)
#define P1INTF      (*(__IO uint8_t  xdata *)0xFD11)
#define P2INTF      (*(__IO uint8_t  xdata *)0xFD12)
#define P3INTF      (*(__IO uint8_t  xdata *)0xFD13)
#define P4INTF      (*(__IO uint8_t  xdata *)0xFD14)
#define P5INTF      (*(__IO uint8_t  xdata *)0xFD15)
#define P6INTF      (*(__IO uint8_t  xdata *)0xFD16)
#define P7INTF      (*(__IO uint8_t  xdata *)0xFD17)
#define P0IM0       (*(__IO uint8_t  xdata *)0xFD20)
#define P1IM0       (*(__IO uint8_t  xdata *)0xFD21)
#define P2IM0       (*(__IO uint8_t  xdata *)0xFD22)
#define P3IM0       (*(__IO uint8_t  xdata *)0xFD23)
#define P4IM0       (*(__IO uint8_t  xdata *)0xFD24)
#define P5IM0       (*(__IO uint8_t  xdata *)0xFD25)
#define P6IM0       (*(__IO uint8_t  xdata *)0xFD26)
#define P7IM0       (*(__IO uint8_t  xdata *)0xFD27)
#define P0IM1       (*(__IO uint8_t  xdata *)0xFD30)
#define P1IM1       (*(__IO uint8_t  xdata *)0xFD31)
#define P2IM1       (*(__IO uint8_t  xdata *)0xFD32)
#define P3IM1       (*(__IO uint8_t  xdata *)0xFD33)
#define P4IM1       (*(__IO uint8_t  xdata *)0xFD34)
#define P5IM1       (*(__IO uint8_t  xdata *)0xFD35)
#define P6IM1       (*(__IO uint8_t  xdata *)0xFD36)
#define P7IM1       (*(__IO uint8_t  xdata *)0xFD37)
#define P0WKUE      (*(__IO uint8_t  xdata *)0xFD40)
#define P1WKUE      (*(__IO uint8_t  xdata *)0xFD41)
#define P2WKUE      (*(__IO uint8_t  xdata *)0xFD42)
#define P3WKUE      (*(__IO uint8_t  xdata *)0xFD43)
#define P4WKUE      (*(__IO uint8_t  xdata *)0xFD44)
#define P5WKUE      (*(__IO uint8_t  xdata *)0xFD45)
#define P6WKUE      (*(__IO uint8_t  xdata *)0xFD46)
#define P7WKUE      (*(__IO uint8_t  xdata *)0xFD47)

#define CCAPM3      (*(__IO uint8_t  xdata *)0xFD54)
#define CCAP3L      (*(__IO uint8_t  xdata *)0xFD55)
#define CCAP3H      (*(__IO uint8_t  xdata *)0xFD56)
#define PCA_PWM3    (*(__IO uint8_t  xdata *)0xFD57)

#define PIN_IP      (*(__IO uint8_t  xdata *)0xFD60)
#define PIN_IPH     (*(__IO uint8_t  xdata *)0xFD61)

#define DMA_M2M_CFG     (*(__IO uint8_t  xdata *)0xFA00)
#define DMA_M2M_CR      (*(__IO uint8_t  xdata *)0xFA01)
#define DMA_M2M_STA     (*(__IO uint8_t  xdata *)0xFA02)
#define DMA_M2M_AMT     (*(__IO uint8_t  xdata *)0xFA03)
#define DMA_M2M_DONE    (*(__IO uint8_t  xdata *)0xFA04)
#define DMA_M2M_TXA     (*(__IO uint16_t xdata *)0xFA05)
#define DMA_M2M_TXAH    (*(__IO uint8_t  xdata *)0xFA05)
#define DMA_M2M_TXAL    (*(__IO uint8_t  xdata *)0xFA06)
#define DMA_M2M_RXA     (*(__IO uint16_t xdata *)0xFA07)
#define DMA_M2M_RXAH    (*(__IO uint8_t  xdata *)0xFA07)
#define DMA_M2M_RXAL    (*(__IO uint8_t  xdata *)0xFA08)

#define DMA_ADC_CFG     (*(__IO uint8_t  xdata *)0xFA10)
#define DMA_ADC_CR      (*(__IO uint8_t  xdata *)0xFA11)
#define DMA_ADC_STA     (*(__IO uint8_t  xdata *)0xFA12)
#define DMA_ADC_RXA     (*(__IO uint16_t xdata *)0xFA17)
#define DMA_ADC_RXAH    (*(__IO uint8_t  xdata *)0xFA17)
#define DMA_ADC_RXAL    (*(__IO uint8_t  xdata *)0xFA18)
#define DMA_ADC_CFG2    (*(__IO uint8_t  xdata *)0xFA19)
#define DMA_ADC_CHSW    (*(__IO uint16_t xdata *)0xFA1A)
#define DMA_ADC_CHSW0   (*(__IO uint8_t  xdata *)0xFA1A)
#define DMA_ADC_CHSW1   (*(__IO uint8_t  xdata *)0xFA1B)

#define DMA_SPI_CFG     (*(__IO uint8_t  xdata *)0xFA20)
#define DMA_SPI_CR      (*(__IO uint8_t  xdata *)0xFA21)
#define DMA_SPI_STA     (*(__IO uint8_t  xdata *)0xFA22)
#define DMA_SPI_AMT     (*(__IO uint8_t  xdata *)0xFA23)
#define DMA_SPI_DONE    (*(__IO uint8_t  xdata *)0xFA24)
#define DMA_SPI_TXA     (*(__IO uint16_t xdata *)0xFA25)
#define DMA_SPI_TXAH    (*(__IO uint8_t  xdata *)0xFA25)
#define DMA_SPI_TXAL    (*(__IO uint8_t  xdata *)0xFA26)
#define DMA_SPI_RXA     (*(__IO uint16_t xdata *)0xFA27)
#define DMA_SPI_RXAH    (*(__IO uint8_t  xdata *)0xFA27)
#define DMA_SPI_RXAL    (*(__IO uint8_t  xdata *)0xFA28)
#define DMA_SPI_CFG2    (*(__IO uint8_t  xdata *)0xFA29)

#define DMA_UR1T_CFG    (*(__IO uint8_t  xdata *)0xFA30)
#define DMA_UR1T_CR     (*(__IO uint8_t  xdata *)0xFA31)
#define DMA_UR1T_STA    (*(__IO uint8_t  xdata *)0xFA32)
#define DMA_UR1T_AMT    (*(__IO uint8_t  xdata *)0xFA33)
#define DMA_UR1T_DONE   (*(__IO uint8_t  xdata *)0xFA34)
#define DMA_UR1T_TXA    (*(__IO uint16_t xdata *)0xFA35)
#define DMA_UR1T_TXAH   (*(__IO uint8_t  xdata *)0xFA35)
#define DMA_UR1T_TXAL   (*(__IO uint8_t  xdata *)0xFA36)
#define DMA_UR1R_CFG    (*(__IO uint8_t  xdata *)0xFA38)
#define DMA_UR1R_CR     (*(__IO uint8_t  xdata *)0xFA39)
#define DMA_UR1R_STA    (*(__IO uint8_t  xdata *)0xFA3A)
#define DMA_UR1R_AMT    (*(__IO uint8_t  xdata *)0xFA3S)
#define DMA_UR1R_DONE   (*(__IO uint8_t  xdata *)0xFA3D)
#define DMA_UR1R_RXA    (*(__IO uint16_t xdata *)0xFA3D)
#define DMA_UR1R_RXAH   (*(__IO uint8_t  xdata *)0xFA3D)
#define DMA_UR1R_RXAL   (*(__IO uint8_t  xdata *)0xFA3E)

#define DMA_UR2T_CFG    (*(__IO uint8_t  xdata *)0xFA40)
#define DMA_UR2T_CR     (*(__IO uint8_t  xdata *)0xFA41)
#define DMA_UR2T_STA    (*(__IO uint8_t  xdata *)0xFA42)
#define DMA_UR2T_AMT    (*(__IO uint8_t  xdata *)0xFA43)
#define DMA_UR2T_DONE   (*(__IO uint8_t  xdata *)0xFA44)
#define DMA_UR2T_TXA    (*(__IO uint16_t xdata *)0xFA45)
#define DMA_UR2T_TXAH   (*(__IO uint8_t  xdata *)0xFA45)
#define DMA_UR2T_TXAL   (*(__IO uint8_t  xdata *)0xFA46)
#define DMA_UR2R_CFG    (*(__IO uint8_t  xdata *)0xFA48)
#define DMA_UR2R_CR     (*(__IO uint8_t  xdata *)0xFA49)
#define DMA_UR2R_STA    (*(__IO uint8_t  xdata *)0xFA4A)
#define DMA_UR2R_AMT    (*(__IO uint8_t  xdata *)0xFA4B)
#define DMA_UR2R_DONE   (*(__IO uint8_t  xdata *)0xFA4C)
#define DMA_UR2R_RXA    (*(__IO uint16_t xdata *)0xFA4D)
#define DMA_UR2R_RXAH   (*(__IO uint8_t  xdata *)0xFA4D)
#define DMA_UR2R_RXAL   (*(__IO uint8_t  xdata *)0xFA4E)

#define DMA_UR3T_CFG    (*(__IO uint8_t  xdata *)0xFA50)
#define DMA_UR3T_CR     (*(__IO uint8_t  xdata *)0xFA51)
#define DMA_UR3T_STA    (*(__IO uint8_t  xdata *)0xFA52)
#define DMA_UR3T_AMT    (*(__IO uint8_t  xdata *)0xFA53)
#define DMA_UR3T_DONE   (*(__IO uint8_t  xdata *)0xFA54)
#define DMA_UR3T_TXA    (*(__IO uint16_t xdata *)0xFA55)
#define DMA_UR3T_TXAH   (*(__IO uint8_t  xdata *)0xFA55)
#define DMA_UR3T_TXAL   (*(__IO uint8_t  xdata *)0xFA56)
#define DMA_UR3R_CFG    (*(__IO uint8_t  xdata *)0xFA58)
#define DMA_UR3R_CR     (*(__IO uint8_t  xdata *)0xFA59)
#define DMA_UR3R_STA    (*(__IO uint8_t  xdata *)0xFA5A)
#define DMA_UR3R_AMT    (*(__IO uint8_t  xdata *)0xFA5B)
#define DMA_UR3R_DONE   (*(__IO uint8_t  xdata *)0xFA5C)
#define DMA_UR3R_RXA    (*(__IO uint16_t xdata *)0xFA5D)
#define DMA_UR3R_RXAH   (*(__IO uint8_t  xdata *)0xFA5D)
#define DMA_UR3R_RXAL   (*(__IO uint8_t  xdata *)0xFA5E)

#define DMA_UR4T_CFG    (*(__IO uint8_t  xdata *)0xFA60)
#define DMA_UR4T_CR     (*(__IO uint8_t  xdata *)0xFA61)
#define DMA_UR4T_STA    (*(__IO uint8_t  xdata *)0xFA62)
#define DMA_UR4T_AMT    (*(__IO uint8_t  xdata *)0xFA63)
#define DMA_UR4T_DONE   (*(__IO uint8_t  xdata *)0xFA64)
#define DMA_UR4T_TXA    (*(__IO uint16_t xdata *)0xFA65)
#define DMA_UR4T_TXAH   (*(__IO uint8_t  xdata *)0xFA65)
#define DMA_UR4T_TXAL   (*(__IO uint8_t  xdata *)0xFA66)
#define DMA_UR4R_CFG    (*(__IO uint8_t  xdata *)0xFA68)
#define DMA_UR4R_CR     (*(__IO uint8_t  xdata *)0xFA69)
#define DMA_UR4R_STA    (*(__IO uint8_t  xdata *)0xFA6A)
#define DMA_UR4R_AMT    (*(__IO uint8_t  xdata *)0xFA6B)
#define DMA_UR4R_DONE   (*(__IO uint8_t  xdata *)0xFA6C)
#define DMA_UR4R_RXA    (*(__IO uint16_t xdata *)0xFA6D)
#define DMA_UR4R_RXAH   (*(__IO uint8_t  xdata *)0xFA6D)
#define DMA_UR4R_RXAL   (*(__IO uint8_t  xdata *)0xFA6E)

#define DMA_LCM_CFG     (*(__IO uint8_t  xdata *)0xFA70)
#define DMA_LCM_CR      (*(__IO uint8_t  xdata *)0xFA71)
#define DMA_LCM_STA     (*(__IO uint8_t  xdata *)0xFA72)
#define DMA_LCM_AMT     (*(__IO uint8_t  xdata *)0xFA73)
#define DMA_LCM_DONE    (*(__IO uint8_t  xdata *)0xFA74)
#define DMA_LCM_TXA     (*(__IO uint16_t xdata *)0xFA75)
#define DMA_LCM_TXAH    (*(__IO uint8_t  xdata *)0xFA75)
#define DMA_LCM_TXAL    (*(__IO uint8_t  xdata *)0xFA76)
#define DMA_LCM_RXA     (*(__IO uint16_t xdata *)0xFA77)
#define DMA_LCM_RXAH    (*(__IO uint8_t  xdata *)0xFA77)
#define DMA_LCM_RXAL    (*(__IO uint8_t  xdata *)0xFA78)

/* 内置有 32 字节的只读特殊功能寄存器 CHIPID */
#define CHIPID0     (*(__IO uint8_t  xdata *)0xFDE0)
#define CHIPID1     (*(__IO uint8_t  xdata *)0xFDE1)
#define CHIPID2     (*(__IO uint8_t  xdata *)0xFDE2)
#define CHIPID3     (*(__IO uint8_t  xdata *)0xFDE3)
#define CHIPID4     (*(__IO uint8_t  xdata *)0xFDE4)
#define CHIPID5     (*(__IO uint8_t  xdata *)0xFDE5)
#define CHIPID6     (*(__IO uint8_t  xdata *)0xFDE6)
#define CHIPID7     (*(__IO uint8_t  xdata *)0xFDE7)
#define CHIPID8     (*(__IO uint8_t  xdata *)0xFDE8)
#define CHIPID9     (*(__IO uint8_t  xdata *)0xFDE9)
#define CHIPID10    (*(__IO uint8_t  xdata *)0xFDEA)
#define CHIPID11    (*(__IO uint8_t  xdata *)0xFDEB)
#define CHIPID12    (*(__IO uint8_t  xdata *)0xFDEC)
#define CHIPID13    (*(__IO uint8_t  xdata *)0xFDED)
#define CHIPID14    (*(__IO uint8_t  xdata *)0xFDEE)
#define CHIPID15    (*(__IO uint8_t  xdata *)0xFDEF)
#define CHIPID16    (*(__IO uint8_t  xdata *)0xFDF0)
#define CHIPID17    (*(__IO uint8_t  xdata *)0xFDF1)
#define CHIPID18    (*(__IO uint8_t  xdata *)0xFDF2)
#define CHIPID19    (*(__IO uint8_t  xdata *)0xFDF3)
#define CHIPID20    (*(__IO uint8_t  xdata *)0xFDF4)
#define CHIPID21    (*(__IO uint8_t  xdata *)0xFDF5)
#define CHIPID22    (*(__IO uint8_t  xdata *)0xFDF6)
#define CHIPID23    (*(__IO uint8_t  xdata *)0xFDF7)
#define CHIPID24    (*(__IO uint8_t  xdata *)0xFDF8)
#define CHIPID25    (*(__IO uint8_t  xdata *)0xFDF9)
#define CHIPID26    (*(__IO uint8_t  xdata *)0xFDFA)
#define CHIPID27    (*(__IO uint8_t  xdata *)0xFDFB)
#define CHIPID28    (*(__IO uint8_t  xdata *)0xFDFC)
#define CHIPID29    (*(__IO uint8_t  xdata *)0xFDFD)
#define CHIPID30    (*(__IO uint8_t  xdata *)0xFDFE)
#define CHIPID31    (*(__IO uint8_t  xdata *)0xFDFF)

#endif



/*----------------------------------------------------------------------------*/
/*                END OF FLIE         (C) COPYRIGHT NBUFE                     */
/*----------------------------------------------------------------------------*/
