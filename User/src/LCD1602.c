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

/* ����ͷ�ļ� -------------------------------------------------------*/
#include "LCD1602.h"

/* ˽�����Ͷ��� -----------------------------------------------------*/
/* None. */

/* ˽�к궨�� -------------------------------------------------------*/
/* None. */

/* ˽�б��� ---------------------------------------------------------*/
/* None. */

/* ��չ���� ---------------------------------------------------------*/
/* None. */

/* ˽�к���ԭ�� -----------------------------------------------------*/
void LCD1602_ReadBusy();
void LCD1602_WriteCmd(uint8 cmd);
void LCD1602_WriteData(uint8 dat);
void LCD1602_SetCursor(uint8 x, uint8 y);

/* ������ -----------------------------------------------------------*/

/**
 * @brief: LCD1602 ��æ����
 * @param: None
 * @return: None
 * @note: �ж�Һ�����Ƿ���ִ����������
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
        EN = 0; 		   // ʹ�ܣ���������ͣ��ͷ�����
    } while (sta & 0x80);
}

/**
 * @brief: LCD1602��ʼ������
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
    LCD1602_WriteCmd(0x38); // ������ʾģʽ
    LCD1602_WriteCmd(0x0C); // ����ʾ����ʾ��꣬��겻��˸
    LCD1602_WriteCmd(0x06); // ������ƣ���Ļ���ƶ�
    LCD1602_Clear();        // ����
}

/**
 * @brief: LED1602��������
 * @param: None
 * @return: None
 * @note: None
 */
void LCD1602_Clear()
{
    LCD1602_WriteCmd(0x01);
}

/**
 * @brief: LCD1602 д�����
 * @param: cmd ָ��
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
 * @brief: LCD1602 д���ݺ���
 * @param: dat ����
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
 * @brief: LCD1602������ʾ����
 * @param: x, y ����
 * @return: None
 * @note: ����LCD1602�Ĺ��λ��
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
 * @brief: LCD1602������ʾ����
 * @param: flag
 * @return: None
 * @note: ����0��������Ļ������1���ƣ�����2����
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
 * @brief: LCD1602 ��ʾ�ַ�������
 * @param: None
 * @return: None
 * @note: None
 */
void LCD1602_ShowString(uint8 x, uint8 y, uint8 *str)
{
    LCD1602_SetCursor(x, y); // ��ǰ�ַ�������
    while (*str != '\0')
    {
        LCD1602_WriteData(*str++);
    }
}

/*>>>>>>>>>> (C) COPYRIGHT PSYM <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/
