/*-------------------------------------------------------------------
/*      (C) Copyright 2023, PSYM. All Rights Reserved
/*-------------------------------------------------------------------
/* File name   : LCD1602.c
/* Description :
/* Author      : PSYM
/*-------------------------------------------------------------------
/* Update note:
/* -----------   -----------   --------------------------------------
/*    Date         Author                       Note
/* -----------   -----------   --------------------------------------
/* 2023-05-25,     psym
/*   14:15
**/

/* 包含头文件 -------------------------------------------------------*/
#include "LCD1602.h"

/* 私有类型定义 -----------------------------------------------------*/
/* None. */

/* 私有宏定义 -------------------------------------------------------*/
/* None. */

/* 私有变量 ---------------------------------------------------------*/
/* None. */

/* 扩展变量 ---------------------------------------------------------*/
/* None. */

/* 私有函数原形 -----------------------------------------------------*/
void LCD1602_ReadBusy();
void LCD1602_WriteCmd(uint8 cmd);
void LCD1602_WriteData(uint8 dat);
void LCD1602_SetCursor(uint8 x, uint8 y);

/* 函数体 -----------------------------------------------------------*/

/**
 * @brief: LCD1602 测忙函数
 * @param: None
 * @return: None
 * @note: 判断液晶屏是否在执行其它程序
 */
void LCD1602_ReadBusy()
{
    uint8 sta;
    DB = 0xFF;
    RS = 0;
    RW = 1;
    do
    {
        EN = 1;
        sta = DB;
        EN = 0; 		   // 使能，用完就拉低，释放总线
    } while (sta & 0x80);
}

/**
 * @brief: LCD1602初始化程序
 * @param: None
 * @return: None
 * @note: None
 */
void LCD1602_Init()
{
    Delay_ms(15);
    LCD1602_WriteCmd(0x38);
    Delay_ms(5);
    LCD1602_WriteCmd(0x38);
    Delay_ms(5);
    LCD1602_WriteCmd(0x38); // 设置显示模式
    LCD1602_WriteCmd(0x0C); // 开显示，显示光标，光标不闪烁
    LCD1602_WriteCmd(0x06); // 光标右移，屏幕不移动
    LCD1602_Clear();        // 清屏
}

/**
 * @brief: LED1602清屏程序
 * @param: None
 * @return: None
 * @note: None
 */
void LCD1602_Clear()
{
    LCD1602_WriteCmd(0x01);
}

/**
 * @brief: LCD1602 写命令函数
 * @param: cmd 指令
 * @return: None
 * @note: None
 */
void LCD1602_WriteCmd(uint8 cmd)
{
    LCD1602_ReadBusy();
    RS = 0;
    RW = 0;
    DB = cmd;
    EN = 1;
	Delay_ms(5);
    EN = 0;
}

/**
 * @brief: LCD1602 写数据函数
 * @param: dat 数据
 * @return: None
 * @note: None
*/
void LCD1602_WriteData(uint8 dat)
{
    LCD1602_ReadBusy();
    RS = 1;
    RW = 0;
    DB = dat;
    EN = 1;
	Delay_ms(5);
	EN = 0;
}

/**
 * @brief: LCD1602坐标显示函数
 * @param: x, y 坐标
 * @return: None
 * @note: 设置LCD1602的光标位置
 */
void LCD1602_SetCursor(uint8 x, uint8 y)
{
    uint8 addr;
    
    if (y == 0)
        addr = 0x00 + x;
    else
        addr = 0x40 + x;

    LCD1602_WriteCmd(addr | 0x80);
}

/**
 * @brief: LCD1602滚动显示函数
 * @param: flag
 * @return: None
 * @note: 输入0不滚动屏幕，输入1左移，输入2右移
 */
void LCD_roll(uint8 flag)
{
    switch (flag)
    {
    case 0:
        LCD1602_WriteCmd(0x06);
        break;
    case 1:
        LCD1602_WriteCmd(0x18);
        break;
    case 2:
        LCD1602_WriteCmd(0x1C);
        break;
    default:
        break;
    }
}

/**
 * @brief: LCD1602 显示字符串函数
 * @param: None
 * @return: None
 * @note: None
 */
void LCD1602_ShowString(uint8 x, uint8 y, uint8 *str)
{
    LCD1602_SetCursor(x, y); // 当前字符的坐标
    while (*str != '\0')
    {
        LCD1602_WriteData(*str++);
    }
}

/*>>>>>>>>>> (C) COPYRIGHT PSYM <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
