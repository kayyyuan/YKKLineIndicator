//
//  YKIndicatorBaseLib.h
//  YKKline
//
//  Created by nethanhan on 2017/6/5.
//  Copyright © 2017年 nethanhan. All rights reserved.
//

#ifndef YKIndicatorBaseLib_h
#define YKIndicatorBaseLib_h

#include <stdio.h>

/**
 计算ma值
 
 @param value 初始数据数组
 @param length 初始数据数组长度
 @param m 参数m值
 @param ma 存储ma值的数组
 */
void calMa(const double value[], int length, int m, double ma[]);

/**
 计算ema值
 
 @param value 初始数据数组
 @param length 初始数据数组长度
 @param n 参数n值
 @param ema 存储ema值的数组
 */
void calEma(const double value[], int length, int n, double ema[]);

/**
 计算sma值
 
 @param value 初始数据数组
 @param length 初始数据数组长度
 @param n 参数n值
 @param m 参数m值
 @param sma 存储sma值的数组
 */
void calSma(const double value[], int length, int n, int m, double sma[]);

/**
 计算hhv值
 
 @param value HLOC二维数组
 @param length 数组长度
 @param n 周期值
 @param index HLOC二维数组当前的索引值
 @param x 0最高价-1最低价-2开盘价-3收盘价
 @return 返回hhv值
 */
double calHhv(const double value[][4], int length, int n, int index, int x);

/**
 计算llv值
 
 @param value HLOC二维数组
 @param length 数组长度
 @param n 周期值
 @param index HLOC二维数组当前的索引值
 @param x 0最高价-1最低价-2开盘价-3收盘价
 @return 返回llv值
 */
double calLlv(const double value[][4], int length, int n, int index, int x);

/**
 计算REF值
 
 @param value 原始数组
 @param length 数组长度
 @param index 当前数组下标值
 @param n 取前n个周期的值
 @return 返回ref值
 */
double calRef(const double value[], int length, int index, int n);

/**
 计算STD值
 
 @param x 第一个差值数组
 @param n 第二个差值
 @param length 数组长度
 @param index 第一个差值数组当前的索引
 @return 返回计算值
 */
double calStd(double x[], double n, int length, int index);

/**
 计算平均绝对偏差
 
 @param X 第一个参数
 @param U 第二个参数
 @param count N
 @return 返回计算结果值
 */
double calAVEDEV(const double X[], const double U[], const int count);

/**
 计算平滑指数移动平均
 
 @param dataX 数据数组
 @param countX 数组大小
 @param N expmema(N)中的N的值
 @param smooth 平滑值
 @param expmema 存储计算后的值得数组
 */
void calEXPMEMA(const double dataX[],
                const int countX,
                const int N,
                const double smooth,
                double expmema[]);


/**
 计算综合
 
 @param data 数据数组
 @param N 周期值
 @param I 索引值
 @return 总和值
 */
double calSum(const double data[],
              const int N,
              const int I);

#endif /* YKIndicatorBaseLib_h */
