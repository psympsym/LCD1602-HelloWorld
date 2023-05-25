/*-------------------------------------------------------------------
/*      (C) Copyright 2023, PSYM. All Rights Reserved
/*-------------------------------------------------------------------
/* File name   : Time.c
/* Description :
/* Author      : PSYM
/*-------------------------------------------------------------------
/* Update note:
/* -----------   -----------   --------------------------------------
/*    Date         Author                       Note
/* -----------   -----------   --------------------------------------
/* 2023-05-25,     psym
/*   14:08
**/

/* ����ͷ�ļ� -------------------------------------------------------*/
#include "Time.h"

/* ˽�����Ͷ��� -----------------------------------------------------*/
/* None. */

/* ˽�к궨�� -------------------------------------------------------*/
/* None. */

/* ˽�б��� ---------------------------------------------------------*/
uint8 count;

/* ��չ���� ---------------------------------------------------------*/

/* ˽�к���ԭ�� -----------------------------------------------------*/
/* None. */

/* ������ -----------------------------------------------------------*/

/**
 * @brief: ��ʱ��0��ʼ��
 * @param: None
 * @return: None
 * @note: None
 */
void Time0_Config()
{
    // @24MHZ 1ms 12Tʱ��ģʽ
    TMOD &= 0xF0; // ����T0�Ŀ���λ
    TMOD |= 0x01; // ����T0Ϊģʽ1
    // ����Ϊ1ms
    TH0 = (65536 - 2000) / 256;
    TL0 = (65536 - 2000) % 256;
    TF0 = 0; // ���TF0��־
    ET0 = 1;
    TR0 = 1; // ��ʱ��0��ʼ��ʱ
}

void Time0_ISR() interrupt 1
{
    TF0 = 0;
    TR0 = 0;

    if (++count % 200 == 0)
    {
        LCD1602_ShowString(10, 0, "1602LCD");
        LCD1602_ShowString(15, 1, "HELLO WORLD");
        LCD_roll(roll);
    }
    
	KeyScan();

    TH0 = (65536 - 2000) / 256;
    TL0 = (65536 - 2000) % 256;
    TR0 = 1;
}

/*>>>>>>>>>> (C) COPYRIGHT PSYM <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/