# YKKLineIndicator

YKKLineIndicator是一个用C语言编写的K线指标库，其中包含了19种K线指标以及基础的指标函数。它可以让你在计算K线指标时，直接接入并赋以KLOC数据即可，免去了编写指标公式的繁琐步骤。


## 基础函数

**1、MA: 简单移动平均**

 MA(X,N):X的N日简单移动平均  
 算法(X1+X2+X3+...+Xn)/N，N支持变量

**2、 EMA: 指数移动平均**

EMA(X,N):X的N日指数移动平均  
算法:Y=(X*2+Y'*(N-1))/(N+1)，N支持变量

**3、 SMA: 移动平均**
SMA(X,N,M):X的N日移动平均,M为权重  
算法:Y=(X*M+Y'*(N-M))/N

**4、 HHV: 求周期内最高值**

HHV(X,N),求N周期内X最高值,N=0则从第一个有效值开始

**5、 LLV: 求周期内最低值**

LLV(X,N),求N周期内X最低值,N=0则从第一个有效值开始.

**6、 REF: 引用若干周期前的数据**

REF(X,A),引用A周期前的X值.A可以是变量.

**7、 STD: 估算标准差**

## K线指标

**1、BOLL (布林线)**

公式：  
BOLL:MA(CLOSE,M);  
UB:BOLL+2*STD(CLOSE,M);  
LB:BOLL-2*STD(CLOSE,M);


**2、MA（均线）**

公式：  
MA1:MA(CLOSE,M1);  
MA2:MA(CLOSE,M2);  
MA3:MA(CLOSE,M3);

**3、MACD（平滑异同平均）**

公式：  
DIF:EMA(CLOSE,SHORT)-EMA(CLOSE,LONG);  
DEA:EMA(DIF,MID);  
MACD:(DIF-DEA)*2,COLORSTICK;

**4、KDJ（随机指标）**

公式：  
RSV:=(CLOSE-LLV(LOW,N))/(HHV(HIGH,N)-LLV(LOW,N))*100;  
K:SMA(RSV,M1,1);  
D:SMA(K,M2,1);  
J:3*K-2*D;

**5、RSI（相对强弱指标）**

公式：  
LC:=REF(CLOSE,1);  
RSI1:SMA(MAX(CLOSE-LC,0),N1,1)/SMA(ABS(CLOSE-LC),N1,1)*100;  
RSI2:SMA(MAX(CLOSE-LC,0),N2,1)/SMA(ABS(CLOSE-LC),N2,1)*100;  
RSI3:SMA(MAX(CLOSE-LC,0),N3,1)/SMA(ABS(CLOSE-LC),N3,1)*100;

**6、BIAS（乖离率）**

公式：  
BIAS1 :(CLOSE-MA(CLOSE,N1))/MA(CLOSE,N1)*100;  
BIAS2 :(CLOSE-MA(CLOSE,N2))/MA(CLOSE,N2)*100;  
BIAS3 :(CLOSE-MA(CLOSE,N3))/MA(CLOSE,N3)*100;

**7、ATR（真实波幅）**

公式：  
MTR:MAX(MAX((HIGH-LOW),ABS(REF(CLOSE,1)-HIGH)),ABS(REF(CLOSE,1)-LOW));  ATR:MA(MTR,N);

**8、CCI（商品路径指标）**

公式：  
TYP:=(HIGH+LOW+CLOSE)/3;  CCI:(TYP-MA(TYP,N))/(0.015*AVEDEV(TYP,N));

**9、DMI（趋向指标）**

公式：  
MTR:=SUM(MAX(MAX(HIGH-LOW,ABS(HIGH-REF(CLOSE,1))),ABS(REF(CLOSE,1)-LOW)),N);  HD :=HIGH-REF(HIGH,1);  LD :=REF(LOW,1)-LOW;  DMP:=SUM(IF(HD>0&&HD>LD,HD,0),N);  DMM:=SUM(IF(LD>0&&LD>HD,LD,0),N);  PDI: DMP*100/MTR;  MDI: DMM*100/MTR;  ADX: MA(ABS(MDI-PDI)/(MDI+PDI)*100,M);  ADXR:(ADX+REF(ADX,M))/2;

**10、WR（威廉指标）**

公式：
WR1:100*(HHV(HIGH,N)-CLOSE)/(HHV(HIGH,N)-LLV(LOW,N));WR2:100*(HHV(HIGH,N1)-CLOSE)/(HHV(HIGH,N1)-LLV(LOW,N1));

**11、CR（带状能量线）**

公式：  
MID:=REF(HIGH+LOW,1)/2;  CR:SUM(MAX(0,HIGH-MID),N)/SUM(MAX(0,MID-LOW),N)*100;  MA1:REF(MA(CR,M1),M1/2.5+1);  MA2:REF(MA(CR,M2),M2/2.5+1);  MA3:REF(MA(CR,M3),M3/2.5+1);  MA4:REF(MA(CR,M4),M4/2.5+1);

**12、DMA（平均差）**

公式：  
DIF:MA(CLOSE,N1)-MA(CLOSE,N2);  DIFMA:MA(DIF,M);

**13、BRAR（情绪指标）**

公式：  
BR:SUM(MAX(0,HIGH-REF(CLOSE,1)),N)/SUM(MAX(0,REF(CLOSE,1)-LOW),N)*100;  AR:SUM(HIGH-OPEN,N)/SUM(OPEN-LOW,N)*100;  

**14、ENV（轨道线）**

公式：  
UPPER:(1+M1/100)*MA(CLOSE,N);  LOWER:(1-M2/100)*MA(CLOSE,N);  MID:(UPPER+LOWER)/2;

**15、EXPMA（指数平滑移动平均线）**

公式：  
EXP1:EMA(CLOSE,M1);  EXP2:EMA(CLOSE,M2);  
EXP3:EMA(CLOSE,M3);  EXP4:EMA(CLOSE,M4);  

**16、DPO（区间震荡线）**

公式：  
DPO:CLOSE-REF(MA(CLOSE,N),N/2+1);  MADPO:MA(DPO,M);

**17、CDP（逆势操作）**

公式：  
CH:=REF(H,1);  CL:=REF(L,1);  CC:=REF(C,1);  CDP:(CH+CL+CC)/3;  AH:2*CDP+CH-2*CL;  NH:CDP+CDP-CL;  NL:CDP+CDP-CH;  AL:2*CDP-2*CH+CL;

**18、PSY（心理线）**

公式：  
PSY:COUNT(CLOSE>REF(CLOSE,1),N)/N*100;  PSYMA:MA(PSY,M);

**19、ROC（变动率指标）**

公式：  
ROC:100*(CLOSE-REF(CLOSE,N))/REF(CLOSE,N);  MAROC:MA(ROC,M);

## 联系

如在使用指标库的过程中遇到问题，可随时发邮件至nethanhan@163.com与我取得联系。

