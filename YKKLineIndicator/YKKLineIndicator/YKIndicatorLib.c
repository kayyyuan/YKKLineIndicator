//
//  YKIndicatorLib.c
//  YKKline
//
//  Created by nethanhan on 2017/6/5.
//  Copyright © 2017年 nethanhan. All rights reserved.
//

#include "YKIndicatorLib.h"
#include "YKIndicatorBaseLib.h"
#include <math.h>

#pragma mark - BOLL布林线

/**
 计算std值

 @param close 收盘价数组
 @param length 数组长度
 @param m 参数m
 @param std 存储std值的数组
 */
void calBollStd(double close[], int length, int m, double std[])
{
    for (int idx=0; idx<length; idx++)
    {
        std[idx] = calStd(close, m, length, idx);
    }
}

/**
 计算ub值

 @param std std数组
 @param boll boll数组
 @param length 数组长度
 @param ub 存储ub值的数组
 */
void calUb(double std[], double boll[], int length, double ub[])
{
    for (int idx=0; idx<length; idx++)
    {
        ub[idx] = boll[idx] + 2 * std[idx];
    }
}

/**
 计算lb值

 @param std std数组
 @param boll boll数组
 @param length 数组长度
 @param lb 存储lb值的数组
 */
void calLb(double std[], double boll[], int length, double lb[])
{
    for (int idx=0; idx<length; idx++)
    {
        lb[idx] = boll[idx] - 2 * std[idx];
    }
}

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
                      double lb[])
{
    /*
     指标公式
     BOLL:MA(CLOSE,M);
     UB:BOLL+2*STD(CLOSE,M);
     LB:BOLL-2*STD(CLOSE,M);
     */
    double close[length];
    for (int idx=0; idx<length; idx++)
    {
        close[idx] = value[idx][3];
    }
    
    calMa(close, length, m, boll);
    double std[length];
    calBollStd(close, length, m, std);
    calUb(std, boll, length, ub);
    calLb(std, boll, length, lb);
}

#pragma mark - MA 均线

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
                    double ma3[])
{
    /*
     指标公式
     MA1:MA(CLOSE,M1);
     MA2:MA(CLOSE,M2);
     MA3:MA(CLOSE,M3);
     */
    double close[length];
    for (int idx=0; idx<length; idx++)
    {
        close[idx] = value[idx][3];
    }
    
    calMa(close, length, m1, ma1);
    calMa(close, length, m2, ma2);
    calMa(close, length, m3, ma3);
}

#pragma mark - MACD 平滑异同平均

/**
 计算macd指标中的dif值

 @param close 收盘价数组
 @param length 数组长度
 @param dif 存储dif值的数组
 @param SHORT 参数short值
 @param LONG 参数long值
 */
void calDif(double close[],
            int length,
            double dif[],
            int SHORT,
            int LONG)
{
    double shortEma[length];
    double longEma[length];
    
    calEma(close, length, SHORT, shortEma);
    calEma(close, length, LONG, longEma);
    
    for (int idx=0; idx<length; idx++)
    {
        dif[idx] = shortEma[idx] - longEma[idx];
    }
}

/**
 计算macd指标中的dea值

 @param dif dif数组
 @param dea dea数组
 @param length 数组长度
 @param MID 参数mid值
 */
void calDea(double dif[],
            double dea[],
            int length,
            int MID)
{
    calEma(dif, length, MID, dea);
}

/**
 计算macd指标中的macd值

 @param dif dif数组
 @param dea dea数组
 @param length 数组长度
 @param macd 存储macd值的数组
 */
void calMacd(double dif[],
             double dea[],
             int length,
             double macd[])
{
    for (int idx=0; idx<length; idx++)
    {
        macd[idx] = (dif[idx] - dea[idx]) * 2.f;
    }
}

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
                      double macd[])
{
    /*
     指标公式
     DIF:EMA(CLOSE,SHORT)-EMA(CLOSE,LONG);
     DEA:EMA(DIF,MID);
     MACD:(DIF-DEA)*2,COLORSTICK;
     */
    double close[length];
    for (int idx=0; idx<length; idx++)
    {
        close[idx] = value[idx][3];
    }
    
    calDif(close, length, dif, SHORT, LONG);
    calDea(dif, dea, length, MID);
    calMacd(dif, dea, length, macd);
}

#pragma mark - KDJ 随机指标

/**
 计算KDJ中的rsv值

 @param value HLOC二维数组
 @param length 数组长度
 @param n 参数n
 @param rsv 存放rsv值的数组
 */
void calRsv(double value[][4], int length, int n, double rsv[])
{
    double llv = 0;
    double hhv = 0;
    for (int idx=0; idx<length; idx++)
    {
        llv = calLlv(value, length, n, idx, 1);
        hhv = calHhv(value, length, n, idx, 0);
        rsv[idx] = (value[idx][3] - llv)/ (hhv - llv) * 100;
    }
}

/**
 计算KDJ中的k值

 @param rsv rsv值数组
 @param length 数组长度
 @param m1 参数m1
 @param kdjK 存放k值的数组
 */
void calKdjK(double rsv[], int length, int m1, double kdjK[])
{
    calSma(rsv, length, m1, 1, kdjK);
}

/**
 计算KDJ中的d值

 @param kdjK k值数组
 @param length 数组长度
 @param m2 参数m2
 @param kdjD 存放d值的数组
 */
void calKdjD(double kdjK[], int length, int m2, double kdjD[])
{
    calSma(kdjK, length, m2, 1, kdjD);
}


/**
 计算KDJ中的j值

 @param kdjK k值数组
 @param kdjD d值数组
 @param length 数组长度
 @param kdjJ 存放j值的数组
 */
void calKdjJ(double kdjK[], double kdjD[], int length, double kdjJ[])
{
    for (int idx=0; idx<length; idx++)
    {
        kdjJ[idx] = 3 * kdjK[idx] - 2 * kdjD[idx];
    }
}

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
                     double kdjJ[])
{
    /*
     指标公式
     RSV:=(CLOSE-LLV(LOW,N))/(HHV(HIGH,N)-LLV(LOW,N))*100;
     K:SMA(RSV,M1,1);
     D:SMA(K,M2,1);
     J:3*K-2*D;
     */
    double rsv[length];
    calRsv(value, length, n, rsv);
    calKdjK(rsv, length, m1, kdjK);
    calKdjD(kdjK, length, m2, kdjD);
    calKdjJ(kdjK, kdjD, length, kdjJ);
}

#pragma mark - RSI 相对强弱指标

/**
 计算RSI中的rsi值

 @param close 收盘价数组
 @param length 数组长度
 @param n 参数n
 @param rsi 存储rsi值的数组
 */
void calRsi(double close[], int length, int n, double rsi[])
{
    double maxArr[length];
    double absArr[length];
    
    for (int idx=0; idx<length; idx++)
    {
        maxArr[idx] = fmax(close[idx] - calRef(close, length, idx, 1), 0);
        absArr[idx] = fabs(close[idx] - calRef(close, length, idx, 1));
    }
    
    double maxSma[length];
    double absSma[length];
    calSma(maxArr, length, n, 1, maxSma);
    calSma(absArr, length, n, 1, absSma);
    
    for (int idx=0; idx<length; idx++)
    {
        rsi[idx] = maxSma[idx] / absSma[idx] * 100;
    }
}

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
                     double RSI3[])
{
    /*
     指标公式
     LC:=REF(CLOSE,1);
     RSI1:SMA(MAX(CLOSE-LC,0),N1,1)/SMA(ABS(CLOSE-LC),N1,1)*100;
     RSI2:SMA(MAX(CLOSE-LC,0),N2,1)/SMA(ABS(CLOSE-LC),N2,1)*100;
     RSI3:SMA(MAX(CLOSE-LC,0),N3,1)/SMA(ABS(CLOSE-LC),N3,1)*100;
     */
    double close[length];
    for (int idx=0; idx<length; idx++)
    {
        close[idx] = value[idx][3];
    }
    
    calRsi(close, length, n1, RSI1);
    calRsi(close, length, n2, RSI2);
    calRsi(close, length, n3, RSI3);
}

#pragma mark - BIAS 乖离率

/**
 计算BIAS中的bias值

 @param close 收盘价数组
 @param length 数组长度
 @param n 周期参数n
 @param bias 存放bias值的数组
 */
void calBias(double close[],
             int length,
             int n,
             double bias[])
{
    double closeMa[length];
    calMa(close, length, n, closeMa);
    
    for (int idx=0; idx<length; idx++)
    {
        bias[idx] = (close[idx] - closeMa[idx]) / closeMa[idx] * 100;
    }
}

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
                      double BIAS3[])
{
    /*
     指标公式
     BIAS1 :(CLOSE-MA(CLOSE,N1))/MA(CLOSE,N1)*100;
     BIAS2 :(CLOSE-MA(CLOSE,N2))/MA(CLOSE,N2)*100;
     BIAS3 :(CLOSE-MA(CLOSE,N3))/MA(CLOSE,N3)*100;
     */
    double close[length];
    for (int idx=0; idx<length; idx++)
    {
        close[idx] = value[idx][3];
    }
    
    calBias(close, length, n1, BIAS1);
    calBias(close, length, n2, BIAS2);
    calBias(close, length, n3, BIAS3);
}

#pragma mark - ATR 真实波幅

/**
 计算ATR中的MTR值

 @param PRICE HLOC数组
 @param count 数组大小
 @param mtr 存储mtr的值
 */
void calMTR(const double PRICE[][4],
           const int count,
           double mtr[])
{
    double close[count];
    for(int i=0; i<count; i++)
    {
        close[i] = PRICE[i][3];
    }
    for (int i=0; i<count; i++)
    {
        double ref = calRef(close, count, i, 1);
        double maxArgs = fmax((PRICE[i][0] - PRICE[i][1]), fabs(ref-PRICE[i][0]));
        mtr[i] = fmax(maxArgs, fabs(ref-PRICE[i][1]));
    }
}


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
                     double mtr[])
{
    calMTR(PRICE, count, mtr);
    calMa(mtr, count, N, atr);
}

#pragma mark - CCI 商品路径指标

void calCCITYP(const double PRICE[][4],
            const int count,
            const int N,
            double TYP[],
            double TYPMA[])
{
    for (int i=0; i<count; i++)
    {
        TYP[i] = (PRICE[i][0] + PRICE[i][1] + PRICE[i][3])/3.f;
    }
    
    calMa(TYP, count, N, TYPMA);
}

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
                  double CCI[])
{
    double TYP[count];
    double TYPMA[count];
    calCCITYP(PRICE, count, N, TYP,TYPMA);
    
    for (int i=0; i<count; i++)
    {
        CCI[i] = (TYP[i] - TYPMA[i]) / (0.015 * calAVEDEV(TYP, TYPMA, i));
    }
}

#pragma mark - DMI 趋向指标

void calDMIMTR(const double PRICE[][4],
            const int count,
            const int N,
            const double smooth,
            double MTR[])
{
    double close[count];
    for (int i=0; i<count; i++)
    {
        close[i] = PRICE[i][3];
    }
    double maxValue[count];
    for (int i=0; i<count; i++)
    {
        double ref = calRef(close, count, i, 1);
        double maxArgs = fmax(PRICE[i][0]-PRICE[i][1], fabs(PRICE[i][0] - ref));
        maxValue[i] = fmax(maxArgs, fabs(ref - PRICE[i][1]));
    }
    
    calEXPMEMA(maxValue, count, N, smooth, MTR);
}

void calDMIHD(const double PRICE[][4],
           const int count,
           double HD[])
{
    double high[count];
    for (int i=0; i<count; i++)
    {
        high[i] = PRICE[i][0];
    }
    
    for (int i=0; i<count; i++)
    {
        HD[i] = high[i] - calRef(high, count, i, 1);
    }
}

void calDMILD(const double PRICE[][4],
           const int count,
           double LD[])
{
    double low[count];
    for (int i=0; i<count; i++)
    {
        low[i] = PRICE[i][1];
    }
    
    for (int i=0; i<count; i++)
    {
        LD[i] = calRef(low, count, i, 1) - low[i];
    }
}

void calDMIDMP(const double PRICE[][4],
            const int count,
            const int N,
            const double smooth,
            const double HD[],
            const double LD[],
            double DMP[])
{
    double dmpMiddle[count];
    for (int i=0; i<count; i++)
    {
        if ((HD[i] > 0.f) && (HD[i] > LD[i]))
        {
            dmpMiddle[i] = HD[i];
        } else
        {
            dmpMiddle[i] = 0.f;
        }
    }
    
    calEXPMEMA(dmpMiddle, count, N, smooth, DMP);
}

void calDMIDMM(const double PRICE[][4],
            const int count,
            const int N,
            const double smooth,
            const double HD[],
            const double LD[],
            double DMM[])
{
    double dmmMiddle[count];
    for (int i=0; i<count; i++)
    {
        if ((LD[i] > 0.f) && (LD[i] > HD[i]))
        {
            dmmMiddle[i] = LD[i];
        } else
        {
            dmmMiddle[i] = 0.f;
        }
    }
    
    calEXPMEMA(dmmMiddle, count, N, smooth, DMM);
}

void calDMIPDI(const double DMP[],
            const double MTR[],
            const int count,
            double PDI[])
{
    for (int i=0; i<count; i++)
    {
        PDI[i] = DMP[i] * 100 / MTR[i];
    }
}

void calDMIMDI(const double DMM[],
            const double MTR[],
            const int count,
            double MDI[])
{
    for (int i=0; i<count; i++)
    {
        MDI[i] = DMM[i] * 100 / MTR[i];
    }
}

void calDMIADX(const double MDI[],
            const double PDI[],
            const int count,
            const int M,
            const double smooth,
            double ADX[])
{
    double adxMiddle[count];
    for (int i=0; i<count; i++)
    {
        adxMiddle[i] = fabs(MDI[i] - PDI[i])/(MDI[i] + PDI[i]) * 100;
    }
    
    calEXPMEMA(adxMiddle, count, M, smooth, ADX);
}

void calDMIADXR(const double ADX[],
             const int count,
             const double smooth,
             const int M,
             double ADXR[])
{
    calEXPMEMA(ADX, count, M, smooth, ADXR);
}


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
                     double ADXR[])
{
    double MTR[count];
    double HD[count];
    double LD[count];
    calDMIMTR(PRICE, count, N, smooth, MTR);
    calDMIHD(PRICE, count, HD);
    calDMILD(PRICE, count, LD);
    
    double DMP[count];
    double DMM[count];
    calDMIDMP(PRICE, count, N, smooth, HD, LD, DMP);
    calDMIDMM(PRICE, count, N, smooth, HD, LD, DMM);
    
    calDMIPDI(DMP, MTR, count, PDI);
    calDMIMDI(DMM, MTR, count, MDI);
    calDMIADX(MDI, PDI, count, M, smooth, ADX);
    calDMIADXR(ADX, count, smooth, M, ADXR);
}

#pragma mark - WR 威廉指标

void calWRWR(const double PRICE[][4],
             const int count,
             const int N,
             double WR1[])
{
    for (int i=0; i<count; i++)
    {
        double hhv = calHhv(PRICE, count, N, i, 0);
        double llv = calLlv(PRICE, count, N, i, 1);
        WR1[i] = 100 * (hhv - PRICE[i][3]) / (hhv - llv);
    }
}


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
                    double WR2[])
{
    calWRWR(PRICE, count, N, WR1);
    calWRWR(PRICE, count, N1, WR2);
}

#pragma mark - CR 带状能量线

void calCRMID(const double PRICE[][4],
              const int count,
              double MID[])
{
    double sum[count];
    for (int i=0; i<count; i++)
    {
        sum[i] = PRICE[i][0] + PRICE[i][1];
    }
    
    for (int i=0; i<count; i++)
    {
        MID[i] = calRef(sum, count, i, 1) / 2;
    }
}

void calCRCR(const double PRICE[][4],
          const int count,
          const double MID[],
          const int N,
          double CR[])
{
    double max1[count];
    double max2[count];
    
    for (int i=0; i<count; i++)
    {
        max1[i] = fmax(0, PRICE[i][0] - MID[i]);
        max2[i] = fmax(0, MID[i] - PRICE[i][1]);
    }
    
    
    for (int i=0; i<count; i++)
    {
        double sum1 = calSum(max1, N, i);
        double sum2 = calSum(max2, N, i);
        CR[i] = sum1/sum2 * 100;
    }
}

void calCRMA(const double CR[],
          const int count,
          const int M,
          double MAN[])
{
    double ma[count];
    calMa(CR, count, M, ma);
    
    for (int i=0; i<count; i++)
    {
        MAN[i] = calRef(ma, count, i, M/2.5 + 1);
    }
}



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
                 double MA4[])
{
    double MID[count];
    calCRMID(PRICE, count, MID);
    calCRCR(PRICE, count, MID, N, CR);
    calCRMA(CR, count, M1, MA1);
    calCRMA(CR, count, M2, MA2);
    calCRMA(CR, count, M3, MA3);
    calCRMA(CR, count, M4, MA4);
}


#pragma mark - DMA 平均差

void calDMADIF(const double CLOSE[],
            const int count,
            const int N1,
            const int N2,
            double DIF[])
{
    double ma1[count];
    double ma2[count];
    calMa(CLOSE, count, N1, ma1);
    calMa(CLOSE, count, N2, ma2);
    for (int i=0; i<count; i++)
    {
        DIF[i] = ma1[i] - ma2[i];
    }
}


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
                  double DIFMA[])
{
    double CLOSE[count];
    for (int i=0; i<count; i++)
    {
        CLOSE[i] = PRICE[i][3];
    }
    calDMADIF(CLOSE, count, N1, N2, DIF);
    calMa(DIF, count, M, DIFMA);
}

#pragma mark - BRAR 情绪指标

void calBR(const double PRICE[][4],
          const int count,
          const int N,
          double BR[])
{
    double close[count];
    for (int i=0; i<count; i++)
    {
        close[i] = PRICE[i][3];
    }
    
    double max1[count];
    double max2[count];
    for (int i=0; i<count; i++)
    {
        max1[i] = fmax(0, PRICE[i][0] - calRef(close, count, i, 1));
        max2[i] = fmax(0, calRef(close, count, i, 1) - PRICE[i][1]);
    }
    
    for (int i=0; i<count; i++)
    {
        double sum1 = calSum(max1, N, i);
        double sum2 = calSum(max2, N, i);
        BR[i] = sum1 / sum2 * 100;
    }
}

void calAR(const double PRICE[][4],
          const int count,
          const int N,
          double AR[])
{
    double hoValue[count];
    double olValue[count];
    
    for (int i=0; i<count; i++)
    {
        hoValue[i] = PRICE[i][0] - PRICE[i][2];
        olValue[i] = PRICE[i][2] - PRICE[i][1];
    }
    
    for (int i=0; i<count; i++)
    {
        double sum1 = calSum(hoValue, N, i);
        double sum2 = calSum(olValue, N, i);
        AR[i] = sum1 / sum2 * 100;
    }
}

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
                   double AR[])
{
    calBR(PRICE, count, N, BR);
    calAR(PRICE, count, N, AR);
}

#pragma mark - ENV 轨道线

void calENVUPPER(const double ma[],
              const int count,
              const int M1,
              const int N,
              double UPPER[])
{
    
    for (int i=0; i<count; i++)
    {
        UPPER[i] = (1 + M1 / 100) * ma[i];
    }
}

void calENVLOWER(const double ma[],
              const int count,
              const int M2,
              const int N,
              double LOWER[])
{
    for (int i=0; i<count; i++)
    {
        LOWER[i] = (1 - M2 / 100) * ma[i];
    }
}

void calENVMID(const double UPPER[],
            const double LOWER[],
            const int count,
            double MID[])
{
    for (int i=0; i<count; i++)
    {
        MID[i] = (UPPER[i] + LOWER[i]) / 2;
    }
}


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
                  double MID[])
{
    double close[count];
    double closeMA[count];
    for (int i=0; i<count; i++)
    {
        close[i] = PRICE[i][3];
    }
    calMa(close, count, N, closeMA);
    calENVUPPER(closeMA, count, M1, N, UPPER);
    calENVLOWER(closeMA, count, M2, N, LOWER);
    calENVMID(UPPER, LOWER, count, MID);
}

#pragma mark EXPMA 指数平滑移动平均线

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
                    double EXP4[])
{
    double close[count];
    for (int i=0; i<count; i++)
    {
        close[i] = PRICE[i][3];
    }
    calEma(close, count, M1, EXP1);
    calEma(close, count, M2, EXP2);
    calEma(close, count, M3, EXP3);
    calEma(close, count, M4, EXP4);
}

#pragma mark DPO 区间震荡线


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
                  double MADPO[])
{
    double close[count];
    for (int i=0; i<count; i++)
    {
        close[i] = PRICE[i][3];
    }
    
    double maclose[count];
    calMa(close, count, N, maclose);
    for (int i=0; i<count; i++)
    {
        double ref = calRef(maclose, count, i, N/2+1);
        DPO[i] = close[i] - ref;
    }
    calMa(DPO, count, M, MADPO);
}

#pragma mark CDP 逆势操作

void calCDPPT(const double high[],
           const double low[],
           const int count,
           double pt[])
{
    for (int i=0; i<count; i++)
    {
        double highRef = calRef(high, count, i, 1);
        double lowRef = calRef(low, count, i, 1);
        pt[i] = highRef - lowRef;
    }
}

void calCDPCDP(const double high[],
            const double low[],
            const double close[],
            const int count,
            double cdp[])
{
    for (int i=0; i<count; i++)
    {
        double highRef = calRef(high, count, i, 1);
        double lowRef = calRef(low, count, i, 1);
        double closeRef = calRef(close, count, i, 1);
        cdp[i] = (highRef + lowRef + closeRef) / 3.f;
    }
}

void calCDPAH(const double cdp[],
           const double pt[],
           const int count,
           const int N,
           double ah[])
{
    double ma[count];
    for (int i=0; i<count; i++)
    {
        ma[i] = cdp[i] + pt[i];
    }
    
    calMa(ma, count, N, ah);
}

void calCDPAL(const double cdp[],
           const double pt[],
           const int count,
           const int N,
           double al[])
{
    double ma[count];
    for (int i=0; i<count; i++)
    {
        ma[i] = cdp[i] - pt[i];
    }
    
    calMa(ma, count, N, al);
}

void calCDPNH(const double cdp[],
           const double low[],
           const int count,
           const int N,
           double nh[])
{
    double ma[count];
    for (int i=0; i<count; i++)
    {
        ma[i] = 2.f * cdp[i] - low[i];
    }
    
    calMa(ma, count, N, nh);
}

void calCDPNL(const double cdp[],
           const double high[],
           const int count,
           const int N,
           double nl[])
{
    double ma[count];
    for (int i=0; i<count; i++)
    {
        ma[i] = 2.f * cdp[i] - high[i];
    }
    
    calMa(ma, count, N, nl);
}

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
                     double NL[])
{
    double high[count];
    double low[count];
    double close[count];
    for (int i=0; i<count; i++)
    {
        high[i] = PRICE[i][0];
        low[i] = PRICE[i][1];
        close[i] = PRICE[i][3];
    }
    
    double pt[count];
    calCDPPT(high, low, count, pt);
    calCDPCDP(high, low, close, count, CDP);
    calCDPAH(CDP, pt, count, N, AH);
    calCDPAL(CDP, pt, count, N, AL);
    calCDPNH(CDP, low, count, N, NH);
    calCDPNL(CDP, high, count, N, NL);
}

#pragma mark RSY 心理线

int calPSYCOUNT(const double ARGS1[],
          const double ARGS2[],
          const int i,
          const int N)
{
    int idx = N > i ? i : N;
    
    int sum = 0;
    for (int i=0; i<idx; i++)
    {
        if (ARGS1[i] > ARGS2[i])
        {
            sum++;
        }
    }
    
    return sum;
}

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
                     double PSYMA[])
{
    
    double close[count];
    for (int i=0; i<count; i++)
    {
        close[i] = PRICE[i][3];
    }
    double refclose[count];
    for (int i=0; i<count; i++)
    {
        refclose[i] = calRef(close, count, i, 1);
    }
    for (int i=0; i<count; i++)
    {
        int count = calPSYCOUNT(close, refclose, i, N);
        PSY[i] = count / N * 100;
    }
    calMa(PSY, count, M, PSYMA);
}

#pragma mark ROC 变动速率

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
                  double ROCMA[])
{
    double close[count];
    for (int i=0; i<count; i++)
    {
        close[i] = PRICE[i][3];
    }
    
    for (int i=0; i<count; i++)
    {
        double ref = calRef(close, count, i, N);
        ROC[i] = (close[i] - ref) / ref * 100.f;
    }
    
    calMa(ROC, count, M, ROCMA);
}

