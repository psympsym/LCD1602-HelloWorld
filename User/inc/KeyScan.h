/* -----------------------------------------------------------------------------
/* File name   : KeyScan.h
/* Author      : PSYM
/* Copyright(C): 2023 PSYM. All rights reserved.
/* -----------------------------------------------------------------------------
 */
#ifndef __KeyScan_H_
#define __KeyScan_H_

/* --------------------------------- 包含头文件 --------------------------------- */
#include "STC8Ax_REG.h"
#include "Time.h"
/* ---------------------------------- 类型定义 ---------------------------------- */
/* None. */

/* ----------------------------------- 宏定义 ----------------------------------- */
/* None. */

/* ---------------------------------- 扩展变量 ---------------------------------- */
extern uint8 roll;

/* ---------------------------------- 函数声明 ---------------------------------- */
void KeyScan();
void KeyServices();

#endif /* __KeyScan_H_ */

/*>>>>>>>>>> (C) COPYRIGHT PSYM <<<<<< >>>>>> END OF FILE <<<<<<<<<<*/