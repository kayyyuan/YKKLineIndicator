//
//  YKIndicatorLib.h
//  YKKline
//
//  Created by nethanhan on 2017/6/5.
//  Copyright © 2017年 nethanhan. All rights reserved.
//

#ifndef YKIndicatorLib_h
#define YKIndicatorLib_h

#include <stdio.h>

/**
 生成MA指标
 
 @param value OHLC二维数组
 @param length 数组长度
 @param m1 参数m1
 @param m2 参数m2
 @param m3 参数m3
 @param ma1 参数m1存放的数组
 @param ma2 参数m2存放的数组
 @param ma3 参数m3存放的数组
 */
void YKCalMAIndicator(double value[][4],
                    int length,
                    int m1,
                    int m2,
                    int m3,
                    double ma1[],
                    double ma2[],
                    double ma3[]);

/**
 生成BOLL指标
 
 @param value HLOC二维数组
 @param length 数组长度
 @param m 参数m
 @param boll 存储boll值的数组
 @param ub 存储ub值的数组
 @param lb 存储lb值的数组
 */
void YKCalBOLLIndicator(double value[][4],
                      int length,
                      int m,
                      double boll[],
                      double ub[],
                      double lb[]);

/**
 生成MACD指标
 
 @param value hloc二维数组
 @param length 数组长度
 @param SHORT 参数short
 @param LONG 参数long
 @param MID 参数mid
 @param dif 存储dif值的数组
 @param dea 存储dea值的数组
 @param macd 存储macd值的数组
 */
void YKCalMACDIndicator(double value[][4],
                      int length,
                      int SHORT,
                      int LONG,
                      int MID,
                      double dif[],
                      double dea[],
                      double macd[]);

/**
 生成KDJ指标
 
 @param value HLOC二维数组
 @param length 数组长度
 @param n 参数n
 @param m1 参数m1
 @param m2 参数m2
 @param kdjK 存放k值的数组
 @param kdjD 存放d值的数组
 @param kdjJ 存放j值的数组
 */
void YKCalKDJIndicator(double value[][4],
                     int length,
                     int n,
                     int m1,
                     int m2,
                     double kdjK[],
                     double kdjD[],
                     double kdjJ[]);

/**
 生成RSI指标
 
 @param value HLOC二维数组
 @param length 数组长度
 @param n1 参数n1
 @param n2 参数n2
 @param n3 参数n3
 @param RSI1 存储周期n1的数组
 @param RSI2 存储周期n2的数组
 @param RSI3 存储周期n3的数组
 */
void YKCalRSIIndicator(double value[][4],
                     int length,
                     int n1,
                     int n2,
                     int n3,
                     double RSI1[],
                     double RSI2[],
                     double RSI3[]);

/**
 生成BIAS指标
 
 @param value HLOC二维数组
 @param length 数组长度
 @param n1 参数n1
 @param n2 参数n2
 @param n3 参数n3
 @param BIAS1 存储周期n1的数组
 @param BIAS2 存储周期n2的数组
 @param BIAS3 存储周期n3的数组
 */
void YKCalBIASIndicator(double value[][4],
                      int length,
                      int n1,
                      int n2,
                      int n3,
                      double BIAS1[],
                      double BIAS2[],
                      double BIAS3[]);

/**
 计算ATR指标值
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数值
 @param atr 存储atr数组参数
 @param mtr 存储mtr数组参数
 */
void YKCalATRIndicator(const double PRICE[][4],
                     const int count,
                     const int N,
                     double atr[],
                     double mtr[]);

/**
 计算CCI指标值
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数
 @param CCI CCI数组参数
 */
void YKCalCCIIndicator(const double PRICE[][4],
                       const int count,
                       const int N,
                       double CCI[]);

/**
 计算DMI指标
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数值
 @param M M参数值
 @param smooth 平滑值
 @param PDI 存储PDI数组参数
 @param MDI 存储MDI数组参数
 @param ADX 存储ADX数组参数
 @param ADXR 存储ADXR数组参数
 */
void YKCalDMIIndicator(const double PRICE[][4],
                       const int count,
                       const int N,
                       const int M,
                       const double smooth,
                       double PDI[],
                       double MDI[],
                       double ADX[],
                       double ADXR[]);

/**
 计算WR指标值
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数
 @param N1 N1参数
 @param WR1 存储WR1数组参数
 @param WR2 存储WR2数组参数
 */
void YKCalWRIndicator(const double PRICE[][4],
                      const int count,
                      const int N,
                      const int N1,
                      double WR1[],
                      double WR2[]);

/**
 计算CR指标值
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数值
 @param M1 M1参数值，必须为2.5的整数倍
 @param M2 M2参数值，必须为2.5的整数倍
 @param M3 M3参数值，必须为2.5的整数倍
 @param M4 M4参数值，必须为2.5的整数倍
 @param CR 存储CR数组参数
 @param MA1 存储MA1数组参数
 @param MA2 存储MA2数组参数
 @param MA3 存储MA3数组参数
 @param MA4 存储MA4数组参数
 */
void YKCalCRIndicator(const double PRICE[][4],
                      const int count,
                      const int N,
                      const int M1,
                      const int M2,
                      const int M3,
                      const int M4,
                      double CR[],
                      double MA1[],
                      double MA2[],
                      double MA3[],
                      double MA4[]);

/**
 计算DMA指标
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N1 N1参数
 @param N2 N2参数
 @param M M参数
 @param DIF DIF数组参数
 @param DIFMA DIFMA数组参数
 */
void YKCalDMAIndicator(const double PRICE[][4],
                       const int count,
                       const int N1,
                       const int N2,
                       const int M,
                       double DIF[],
                       double DIFMA[]);

/**
 计算BRAR指标值
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数
 @param BR BR数组参数
 @param AR AR数组参数
 */
void YKCalBRARIndicator(const double PRICE[][4],
                        const int count,
                        const int N,
                        double BR[],
                        double AR[]);

/**
 计算ENV指标值
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数
 @param M1 M1参数
 @param M2 M2参数
 @param UPPER 存储UPPER数组参数
 @param LOWER 存储LOWER数组参数
 @param MID 存储MID数组参数
 */
void YKCalENVIndicator(const double PRICE[][4],
                       const int count,
                       const int N,
                       const int M1,
                       const int M2,
                       double UPPER[],
                       double LOWER[],
                       double MID[]);

/**
 计算EXPMA指标
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param M1 第M1参数
 @param M2 第M2参数
 @param M3 第M3参数
 @param M4 第M4参数
 @param EXP1 存储EXP1数组
 @param EXP2 存储EXP2数组
 @param EXP3 存储EXP3数组
 @param EXP4 存储EXP4数组
 */
void YKCalEXPMAIndicator(const double PRICE[][4],
                         const int count,
                         const int M1,
                         const int M2,
                         const int M3,
                         const int M4,
                         double EXP1[],
                         double EXP2[],
                         double EXP3[],
                         double EXP4[]);

/**
 计算DPO指标
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N 第1个参数
 @param M 第2个参数
 @param DPO 存储DPO数组
 @param MADPO 存储MADPO数组
 */
void YKCalDPOIndicator(const double PRICE[][4],
                       const int count,
                       const int N,
                       const int M,
                       double DPO[],
                       double MADPO[]);

/**
 计算CDP指标值
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数
 @param CDP 存储CDP的数组
 @param AH 存储AH的数组
 @param AL 存储AL的数组
 @param NH 存储NH的数组
 @param NL 存储NL的数组
 */
void YKCalCDPIndicator(const double PRICE[][4],
                       const int count,
                       const int N,
                       double CDP[],
                       double AH[],
                       double AL[],
                       double NH[],
                       double NL[]);

/**
 计算PSY指标
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数
 @param M M参数
 @param PSY 存储PSY的数组
 @param PSYMA 存储PSYMA的数组
 */
void YKCalPSYIndicator(const double PRICE[][4],
                       const int count,
                       const int N,
                       const int M,
                       double PSY[],
                       double PSYMA[]);

/**
 计算ROC指标值
 
 @param PRICE HLOC数组
 @param count 数组大小
 @param N N参数
 @param M M参数
 @param ROC 存储ROC的数组
 @param ROCMA 存储ROCMA的数组
 */
void YKCalROCIndicator(const double PRICE[][4],
                       const int count,
                       const int N,
                       const int M,
                       double ROC[],
                       double ROCMA[]);

#endif /* YKIndicatorLib_h */
