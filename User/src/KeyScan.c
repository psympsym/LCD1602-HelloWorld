/* ---------------------------------- ����ͷ�ļ� --------------------------------- */
#include "KeyScan.h"

/* ---------------------------------- ˽�к궨�� --------------------------------- */
#define KeyTime 10 // ������������ֵ
#define KEYPORT P5 // �����˿�

/* ---------------------------------- ˽�ж��� ---------------------------------- */
sbit Key1 = KEYPORT ^ 1;
sbit Key2 = KEYPORT ^ 0;
sbit Key3 = KEYPORT ^ 2;
sbit Key4 = KEYPORT ^ 3;

/* ---------------------------------- ��չ���� ---------------------------------- */
uint8 roll = 0;

/* ---------------------------------- ˽�б��� ---------------------------------- */
uint8 Keysign = 0;  // ������־
uint8 Key1Time = 0; // ����������1, ���ڰ�������
uint8 Key2Time = 0; // ����������2, ���ڰ�������
uint8 Key3Time = 0; // ����������3, ���ڰ�������
uint8 Key4Time = 0; // ����������4, ���ڰ�������

uint8 Key1Flag = 0; // ����������־1
uint8 Key2Flag = 0; // ����������־2
uint8 Key3Flag = 0; // ����������־3
uint8 Key4Flag = 0; // ����������־4

/* ---------------------------------- ˽�к��� ---------------------------------- */

/**
 * @brief ����ɨ��
 * @note ��ͨ����ɨ��
 */
void KeyScan()
{
    if (Key1 == 1) // �����ͷ�
    {
        Key1Flag = 1; // ������־��
        Key1Time = 0; // ����������1��0
    }
    else if (Key1Flag)
    {
        // ��������
        if (++Key1Time > KeyTime)
        {
            Key1Time = 0; // ����������1��0
            Key1Flag = 0; // ������־��
            Keysign = 1;  // ������־��1
        }
    }

    if (Key2 == 1) // �����ͷ�
    {
        Key2Flag = 1; // ������־��
        Key2Time = 0; // ����������2��0
    }
    else if (Key2Flag)
    {
        // ��������
        if (++Key2Time > KeyTime)
        {
            Key2Time = 0; // ����������2��0
            Key2Flag = 0; // ������־��
            Keysign = 2;  // ������־��2
        }
    }

    if (Key3 == 1) // �����ͷ�
    {
        Key3Flag = 1; // ������־��
        Key3Time = 0; // ����������3��0
    }
    else if (Key3Flag)
    {
        // ��������
        if (++Key3Time > KeyTime)
        {
            Key3Time = 0; // ����������3��0
            Key3Flag = 0; // ������־��
            Keysign = 3;  // ������־��3
        }
    }

    if (Key4 == 1) // �����ͷ�
    {
        Key4Flag = 1; // ������־��
        Key4Time = 0; // ����������4��0
    }
    else if (Key4Flag)
    {
        // ��������
        if (++Key4Time > KeyTime)
        {
            Key4Time = 0; // ����������4��0
            Key4Flag = 0; // ������־��
            Keysign = 4;  // ������־��4
        }
    }
}

/**
 * @brief �����������
 */
void KeyServices()
{
    switch (Keysign)
    {
    case 1:
        roll = 1;
        break;
    case 2:
        roll = 2;
        break;
    case 3:
        roll = 0;
        break;
    case 4:
        break;
    default:
        break;
    }
    Keysign = 0;
}