/* ---------------------------------- 包含头文件 --------------------------------- */
#include "KeyScan.h"

/* ---------------------------------- 私有宏定义 --------------------------------- */
#define KeyTime 10 // 消抖计数器的值
#define KEYPORT P5 // 按键端口

/* ---------------------------------- 私有定义 ---------------------------------- */
sbit Key1 = KEYPORT ^ 1;
sbit Key2 = KEYPORT ^ 0;
sbit Key3 = KEYPORT ^ 2;
sbit Key4 = KEYPORT ^ 3;

/* ---------------------------------- 扩展变量 ---------------------------------- */
uint8 roll = 0;

/* ---------------------------------- 私有变量 ---------------------------------- */
uint8 Keysign = 0;  // 按键标志
uint8 Key1Time = 0; // 按键计数器1, 用于按键消抖
uint8 Key2Time = 0; // 按键计数器2, 用于按键消抖
uint8 Key3Time = 0; // 按键计数器3, 用于按键消抖
uint8 Key4Time = 0; // 按键计数器4, 用于按键消抖

uint8 Key1Flag = 0; // 按键自锁标志1
uint8 Key2Flag = 0; // 按键自锁标志2
uint8 Key3Flag = 0; // 按键自锁标志3
uint8 Key4Flag = 0; // 按键自锁标志4

/* ---------------------------------- 私有函数 ---------------------------------- */

/**
 * @brief 按键扫描
 * @note 普通按键扫描
 */
void KeyScan()
{
    if (Key1 == 1) // 按键释放
    {
        Key1Flag = 1; // 按键标志开
        Key1Time = 0; // 按键计数器1置0
    }
    else if (Key1Flag)
    {
        // 按键消抖
        if (++Key1Time > KeyTime)
        {
            Key1Time = 0; // 按键计数器1置0
            Key1Flag = 0; // 按键标志关
            Keysign = 1;  // 按键标志置1
        }
    }

    if (Key2 == 1) // 按键释放
    {
        Key2Flag = 1; // 按键标志开
        Key2Time = 0; // 按键计数器2置0
    }
    else if (Key2Flag)
    {
        // 按键消抖
        if (++Key2Time > KeyTime)
        {
            Key2Time = 0; // 按键计数器2置0
            Key2Flag = 0; // 按键标志关
            Keysign = 2;  // 按键标志置2
        }
    }

    if (Key3 == 1) // 按键释放
    {
        Key3Flag = 1; // 按键标志开
        Key3Time = 0; // 按键计数器3置0
    }
    else if (Key3Flag)
    {
        // 按键消抖
        if (++Key3Time > KeyTime)
        {
            Key3Time = 0; // 按键计数器3置0
            Key3Flag = 0; // 按键标志关
            Keysign = 3;  // 按键标志置3
        }
    }

    if (Key4 == 1) // 按键释放
    {
        Key4Flag = 1; // 按键标志开
        Key4Time = 0; // 按键计数器4置0
    }
    else if (Key4Flag)
    {
        // 按键消抖
        if (++Key4Time > KeyTime)
        {
            Key4Time = 0; // 按键计数器4置0
            Key4Flag = 0; // 按键标志关
            Keysign = 4;  // 按键标志置4
        }
    }
}

/**
 * @brief 按键服务程序
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