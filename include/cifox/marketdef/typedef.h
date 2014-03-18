#ifndef _INC_TYPEDEF_H
#define _INC_TYPEDEF_H

#pragma pack(1)
/////////////////////////////////////////////////////////////////////////////
/*
  数据项目的说明

1、所有数据项的定义值用 DWORD 表示
   |<- 31 - 22 ->|<- 21 - 16 ->|<- 15 ->|<- 14 - 12 ->|<- 11 - 0 ->|
     项目实例     自定义扩展    系统      数据类型      基本项目
  
   基本项目：  分段表示，每段表示一种类型，比如行情数据、财务数据等
   数据类型：  见定义 DTE_* 表示字符串、整数、浮点数等
   系统：      表示是用户自定义的，还是系统的。如果此位为 1 表示用户自定义 SF_USERDEFINE
   自定义扩展：基本项目不够用了，使用这个扩展，共 6 位。可以做 32 倍的扩展。
   项目实例：  用于计算公式内部，多个输出的ID分配。包括两部分：实例和高位标志 SF_INST_MASK SF_MARK_MASK

2、关于周期描述的一些约定
	1）基本周期分为四类：实时、成交明细、分时、K线（包括分钟K线和日K线等）
	2）所有周期：包括上述所有的
	3）从实时到K线是一个数据信息量逐步减少的过程。则取决于转码的过程，有些数据只在实时数据下面有就是为了减少数据量。

3、基本项目的分类 （共4095个）
	1）行情数据：分段：1-300（SM_HQ_BEGIN - SM_HQ_END）下面的注释会简单的说明数据项目是哪个周期的，但是详细的确切的
	   定义在 文件 /cifox/datapool/poolstruct.cpp 和 /cifox/datapool/poolstruct_l2.cpp 里面定义每个市场每个周期的数据结构
	   行情数据不要扩展，有些定义可以复用（比如只是针对一个市场的数据定义）。
    2）财务数据： 分段：301-2101（SM_FD_BEGIN - SM_FD_END）这里定义的并不是全部的数据项目，完整的数据项目见文件 formula.ini
	3）委托数据： 分段：2102-2202（SM_WT_BEGIN - SM_WT_END）委托用户端使用的一些数据项目
	4）内部函数： 分段：2203-2503（SM_FUNC_BEGIN - SM_FUNC_END）虚拟机使用的内部函数。完整的公式见文件 formula.ini
	5）外部函数： 分段：2504-3504（SM_USERS_BEGIN - SM_USERS_END）通过公式编辑器编写的公式。见文件 formula.ini
	6）资讯数据： 分段：3505-3605（SM_TEXT_BEGIN - SM_TEXT_END）和资讯相关的数据项目，完整的定义在文件 formula.ini
	7）未分配的： 分段：3606-4095

4、本文件的使用
	1）这个文件可以作为数据项目的说明文档。
	2）禁止构件使用这个文件。包括使用这个文件定义的宏。
*/
#define	SF_INST_MASK		0x1FC00000			//项目实例掩码
#define SF_EXT_MASK			0x003F0000			//自定义扩展
#define SF_USERDEFINE		0x00008000			//用户自定义
#define	SF_ITEM_MASK		0xFFFF8FFF			//数据项目掩码
#define	SF_TYPE_MASK		0x00007000			//数据类型掩码

//计算项目高位标志
#define SF_MARK_MASK		0xE0000000
#define SF_MARK_SIGN		0x80000000			//输出为标志，如信息地雷等
#define SF_MARK_SELECT		0x40000000			//选股的输出标志
#define SF_MARK_TEMP		0x20000000			//临时数据项目，比如从主站返回的计算项目

//
#define	SF_INST_BEGIN		0x00400000			//项目实例起始值lsb

#define	SF_INST_POS			22
#define SF_MAX_EXT			0x3F

//#define SF_BASEID(x)		((DWORD)(x) & ~(SF_INST_MASK|SF_MARK_MASK))
#define SF_BASEID(x)		((DWORD)(x) & ~((SF_INST_MASK|SF_MARK_MASK)&~SF_MARK_SELECT))
#define SF_DRAWID(x)		((DWORD)(x) | SF_INST_MASK)

#define SF_ISUSERDEFINE(x)	((DWORD)(x) & SF_USERDEFINE)
#define SF_ISSIGN(x)		((DWORD)(x) & SF_MARK_SIGN)
#define SF_ISEXT(x)			((DWORD)(x) & SF_EXT_MASK)

////////////////////////////////////////////////////////////////////////////////////////////
//最高位表示是否计算项目
//数据类型
#define DTE_CHAR		0x1000			//字符串（长度小于等于 8）
#define DTE_STRING		0x2000			//字符串（长度大于 8）
#define DTE_LONG		0x3000			//整数
#define DTE_TIMELONG	0x4000			//时间和TLLong数据结构的组合体，不再是时间。
#define DTE_DOUBLE		0x5000			//浮点数
#define DTE_MEMO		0x6000			//不定长的备注型数据
#define DTE_HXLONG		0x7000			//结构化的整数

#define SF_ITEM(x)		((DWORD)(x) & SF_ITEM_MASK)	//取ID
#define SF_TYPE(x)		((DWORD)(x) & SF_TYPE_MASK)	//取数据类型
#define SF_INST(x)		((DWORD)(x) & SF_INST_MASK)	//取数据项目实例

//空值
#ifndef SS_MINTIME
#define SS_MINTIME		100000000		//最小时间
#endif
#define PI				3.141592653589793238462643383279

#define GET_MAX_COUNT		10000		//取数据的最大个数
#define DTE_CHAR_NULL		_T("NUL")		//字符串空值
#define DTE_LONG_NULL		TSH_LONG_MIN		//整数空值
#define DTE_DATETIME_NULL	SS_MINTIME		//日期时间空值
//#define DTE_DOUBLE_NULL		DBL_MIN			//符点数空值
#define DTE_COLOR_NULL		0x7fffffff		//颜色COLORREF

#define IsColorNull(x)		((x) == DTE_COLOR_NULL)
#define SetColorNull(x)		(x) = DTE_COLOR_NULL

///////////////////////////////////////////////////////////////////////////
//股票行情数据项定义
//所有价格、成交金额的单位是‘元’。
//所有的成交量的单位是‘股’。
//
#define	SM_HQ_BEGIN			0						//行情数据项定义值的开始

#define SM_HQ_TIME			(SM_HQ_BEGIN + 1)		//根据周期，不同格式

#define SM_HQ_MARKETTYPE	(SM_HQ_BEGIN + 2)		//市场类别 适用周期：实时
#define SM_HQ_CODETYPE		(SM_HQ_BEGIN + 3)		//证券类型 适用周期：实时
#define SM_HQ_CODECODE		(SM_HQ_BEGIN + 4)		//证券代码 适用周期：实时
#define SM_HQ_CODE			(SM_HQ_BEGIN + 5)		//证券类型+证券代码 适用周期：实时
#define SM_HQ_PREVCLOSE		(SM_HQ_BEGIN + 6)		//前一日的收盘价  适用周期：特殊周期
#define SM_HQ_OPENPRICE		(SM_HQ_BEGIN + 7)		//开盘价 适用周期：K线
#define SM_HQ_HIGHPRICE		(SM_HQ_BEGIN + 8)		//最高价 适用周期：K线
#define SM_HQ_LOWPRICE		(SM_HQ_BEGIN + 9)		//最低价 适用周期：K线
#define SM_HQ_NEWPRICE		(SM_HQ_BEGIN + 10)		//最新价 适用周期：实时
#define SM_HQ_CLOSEPRICE	(SM_HQ_BEGIN + 11)		//收盘价 适用周期：K线

#define SM_HQ_VOLCLASS		(SM_HQ_BEGIN + 12)		//成交量分类：卖盘3、卖盘2、卖盘1、对倒、买盘1、买盘2、买盘3。
													//指明最近一笔成交的分类情况

#define SM_HQ_VOLUME		(SM_HQ_BEGIN + 13)		//成交量
#define SM_HQ_OUTVOL		(SM_HQ_BEGIN + 14)		//外盘成交量
#define SM_HQ_INVOL			(SM_HQ_BEGIN + 15)		//内盘成交量
#define SM_HQ_ZEROVOL		(SM_HQ_BEGIN + 16)		//对倒成交量

#define SM_HQ_OPENVOL		(SM_HQ_BEGIN + 17)		//开盘成交量 适用周期：K线
#define SM_HQ_VOLAMOUNT		(SM_HQ_BEGIN + 18)		//成交次数

#define SM_HQ_MONEY			(SM_HQ_BEGIN + 19)		//成交金额

#define SM_HQ_BUYPRICE		(SM_HQ_BEGIN + 20)		//本次成交时的委托买入价
#define SM_HQ_SELLPRICE		(SM_HQ_BEGIN + 21)		//本次成交时的委托卖出价

#define SM_HQ_BUYCOUNT		(SM_HQ_BEGIN + 22)		//委托买入量
													//对于个股：三档买入数量之和
													//对于指数：本类指数所有股票的买入数量之和
#define SM_HQ_SELLCOUNT		(SM_HQ_BEGIN + 23)		//委托卖出量
													//对于个股：三档卖出数量之和
													//对于指数：本类指数所有股票的卖出数量之和
//仅对个股有效－开始 （ 适用周期：实时）
#define SM_HQ_BUYPRICE1		(SM_HQ_BEGIN + 24)		//委托买入价格一
#define SM_HQ_BUYCOUNT1		(SM_HQ_BEGIN + 25)		//委托买入数量一
#define SM_HQ_BUYPRICE2		(SM_HQ_BEGIN + 26)		//委托买入价格二
#define SM_HQ_BUYCOUNT2		(SM_HQ_BEGIN + 27)		//委托买入数量二
#define SM_HQ_BUYPRICE3		(SM_HQ_BEGIN + 28)		//委托买入价格三
#define SM_HQ_BUYCOUNT3		(SM_HQ_BEGIN + 29)		//委托买入数量三
#define SM_HQ_SELLPRICE1	(SM_HQ_BEGIN + 30)		//委托卖出价格一
#define SM_HQ_SELLCOUNT1	(SM_HQ_BEGIN + 31)		//委托卖出数量一
#define SM_HQ_SELLPRICE2	(SM_HQ_BEGIN + 32)		//委托卖出价格二
#define SM_HQ_SELLCOUNT2	(SM_HQ_BEGIN + 33)		//委托卖出数量二
#define SM_HQ_SELLPRICE3	(SM_HQ_BEGIN + 34)		//委托卖出价格三
#define SM_HQ_SELLCOUNT3	(SM_HQ_BEGIN + 35)		//委托卖出数量三
//仅对个股有效－结束

//仅对指数有效－开始 （ 适用周期：实时）
#define SM_HQ_INDEXTYPE		(SM_HQ_BEGIN + 36)		//指数种类：0-综合指数 1-A股 2-B股
#define SM_HQ_TOTALSTOCK	(SM_HQ_BEGIN + 37)		//本类股票总数
#define SM_HQ_RISECOUNT		(SM_HQ_BEGIN + 38)		//上涨家数
#define SM_HQ_FALLCOUNT		(SM_HQ_BEGIN + 39)		//下跌家数
#define SM_HQ_INDEXLEAD		(SM_HQ_BEGIN + 40)		//领先指标
#define SM_HQ_RISETREND		(SM_HQ_BEGIN + 41)		//上涨趋势
#define SM_HQ_FALLTREND		(SM_HQ_BEGIN + 42)		//下跌趋势
#define SM_HQ_NEWMONEY		(SM_HQ_BEGIN + 43)		//最近一笔成交金额(现额)
//仅对指数有效－结束

#define SM_HQ_ZQMC_BIG5		(SM_HQ_BEGIN + 44)		//证券名称(繁体中文)
#define SM_HQ_5DAYVOL		(SM_HQ_BEGIN + 45)		//五日总成交量  适用周期：实时
#define SM_HQ_ZQMC_ENG		(SM_HQ_BEGIN + 46)		//证券名称(英文)

#define SM_HQ_ZQMC_UNI		(SM_HQ_BEGIN + 47)		//证券名称(Unicode)
#define SM_HQ_5PERRISE		(SM_HQ_BEGIN + 48)		//五分钟涨跌幅  适用周期：实时
#define SM_HQ_NEWVOL		(SM_HQ_BEGIN + 49)		//最近一笔成交量(现手) 适用周期：实时 成交明细

#define SM_HQ_PERWAVE		(SM_HQ_BEGIN + 50)		//震幅 没有使用过，可以复用。yhm
#define SM_HQ_PERVOL		(SM_HQ_BEGIN + 51)		//量比 没有使用过，可以复用。yhm
#define SM_HQ_COMM			(SM_HQ_BEGIN + 52)		//委差 没有使用过，可以复用。yhm
#define SM_HQ_PERCOMM		(SM_HQ_BEGIN + 53)		//委比 没有使用过，可以复用。yhm
#define SM_HQ_AVERAGE		(SM_HQ_BEGIN + 54)		//均价 没有使用过，可以复用。yhm

#define SM_HQ_ZQMC			(SM_HQ_BEGIN + 55)		//证券名称(简体中文) 适用周期：实时
#define SM_HQ_SERIAL		(SM_HQ_BEGIN + 56)		//序号 适用周期：实时
#define SM_HQ_VALIDBEGIN	(SM_HQ_BEGIN + 57)		//有效时间开始 适用周期：实时
#define SM_HQ_VALIDEND		(SM_HQ_BEGIN + 58)		//有效时间结束 适用周期：实时
#define SM_HQ_ZQMC_DISPLAY	(SM_HQ_BEGIN + 59)		//证券名称(长名称) 适用周期：实时

//仅对期货有效－开始 （适用周期：实时）（reuse begin）
#define SM_HQ_VARIETY		(SM_HQ_CODE)			//合约号 = 代码
#define SM_HQ_TRANNO		(SM_HQ_BEGIN + 60)		//
#define SM_HQ_ID			(SM_HQ_BEGIN + 61)		//
#define SM_HQ_ITEMNO		(SM_HQ_BEGIN + 62)		//
#define SM_HQ_EXCH			(SM_HQ_BEGIN + 63)		//交易所
#define SM_HQ_STATUS		(SM_HQ_BEGIN + 64)		//状态
#define SM_HQ_INTEREST		(SM_HQ_BEGIN + 65)		//持仓量
#define SM_HQ_SETTLE		(SM_HQ_BEGIN + 66)		//结算价(昨结算)
#define SM_HQ_HISHIGH		(SM_HQ_BEGIN + 67)		//史最高
#define SM_HQ_HISLOW		(SM_HQ_BEGIN + 68)		//史最低
#define SM_HQ_UPPERLIM		(SM_HQ_BEGIN + 69)		//涨停板
#define SM_HQ_LOWERLIM		(SM_HQ_BEGIN + 70)		//跌停版
#define	SM_HQ_NOWINTEREST	(SM_HQ_BEGIN + 71)		//增仓
#define SM_HQ_TSETTLE		(SM_HQ_BEGIN + 72)		//今结算价
#define SM_HQ_PREINTEREST	(SM_HQ_BEGIN + 73)		//昨持仓量
#define SM_HQ_PREDELTA		(SM_HQ_BEGIN + 74)		//昨虚实度
#define SM_HQ_CURRDELTA		(SM_HQ_BEGIN + 75)		//今虚实度
//仅对期货有效－结束 （reuse end）

//仅对外汇有效-开始 （适用周期：实时）
#define SM_FX_PK			(SM_HQ_CODE)			//代码 + 类型
#define SM_FX_NAME			(SM_HQ_ZQMC)			//中文名称
#define SM_FX_TIME			(SM_HQ_TIME)			//日期 + 时间 (扫描变化用，传给接收端，在文本头中只传当前时间)
#define	SM_FX_YCLOSE		(SM_HQ_PREVCLOSE)		//昨收
#define	SM_FX_OPEN			(SM_HQ_OPENPRICE)		//开盘
#define	SM_FX_HIGH			(SM_HQ_HIGHPRICE)		//最高
#define SM_FX_LOW			(SM_HQ_LOWPRICE)		//最低
#define	SM_FX_LAST			(SM_HQ_NEWPRICE)		//最新
#define	SM_FX_CLOSE			(SM_HQ_CLOSEPRICE)		//收盘价

#define SM_FX_BUYPRICE		(SM_HQ_BUYPRICE)		//委买价
#define SM_FX_SELLPRICE		(SM_HQ_SELLPRICE)		//委卖价
#define SM_FX_BUYPRICE1		(SM_HQ_BUYPRICE1)
#define SM_FX_BUYPRICE2		(SM_HQ_BUYPRICE2)
#define SM_FX_BUYPRICE3		(SM_HQ_BUYPRICE3)
#define SM_FX_SELLPRICE1	(SM_HQ_SELLPRICE1)
#define SM_FX_SELLPRICE2	(SM_HQ_SELLPRICE2)
#define SM_FX_SELLPRICE3	(SM_HQ_SELLPRICE3)
#define SM_FX_VOLAMOUNT		(SM_HQ_VOLAMOUNT)		//成交次数
#define SM_FX_ZCVL			(SM_HQ_PERCOMM)			//波动率
//仅对外汇有效-结束

//仅对免费版有效－开始  委托买卖最大挂单量
#define SM_HQ_FREEBIGORDERTRADE	(SM_HQ_BEGIN + 76)		//委托买卖最大档的交易方向
#define SM_HQ_FREEBIGORDERGRADE	(SM_HQ_BEGIN + 77)		//委托买卖最大档的档位
#define SM_HQ_FREEBIGORDERPRICE	(SM_HQ_BEGIN + 78)		//委托买卖最大档的价格
#define SM_HQ_FREEBIGORDERVALUE	(SM_HQ_BEGIN + 79)		//委托买卖最大档的量
//仅对免费版有效-结束

//仅对国债有效－开始 （适用周期：实时）
#define SM_HQ_YJLX			(SM_HQ_BEGIN + 80)		//应计利息
//仅对国债有效－结束
#define SM_HQ_SYL2			(SM_HQ_BEGIN + 81)		//深交所的LOF动态净值 适用周期：实时
#define SM_HQ_TIME2			(SM_HQ_BEGIN + 82)		//同一个文件里面的第二个时间值，可能有多种含义 适用周期：实时

#define SM_HQ_PRENAME		(SM_HQ_BEGIN + 83)		//证券简称前缀 适用周期：实时

#define SM_HQ_INDUSTRY		(SM_HQ_BEGIN + 84)		//所属行业 适用周期：实时

//#define SM_NO_USE			(SM_HQ_BEGIN + 85)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 86)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 87)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 88)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 89)		//

#define SM_HQ_LTSZ			(SM_HQ_BEGIN + 90)		//流通市值－交易所发布 适用周期：实时
#define SM_HQ_SYL			(SM_HQ_BEGIN + 91)		//市盈率－交易所发布 适用周期：实时
#define SM_HQ_ZSZ			(SM_HQ_BEGIN + 92)		//总市值－交易所发布 适用周期：实时
#define SM_HQ_JYDW			(SM_HQ_BEGIN + 93)		//交易单位 适用周期：实时
#define SM_HQ_HBDW			(SM_HQ_BEGIN + 94)		//货币单位 适用周期：实时
#define SM_HQ_YEARHIGH		(SM_HQ_BEGIN + 95)		//52周最高 适用周期：实时
#define SM_HQ_YEARLOW		(SM_HQ_BEGIN + 96)		//52周最低 适用周期：实时

#define SM_HQ_TEXTNUM		(SM_HQ_BEGIN + 97)		//实时资讯个数 适用周期：实时

#define SM_HQ_YVALUE		(SM_HQ_BEGIN + 98)		//光标处Y坐标的数值 不用
#define SM_HQ_YSTRVALUE		(SM_HQ_BEGIN + 99)		//光标处Y坐标数值的字符串 不用

//#define SM_NO_USE			(SM_HQ_BEGIN + 100)		//

#define SM_TRADE_RESULT		(SM_HQ_BEGIN + 101)		//交易系统测试数据项
//
//仅对个股有效－开始  - 扩充买卖盘 （适用周期：实时）
#define SM_HQ_BUYPRICE6		(SM_HQ_BEGIN + 102)		//委托买入价格六
#define SM_HQ_BUYCOUNT6		(SM_HQ_BEGIN + 103)		//委托买入数量六
#define SM_HQ_SELLPRICE6	(SM_HQ_BEGIN + 104)		//委托卖出价格六
#define SM_HQ_SELLCOUNT6	(SM_HQ_BEGIN + 105)		//委托卖出数量六

#define SM_HQ_BUYPRICE7		(SM_HQ_BEGIN + 106)		//委托买入价格七
#define SM_HQ_BUYCOUNT7		(SM_HQ_BEGIN + 107)		//委托买入数量七
#define SM_HQ_SELLPRICE7	(SM_HQ_BEGIN + 108)		//委托卖出价格七
#define SM_HQ_SELLCOUNT7	(SM_HQ_BEGIN + 109)		//委托卖出数量七

#define SM_HQ_BUYPRICE8		(SM_HQ_BEGIN + 110)		//委托买入价格八
#define SM_HQ_BUYCOUNT8		(SM_HQ_BEGIN + 111)		//委托买入数量八
#define SM_HQ_SELLPRICE8	(SM_HQ_BEGIN + 112)		//委托卖出价格八
#define SM_HQ_SELLCOUNT8	(SM_HQ_BEGIN + 113)		//委托卖出数量八

#define SM_HQ_BUYPRICE9		(SM_HQ_BEGIN + 114)		//委托买入价格九
#define SM_HQ_BUYCOUNT9		(SM_HQ_BEGIN + 115)		//委托买入数量九
#define SM_HQ_SELLPRICE9	(SM_HQ_BEGIN + 116)		//委托卖出价格九
#define SM_HQ_SELLCOUNT9	(SM_HQ_BEGIN + 117)		//委托卖出数量九
		
#define SM_HQ_BUYPRICE10	(SM_HQ_BEGIN + 118)		//委托买入价格十
#define SM_HQ_BUYCOUNT10	(SM_HQ_BEGIN + 119)		//委托买入数量十
#define SM_HQ_SELLPRICE10	(SM_HQ_BEGIN + 120)		//委托卖出价格十
#define SM_HQ_SELLCOUNT10	(SM_HQ_BEGIN + 121)		//委托卖出数量十

#define SM_HQ_AVGBUYPRICE	(SM_HQ_BEGIN + 122)		//平均委托买入价格
#define SM_HQ_ALLBUYCOUNT	(SM_HQ_BEGIN + 123)		//所有委托买入数量的和
#define SM_HQ_AVGSELLPRICE	(SM_HQ_BEGIN + 124)		//平均委托卖出价格
#define SM_HQ_ALLSELLCOUNT	(SM_HQ_BEGIN + 125)		//所有委托卖出数量的和
//
//#define SM_NO_USE			(SM_HQ_BEGIN + 126)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 127)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 128)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 129)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 130)		//

#define SM_HQ_BID_Q6		(SM_HQ_BEGIN + 131)		//委托买入券商数六
#define SM_HQ_BID_Q7		(SM_HQ_BEGIN + 132)		//委托买入券商数七
#define SM_HQ_BID_Q8		(SM_HQ_BEGIN + 133)		//委托买入券商数八
#define SM_HQ_BID_Q9		(SM_HQ_BEGIN + 134)		//委托买入券商数九
#define SM_HQ_BID_Q10		(SM_HQ_BEGIN + 135)		//委托买入券商数十
#define SM_HQ_ASK_Q6		(SM_HQ_BEGIN + 136)		//委托卖出券商数六
#define SM_HQ_ASK_Q7		(SM_HQ_BEGIN + 137)		//委托卖出券商数七
#define SM_HQ_ASK_Q8		(SM_HQ_BEGIN + 138)		//委托卖出券商数八
#define SM_HQ_ASK_Q9		(SM_HQ_BEGIN + 139)		//委托卖出券商数九
#define SM_HQ_ASK_Q10		(SM_HQ_BEGIN + 140)		//委托卖出券商数十
//
//仅对个股期权有效
#define SM_HQ_AuctionPrice			(SM_HQ_BEGIN + 141)		//波动性中断参考价格
#define SM_HQ_AuctionQty			(SM_HQ_BEGIN + 142)		//波动性中断集合竞价虚拟匹配量
#define SM_HQ_ContractID			(SM_HQ_BEGIN + 143)		//合约代码
#define SM_HQ_UnderlyingID			(SM_HQ_BEGIN + 144)		//标的证券代码
#define SM_HQ_UnderlyingSymbol		(SM_HQ_BEGIN + 145)		//基础证券证券名称
#define SM_HQ_UnderlyingType		(SM_HQ_BEGIN + 146)		//标的证券类型
#define SM_HQ_OptionType			(SM_HQ_BEGIN + 147)		//欧式美式
#define SM_HQ_CallOrPut				(SM_HQ_BEGIN + 148)		//认购认沽
#define SM_HQ_Unit					(SM_HQ_BEGIN + 149)		//合约单位
//个股期权-结束

#define SM_HQ_BUYPRICE4		(SM_HQ_BEGIN + 150)		//委托买入价格四
#define SM_HQ_BUYCOUNT4		(SM_HQ_BEGIN + 151)		//委托买入数量四
#define SM_HQ_SELLPRICE4	(SM_HQ_BEGIN + 152)		//委托卖出价格四
#define SM_HQ_SELLCOUNT4	(SM_HQ_BEGIN + 153)		//委托卖出数量四
#define SM_HQ_BUYPRICE5		(SM_HQ_BEGIN + 154)		//委托买入价格五
#define SM_HQ_BUYCOUNT5		(SM_HQ_BEGIN + 155)		//委托买入数量五
#define SM_HQ_SELLPRICE5	(SM_HQ_BEGIN + 156)		//委托卖出价格五
#define SM_HQ_SELLCOUNT5	(SM_HQ_BEGIN + 157)		//委托卖出数量五
//仅对个股有效－结束

//#define SM_NO_USE			(SM_HQ_BEGIN + 158)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 159)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 160)		//

//仅对港股有效－开始 （适用周期：实时）（reuse begin）
//上证L2数据项复用(SM_HQ_HKBQ_BUYROW1 -- SM_HQ_HIGHER_SPREAD)，参看poolstruct_l2.cpp
#define SM_HQ_HKBQ_BUYROW1	(SM_HQ_BEGIN + 161)		//买入券商一
#define SM_HQ_HKBQ_BUYROW2	(SM_HQ_BEGIN + 162)		//
#define SM_HQ_HKBQ_BUYROW3	(SM_HQ_BEGIN + 163)		//
#define SM_HQ_HKBQ_BUYROW4	(SM_HQ_BEGIN + 164)		//
#define SM_HQ_HKBQ_BUYROW5	(SM_HQ_BEGIN + 165)		//
#define SM_HQ_HKBQ_BUYROW6	(SM_HQ_BEGIN + 166)		//
#define SM_HQ_HKBQ_BUYROW7	(SM_HQ_BEGIN + 167)		//
#define SM_HQ_HKBQ_BUYROW8	(SM_HQ_BEGIN + 168)		//
#define SM_HQ_HKBQ_BUYROW9	(SM_HQ_BEGIN + 169)		//
#define SM_HQ_HKBQ_BUYROW10	(SM_HQ_BEGIN + 170)		//
#define SM_HQ_HKBQ_SELLROW1	(SM_HQ_BEGIN + 171)		//卖出券商一
#define SM_HQ_HKBQ_SELLROW2	(SM_HQ_BEGIN + 172)		//
#define SM_HQ_HKBQ_SELLROW3	(SM_HQ_BEGIN + 173)		//
#define SM_HQ_HKBQ_SELLROW4	(SM_HQ_BEGIN + 174)		//
#define SM_HQ_HKBQ_SELLROW5	(SM_HQ_BEGIN + 175)		//
#define SM_HQ_HKBQ_SELLROW6	(SM_HQ_BEGIN + 176)		//
#define SM_HQ_HKBQ_SELLROW7	(SM_HQ_BEGIN + 177)		//
#define SM_HQ_HKBQ_SELLROW8	(SM_HQ_BEGIN + 178)		//
#define SM_HQ_HKBQ_SELLROW9	(SM_HQ_BEGIN + 179)		//
#define SM_HQ_HKBQ_SELLROW10 (SM_HQ_BEGIN + 180)	//
#define SM_HQ_HKBQ_BEGIN	SM_HQ_HKBQ_BUYROW1
#define SM_HQ_HKBQ_END		SM_HQ_HKBQ_SELLROW10
//
#define SM_HQ_BID_Q1		(SM_HQ_BEGIN + 181)		//委托买入券商数一
#define SM_HQ_BID_Q2		(SM_HQ_BEGIN + 182)		//委托买入券商数二
#define SM_HQ_BID_Q3		(SM_HQ_BEGIN + 183)		//委托买入券商数三
#define SM_HQ_BID_Q4		(SM_HQ_BEGIN + 184)		//委托买入券商数四
#define SM_HQ_BID_Q5		(SM_HQ_BEGIN + 185)		//委托买入券商数五
#define SM_HQ_ASK_Q1		(SM_HQ_BEGIN + 186)		//委托卖出券商数一
#define SM_HQ_ASK_Q2		(SM_HQ_BEGIN + 187)		//委托卖出券商数二
#define SM_HQ_ASK_Q3		(SM_HQ_BEGIN + 188)		//委托卖出券商数三
#define SM_HQ_ASK_Q4		(SM_HQ_BEGIN + 189)		//委托卖出券商数四
#define SM_HQ_ASK_Q5		(SM_HQ_BEGIN + 190)		//委托卖出券商数五
//
#define SM_HQ_LOWER_SPREAD	(SM_HQ_BEGIN + 191)		//差价
#define SM_HQ_HIGHER_SPREAD	(SM_HQ_BEGIN + 192)		//差价
#define SM_HQ_PREMINUM		(SM_HQ_BEGIN + 193)		//溢价
#define SM_HQ_GEARING		(SM_HQ_BEGIN + 194)		//杠杆比率
#define SM_HQ_EXERC_PRICE	(SM_HQ_BEGIN + 195)		//行使价
#define SM_HQ_CONV_RATIO	(SM_HQ_BEGIN + 196)		//换购比率
#define SM_HQ_EXPIRY_DATE	(SM_HQ_BEGIN + 197)		//到期日
//仅对港股有效－结束 （reuse end）

//#define SM_NO_USE			(SM_HQ_BEGIN + 198)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 199)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 200)		//

/////////////////////////////////////////////////////////////////////////////////
//行情定义段扩充到300了
//Level2大单数据（适用周期：所有）
#define SM_HQ_BIGBUYCOUNT1		(SM_HQ_BEGIN + 201)		//主动买入特大单量
#define SM_HQ_BIGSELLCOUNT1		(SM_HQ_BEGIN + 202)		//主动卖出特大单量
#define SM_HQ_BIGBUYCOUNT2		(SM_HQ_BEGIN + 203)		//主动买入大单量
#define SM_HQ_BIGSELLCOUNT2		(SM_HQ_BEGIN + 204)		//主动卖出大单量
#define SM_HQ_BIGBUYCOUNT3		(SM_HQ_BEGIN + 205)		//主动买入中单量
#define SM_HQ_BIGSELLCOUNT3		(SM_HQ_BEGIN + 206)		//主动卖出中单量
#define SM_HQ_WAITBUYCOUNT1		(SM_HQ_BEGIN + 207)		//被动买入特大单量
#define SM_HQ_WAITSELLCOUNT1	(SM_HQ_BEGIN + 208)		//被动卖出特大单量
#define SM_HQ_WAITBUYCOUNT2		(SM_HQ_BEGIN + 209)		//被动买入大单量
#define SM_HQ_WAITSELLCOUNT2	(SM_HQ_BEGIN + 210)		//被动卖出大单量
#define SM_HQ_WAITBUYCOUNT3		(SM_HQ_BEGIN + 211)		//被动买入中单量
#define SM_HQ_WAITSELLCOUNT3	(SM_HQ_BEGIN + 212)		//被动卖出中单量
#define SM_HQ_BIGBUYCOUNT4		(SM_HQ_BEGIN + 213)		//主动买入小单量
#define SM_HQ_BIGSELLCOUNT4		(SM_HQ_BEGIN + 214)		//主动卖出小单量
//
#define SM_HQ_BIGBUYTICK1		(SM_HQ_BEGIN + 215)		//主动买入特大单笔数
#define SM_HQ_BIGSELLTICK1		(SM_HQ_BEGIN + 216)		//主动卖出特大单笔数
#define SM_HQ_BIGBUYTICK2		(SM_HQ_BEGIN + 217)		//主动买入大单笔数
#define SM_HQ_BIGSELLTICK2		(SM_HQ_BEGIN + 218)		//主动卖出大单笔数
#define SM_HQ_WAITBUYTICK1		(SM_HQ_BEGIN + 219)		//被动买入特大单笔数
#define SM_HQ_WAITSELLTICK1		(SM_HQ_BEGIN + 220)		//被动卖出特大单笔数
#define SM_HQ_WAITBUYTICK2		(SM_HQ_BEGIN + 221)		//被动买入大单笔数
#define SM_HQ_WAITSELLTICK2		(SM_HQ_BEGIN + 222)		//被动卖出大单笔数
#define SM_HQ_BIGBUYMONEY1		(SM_HQ_BEGIN + 223)		//主动买入特大单金额
#define SM_HQ_BIGSELLMONEY1		(SM_HQ_BEGIN + 224)		//主动卖出特大单金额
#define SM_HQ_BIGBUYMONEY2		(SM_HQ_BEGIN + 225)		//主动买入大单金额
#define SM_HQ_BIGSELLMONEY2		(SM_HQ_BEGIN + 226)		//主动卖出大单金额
#define SM_HQ_WAITBUYMONEY1		(SM_HQ_BEGIN + 227)		//被动买入特大单金额
#define SM_HQ_WAITSELLMONEY1	(SM_HQ_BEGIN + 228)		//被动卖出特大单金额
#define SM_HQ_WAITBUYMONEY2		(SM_HQ_BEGIN + 229)		//被动买入大单金额
#define SM_HQ_WAITSELLMONEY2	(SM_HQ_BEGIN + 230)		//被动卖出大单金额
#define	SM_HQ_BUYTICK			(SM_HQ_BEGIN + 231)		//买入单数量
#define	SM_HQ_SELLTICK			(SM_HQ_BEGIN + 232)		//卖出单数量

#define	SM_HQ_ZJLR				(SM_HQ_BEGIN + 233)		//资金流入
#define	SM_HQ_ZJLC				(SM_HQ_BEGIN + 234)		//资金流出

#define SM_HQ_DDE_UP			(SM_HQ_BEGIN + 235)		//大单净量正
#define SM_HQ_DDE_DOWN			(SM_HQ_BEGIN + 236)		//大单净量负

#define SM_HQ_BIGBUYMONEY4		(SM_HQ_BEGIN + 237)		//主动买入小单金额
#define SM_HQ_BIGSELLMONEY4		(SM_HQ_BEGIN + 238)		//主动卖出小单金额

#define SM_HQ_TICKAMOUNT		(SM_HQ_BEGIN + 239)		//成交笔数

#define	SM_HQ_PREYIELD			(SM_HQ_BEGIN + 240)		//昨日收盘收益率
#define	SM_HQ_PREAVGYIELD		(SM_HQ_BEGIN + 241)		//昨日加权平均收益率
#define	SM_HQ_OPENYIELD			(SM_HQ_BEGIN + 242)		//开盘收益率
#define	SM_HQ_HIGHYIELD			(SM_HQ_BEGIN + 243)		//最高收益率
#define	SM_HQ_LOWYIELD			(SM_HQ_BEGIN + 244)		//最低收益率
#define	SM_HQ_LASTYIELD			(SM_HQ_BEGIN + 245)		//最新收益率
#define	SM_HQ_AVGYIELD			(SM_HQ_BEGIN + 246)		//当日加权平均收益率

#define SM_HQ_BUYMONEY5			(SM_HQ_BEGIN + 250)		//委托买入前五档金额
#define SM_HQ_SELLMONEY5		(SM_HQ_BEGIN + 251)		//委托卖出前五档金额
#define SM_HQ_BUYMONEY10		(SM_HQ_BEGIN + 252)		//委托买入前十档金额
#define SM_HQ_SELLMONEY10		(SM_HQ_BEGIN + 253)		//委托卖出前十档金额

//#define SM_NO_USE			(SM_HQ_BEGIN + 254)		//

#define SM_HQ_BIGBUYTICK3		(SM_HQ_BEGIN + 255)		//主动买入中单笔数
#define SM_HQ_BIGSELLTICK3		(SM_HQ_BEGIN + 256)		//主动卖出中单笔数
#define SM_HQ_WAITBUYTICK3		(SM_HQ_BEGIN + 257)		//被动买入中单笔数
#define SM_HQ_WAITSELLTICK3		(SM_HQ_BEGIN + 258)		//被动卖出中单笔数
#define SM_HQ_BIGBUYMONEY3		(SM_HQ_BEGIN + 259)		//主动买入中单金额
#define SM_HQ_BIGSELLMONEY3		(SM_HQ_BEGIN + 260)		//主动卖出中单金额
#define SM_HQ_WAITBUYMONEY3		(SM_HQ_BEGIN + 261)		//被动买入中单金额
#define SM_HQ_WAITSELLMONEY3	(SM_HQ_BEGIN + 262)		//被动卖出中单金额

//#define SM_NO_USE			(SM_HQ_BEGIN + 263)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 264)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 265)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 266)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 267)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 268)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 269)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 270)		//

#define SM_HQ_YEARHIGHDATE		(SM_HQ_BEGIN + 271)		//五十二周最高日期
#define SM_HQ_YEARLOWDATE		(SM_HQ_BEGIN + 272)		//五十二周最低日期
#define SM_HQ_HISHIGHDATE		(SM_HQ_BEGIN + 273)		//年度最高日期
#define SM_HQ_HISLOWDATE		(SM_HQ_BEGIN + 274)		//年度最低日期

#define SM_HQ_NOWLZSTOCK		(SM_HQ_BEGIN + 275)		//领涨股
#define SM_HQ_NOWRISELIMITCOUNT	(SM_HQ_BEGIN + 276)		//涨停家数
#define SM_HQ_NOWFALLLIMITCOUNT	(SM_HQ_BEGIN + 277)		//跌停家数

#define SM_HQ_NEWPRICEUS		(SM_HQ_BEGIN + 278)		//盘后最新价
#define SM_HQ_HKRMBMONEY		(SM_HQ_BEGIN + 279)		//港股指数人民币成交金额

//仅对个股期权有效
#define SM_HQ_ExercisePrice			(SM_HQ_BEGIN + 280)		//期权行权价
#define SM_HQ_StartDate				(SM_HQ_BEGIN + 281)		//首个交易日
#define SM_HQ_EndDate				(SM_HQ_BEGIN + 282)		//最后交易日
#define SM_HQ_ExerciseDate			(SM_HQ_BEGIN + 283)		//期权行权日
#define SM_HQ_ExpireDate			(SM_HQ_BEGIN + 284)		//期权到期日
#define SM_HQ_UpdateVersion			(SM_HQ_BEGIN + 285)		//合约版本号
//#define SM_NO_ClrMmbrLimit		(SM_HQ_BEGIN + 286)		//交易会员持仓限制
#define SM_HQ_DeliveryDate			(SM_HQ_BEGIN + 286)		//行权交割日
//#define SM_NO_LeavesQty			(SM_HQ_BEGIN + 287)		//未平仓合约价
//#define SM_HQ_TotalLongPosition	(SM_HQ_BEGIN + 287)		//当前合约未平仓数

#define SM_HQ_UnderlyingClosePx		(SM_HQ_BEGIN + 288)		//标的证券前收盘
#define SM_HQ_PriceLimitType		(SM_HQ_BEGIN + 289)		//涨跌幅限制类型
//#define SM_NO_PriceUpLimit		(SM_HQ_BEGIN + 290)		//涨幅上限价格
//#define SM_NO_PriceDownLimit		(SM_HQ_BEGIN + 291)		//跌幅下限价格
#define SM_HQ_MarginRatioParam1		(SM_HQ_BEGIN + 290)		//保证金计算比例参数一
#define SM_HQ_MarginRatioParam2		(SM_HQ_BEGIN + 291)		//保证金计算比例参数二
#define SM_HQ_MarginUint			(SM_HQ_BEGIN + 292)		//单位保证金
//#define SM_NO_MarginRatio			(SM_HQ_BEGIN + 293)		//保证金比例
#define SM_HQ_RoundLot				(SM_HQ_BEGIN + 294)		//整手数
#define SM_HQ_LmtOrdMinFloor		(SM_HQ_BEGIN + 295)		//单笔限价申报下限
#define SM_HQ_LmtOrdMaxFloor		(SM_HQ_BEGIN + 296)		//单笔限价申报上限
#define SM_HQ_MktOrdMinFloor		(SM_HQ_BEGIN + 297)		//单笔市价申报下限
#define SM_HQ_MktOrdMaxFloor		(SM_HQ_BEGIN + 298)		//单笔市价申报上限
#define SM_HQ_SecurityStatusFlag	(SM_HQ_BEGIN + 299)		//期权合约状态信息标签
//个股期权-结束


#define	SM_HQ_END				SM_HQ_BEGIN + 300		//行情数据项定义值的结束

/////////////////////////////////////////////////////////////////////////////////
//财经数据库数据项定义
#define	CJ_BBRQ				SM_HQ_TIME			  //日期

#define CJ_ITEM_MASK		0xFFF88FFF			  //财经数据的基本数据项目掩码
#define CJ_REPTYPE_MASK		0x00070000			  //报表类型的掩码

#define CJ_REPTYPE_NONE		0x00000000			  //不做要求
#define	CJ_REPTYPE_SEASON1	0x00010000			  //第一季季报
#define CJ_REPTYPE_HALF		0x00020000			  //中报
#define CJ_REPTYPE_SEASON3	0x00030000			  //第三季季报
#define CJ_REPTYPE_YEAR		0x00040000			  //年报

#define CJ_ITEM(a)			(CJ_ITEM_MASK & (a))	//取数据项目
#define CJ_REPTYPE(a)		(CJ_REPTYPE_MASK & (a))	//取报表类型


#define CJ_TOPVIEW_BIT		0x00200000				// 标识是topview数据
#define CJ_TOPVIEW_DAY		0x00000000				// 标识是日线数据
#define CJ_TOPVIEW_WEEK		0x00400000				// 标识是周线数据
#define CJ_TOPVIEW_MONTH	0x00800000				// 标识是月县数据

#define CJ_IS_TOPVIEW(a)	(CJ_TOPVIEW_BIT & (a))	// 判断是否是topview数据项
#define CJ_MAKE_TV_WEEK(a)	(CJ_TOPVIEW_WEEK | (a))	// 合成周线的topview数据项
#define CJ_MAKE_TV_MONTH(a)	(CJ_TOPVIEW_MONTH |(a))	// 合成月线的topview数据项

#define CJ_TOPVIEW_PERIOD(a) ((CJ_TOPVIEW_WEEK|CJ_TOPVIEW_MONTH) & (a))	// 合成

// 报表时间判断. YYYYMMDD
#define IS_SEASON1_DATE(a)	((a)%10000 == 331)	  //判断日期是否是第一季季报日期
#define IS_HALF_DATE(a)		((a)%10000 == 630)	  //判断日期是否是中报
#define IS_SEASON3_DATE(a)	((a)%10000 == 930)	  //判断日期是否是第三季季报
#define IS_YEAR_DATE(a)		((a)%10000 == 1231)	  //判断日期是否是年报


/////////////////////////////////////////////////////////////////////////////////
#define	SM_FD_BEGIN			301					  //301 财经数据项定义值的开始

#define	SM_FD_BEGIN2		(SM_HQ_END + 100 + 1)		  //401 真正财务数据项目的开始

//四、 股本结构表	
//1、数据表名称：GBJG
//2、说明：上市公司的股本组成及变动情况。
//3、表结构
#define GBJG_BEGIN			SM_FD_BEGIN2		//401

#define      CJ_GBBRQ		(GBJG_BEGIN + 0)	//股本变动日期
#define      CJ_ZGS			(GBJG_BEGIN + 1)	//总股数
#define      CJ_GJG			(GBJG_BEGIN + 2)	//国家股
#define      CJ_FQRG		(GBJG_BEGIN + 3)	//发起人股
#define      CJ_FRG			(GBJG_BEGIN + 4)	//法人股
#define      CJ_NBZGG		(GBJG_BEGIN + 5)	//内部职工股
#define      CJ_SHGZG		(GBJG_BEGIN + 6)	//社会公众股
#define      CJ_ZPG			(GBJG_BEGIN + 7)	//转配股
#define      CJ_WZCG		(GBJG_BEGIN + 8)	//外资持股
#define      CJ_BG			(GBJG_BEGIN + 9)	//B股
#define      CJ_HG			(GBJG_BEGIN + 10)	//H股
#define      CJ_YXG			(GBJG_BEGIN + 11)	//优先股
#define      CJ_KZZ			(GBJG_BEGIN + 12)	//可转换公司债券
#define      CJ_FXJA		(GBJG_BEGIN + 13)	//A股发行价
#define      CJ_FXJB		(GBJG_BEGIN + 14)	//B股发行价
#define      CJ_FXJH		(GBJG_BEGIN + 15)	//H股发行价
#define      CJ_GBSM		(GBJG_BEGIN + 16)	//股本说明
#define      CJ_BDYY		(GBJG_BEGIN + 17)	//股本变动原因
#define      CJ_QXBH		(GBJG_BEGIN + 18)	//权息编号
#define      CJ_ZSZ			(GBJG_BEGIN + 19)	//总市值
#define      CJ_LTSZ		(GBJG_BEGIN + 20)	//流通市值

#define GBJG_END			(GBJG_BEGIN + 49)	//450

//五、 权息资料表	
//1、数据表名称：QXZL
//2、说明：上市公司的分红配股方案。
//3、表结构

#define QXZL_BEGIN			(GBJG_BEGIN + 50)	//451

#define      CJ_QXNF		(QXZL_BEGIN + 0)	//权息年份
#define      CJ_QXSQ		(QXZL_BEGIN + 1)	//权息时期
#define      CJ_QXLX		(QXZL_BEGIN + 2)	//权息类型
#define      CJ_SGBL		(QXZL_BEGIN + 3)	//送股比率
#define      CJ_PGBL		(QXZL_BEGIN + 4)	//配股比率
#define      CJ_PGJ			(QXZL_BEGIN + 5)	//配股价
#define      CJ_XJHL		(QXZL_BEGIN + 6)	//现金红利
#define      CJ_ZPBL		(QXZL_BEGIN + 7)	//转配比率
#define      CJ_ZPJ			(QXZL_BEGIN + 8)	//转配价
#define      CJ_ZZBL		(QXZL_BEGIN + 9)	//转赠比率
#define		 CJ_ZFJ			(QXZL_BEGIN + 10)	//增发价
#define		 CJ_ZFBL		(QXZL_BEGIN + 11)	//增发比率
#define		 CJ_PXBL		(QXZL_BEGIN + 12)	//派息比率
#define		 CJ_CQCKJ		(QXZL_BEGIN + 13)	//除权参考价
#define      CJ_CQXS		(QXZL_BEGIN + 14)    //除权系数

#define      CJ_CQR			(QXZL_BEGIN + 15)     //除权日
#define      CJ_DJR			(QXZL_BEGIN + 16)     //登记日
#define      CJ_PSSR		(QXZL_BEGIN + 17)     //配股上市日
#define      CJ_PGHLRQQ		(QXZL_BEGIN + 18)    //缴（领）款起始日
#define      CJ_PGHLRQZ		(QXZL_BEGIN + 19)    //缴（领）款终止日
#define      CJ_QXSM		(QXZL_BEGIN + 20)    //权息说明
#define QXZL_END			(QXZL_BEGIN + 49)	//500

//权息类型
#define		 QXLX_D				'D'			//定案		
#define		 QXLX_Y				'Y'			//预案

//六、 资产负债表
//1、数据表名称：ZCFZB
//2、说明：上市公司的资产负债情况。
//3、表
#define ZCFZB_BEGIN			SM_FD_BEGIN + 200	//501

#define      CJ_HBZJ		(ZCFZB_BEGIN + 0)    //货币资金
#define      CJ_DQTZ		(ZCFZB_BEGIN + 1)    //短期投资
#define      CJ_DQTZDJ		(ZCFZB_BEGIN + 2)    //短期投资跌价准备
#define      CJ_YSPJ		(ZCFZB_BEGIN + 3)    //应收票据
#define      CJ_YSGL		(ZCFZB_BEGIN + 4)    //应收股利
#define      CJ_YSLX		(ZCFZB_BEGIN + 5)    //应收利息
#define      CJ_YSZK		(ZCFZB_BEGIN + 6)    //应收帐款
#define      CJ_QTYSK		(ZCFZB_BEGIN + 7)    //其他应收款
#define      CJ_HZZB		(ZCFZB_BEGIN + 8)    //坏帐准备
#define      CJ_YSZKJE		(ZCFZB_BEGIN + 9)	 //应收帐款净额

#define      CJ_YUFZK		(ZCFZB_BEGIN + 10)   //预付帐款
#define      CJ_YSBTK		(ZCFZB_BEGIN + 11)   //应收补贴款
#define      CJ_NBYSK		(ZCFZB_BEGIN + 12)   //内部应收款
#define      CJ_CH			(ZCFZB_BEGIN + 13)   //存货
#define      CJ_CHDJZB		(ZCFZB_BEGIN + 14)   //存货跌价准备
#define      CJ_CHJE		(ZCFZB_BEGIN + 15)   //存货净额
#define      CJ_DTFY		(ZCFZB_BEGIN + 16)   //待摊费用
#define      CJ_YNDQTZ		(ZCFZB_BEGIN + 17)   //一年内到期的长期债券投资
#define      CJ_QTLDZC		(ZCFZB_BEGIN + 18)   //其他流动资产
#define      CJ_LDZCHJ		(ZCFZB_BEGIN + 19)   //流动资产合计

#define      CJ_CQGQTZ		(ZCFZB_BEGIN + 20)   //长期股权投资
#define      CJ_CQZQTZ		(ZCFZB_BEGIN + 21)   //长期债券投资
#define      CJ_CQTZJZ		(ZCFZB_BEGIN + 22)   //长期投资减值准备
#define      CJ_CQTZHJ		(ZCFZB_BEGIN + 23)   //长期投资合计
#define      CJ_GDZCYJ		(ZCFZB_BEGIN + 24)   //固定资产原价
#define      CJ_LJZJ		(ZCFZB_BEGIN + 25)   //累计折旧
#define      CJ_GDZCJZ		(ZCFZB_BEGIN + 26)   //固定资产减值准备
#define      CJ_GCWZ		(ZCFZB_BEGIN + 27)   //工程物资
#define      CJ_ZJGC		(ZCFZB_BEGIN + 28)   //在建工程
#define      CJ_ZJGCJZ		(ZCFZB_BEGIN + 29)   //在建工程减值准备

#define      CJ_GDZCQL		(ZCFZB_BEGIN + 30)   //固定资产清理
#define      CJ_GDZCHJ		(ZCFZB_BEGIN + 31)   //固定资产合计
#define		 CJ_WXZC		(ZCFZB_BEGIN + 32)   //无形资产
#define      CJ_WXZCJZ		(ZCFZB_BEGIN + 33)   //无形资产减值准备
#define      CJ_CQDTFY		(ZCFZB_BEGIN + 34)   //长期待摊费用
#define      CJ_QTCQZC		(ZCFZB_BEGIN + 35)   //其他长期资产
#define      CJ_WXJQT		(ZCFZB_BEGIN + 36)   //无形资产及其他资产合计
#define      CJ_DYZC		(ZCFZB_BEGIN + 37)   //递延资产
#define      CJ_DYSKJX		(ZCFZB_BEGIN + 38)   //递延税款借项
#define      CJ_DCLLCSS		(ZCFZB_BEGIN + 39)   //待处理流动资产损失

#define      CJ_DCLGCSS		(ZCFZB_BEGIN + 40)   //待处理固定资产损失
#define      CJ_DCLZCSS		(ZCFZB_BEGIN + 41)   //待处理资产损失
#define      CJ_ZCZJ		(ZCFZB_BEGIN + 42)   //资产总计
#define      CJ_DQJK		(ZCFZB_BEGIN + 43)   //短期借款
#define      CJ_YFPJ		(ZCFZB_BEGIN + 44)   //应付票据
#define      CJ_YFZK		(ZCFZB_BEGIN + 45)   //应付帐款
#define      CJ_YUSZK		(ZCFZB_BEGIN + 46)   //预收帐款
#define      CJ_YFGZ		(ZCFZB_BEGIN + 47)   //应付工资
#define      CJ_YFFLF		(ZCFZB_BEGIN + 48)   //应付福利费
#define      CJ_YFGL		(ZCFZB_BEGIN + 49)   //应付股利

#define      CJ_YJSJ		(ZCFZB_BEGIN + 50)   //应交税金
#define      CJ_QTYJK		(ZCFZB_BEGIN + 51)   //其他应交款
#define      CJ_QTYFK		(ZCFZB_BEGIN + 52)   //其他应付款
#define      CJ_NBYFK		(ZCFZB_BEGIN + 53)   //内部应付款
#define      CJ_YUTFY		(ZCFZB_BEGIN + 54)   //预提费用
#define      CJ_DKSJ		(ZCFZB_BEGIN + 55)   //待扣税金
#define      CJ_YJFZ		(ZCFZB_BEGIN + 56)   //预计负债
#define      CJ_YNDQFZ		(ZCFZB_BEGIN + 57)   //一年内到期的长期的长期负债
#define      CJ_QTLDFZ		(ZCFZB_BEGIN + 58)   //其他流动负债
#define      CJ_LDFZHJ		(ZCFZB_BEGIN + 59)   //流动负债合计

#define      CJ_CQJK		(ZCFZB_BEGIN + 60)   //长期借款
#define      CJ_YFZHK		(ZCFZB_BEGIN + 61)   //应付债款
#define      CJ_CQYFK		(ZCFZB_BEGIN + 62)   //长期应付款
#define      CJ_ZXYFK		(ZCFZB_BEGIN + 63)   //专项应付款
#define      CJ_QTCQFZ		(ZCFZB_BEGIN + 64)   //其他长期负债
#define      CJ_ZFZZJ		(ZCFZB_BEGIN + 65)   //住房周转金
#define      CJ_CQFZHJ		(ZCFZB_BEGIN + 66)   //长期负债合计
#define      CJ_DYSKDX		(ZCFZB_BEGIN + 67)   //递延税款贷项
#define      CJ_FZHJ		(ZCFZB_BEGIN + 68)   //负债合计
#define      CJ_GB			(ZCFZB_BEGIN + 69)   //股本

#define      CJ_ZBGJ		(ZCFZB_BEGIN + 70)   //资本公积
#define      CJ_YYGJ		(ZCFZB_BEGIN + 71)   //盈余公积
#define      CJ_FDGYJ		(ZCFZB_BEGIN + 72)   //法定公益金
#define      CJ_WFPLR		(ZCFZB_BEGIN + 73)   //未分配利润
#define      CJ_GDQYHJ		(ZCFZB_BEGIN + 74)   //股东权益合计
#define      CJ_SSGQ		(ZCFZB_BEGIN + 75)   //少数股权
#define      CJ_FZGDQY		(ZCFZB_BEGIN + 76)   //负债和股东权益合计

//资产负债表计算项目
#define      CJ_GDZCJE		(ZCFZB_BEGIN + 79)   //固定资产净额
#define      CJ_LDBL		(ZCFZB_BEGIN + 80)   //流动比率
#define      CJ_SDBL		(ZCFZB_BEGIN + 81)   //速动比率
#define      CJ_CSDBL		(ZCFZB_BEGIN + 82)   //超速动比率
#define      CJ_XJBL		(ZCFZB_BEGIN + 83)   //现金比率
#define      CJ_GDQYBL		(ZCFZB_BEGIN + 84)   //股东权益比率
#define      CJ_ZCFZBL		(ZCFZB_BEGIN + 85)   //资产负债比率
#define      CJ_ZBFZBL		(ZCFZB_BEGIN + 86)   //资本负债比率
#define      CJ_CQFZBL		(ZCFZB_BEGIN + 87)   //长期负债比率
#define      CJ_GQGDZCBL	(ZCFZB_BEGIN + 88)   //股东权益与固定资产比率
#define      CJ_YXFZBL		(ZCFZB_BEGIN + 89)   //有息负债比率
#define      CJ_ZJGCGGXS	(ZCFZB_BEGIN + 90)   //在建工程杠杆系数
#define      CJ_YSLDBL		(ZCFZB_BEGIN + 91)   //其他应收帐款/流动资产
#define		 CJ_GJJ			(ZCFZB_BEGIN + 92)	 //公积金

//七、 利润及利润分配表
//1、数据表名称：LRFPB
//2、说明：上市公司的某段时期内（半年、一年）利润及利润分配情况。
//3、表结构
#define LRFPB_BEGIN			SM_FD_BEGIN + 300	  //601

#define      CJ_LQSRQ		(LRFPB_BEGIN + 0)	  //报表起始日期
#define      CJ_ZYYWSR		(LRFPB_BEGIN + 1)     //主营业务收入
#define      CJ_ZYYWCB      (LRFPB_BEGIN + 2)     //主营业务成本
#define      CJ_ZYYWSJ		(LRFPB_BEGIN + 3)     //主营业务税金及附加
#define      CJ_ZYYWLR		(LRFPB_BEGIN + 4)     //主营业务利润
#define      CJ_QTLR		(LRFPB_BEGIN + 5)     //其他业务利润
#define      CJ_YYFY		(LRFPB_BEGIN + 6)     //营业费用
#define      CJ_GLFY		(LRFPB_BEGIN + 7)     //管理费用
#define      CJ_CWFY		(LRFPB_BEGIN + 8)     //财务费用
#define      CJ_YYLR		(LRFPB_BEGIN + 9)     //营业利润

#define      CJ_TZSY		(LRFPB_BEGIN + 10)    //投资收益
#define      CJ_BTSR		(LRFPB_BEGIN + 11)    //补贴收入
#define      CJ_YYWSR		(LRFPB_BEGIN + 12)    //营业外收入
#define      CJ_YYWZC		(LRFPB_BEGIN + 13)    //营业外支出
#define      CJ_LRZE		(LRFPB_BEGIN + 14)    //利润总额
#define      CJ_SDS			(LRFPB_BEGIN + 15)    //所得税
#define      CJ_LSSGQ		(LRFPB_BEGIN + 16)    //少数股权
#define      CJ_WQRTZSS		(LRFPB_BEGIN + 17)    //未确认的投资损失
#define      CJ_JLR			(LRFPB_BEGIN + 18)    //净利润
#define      CJ_SHLR		(LRFPB_BEGIN + 19)    //税后利润

#define      CJ_QCWFPLR		(LRFPB_BEGIN + 20)    //期初末分配利润
#define      CJ_SQLRTZ		(LRFPB_BEGIN + 21)    //上期利润调转
#define      CJ_YYGJJZR		(LRFPB_BEGIN + 22)    //盈余公积金转入
#define      CJ_KGFPLR		(LRFPB_BEGIN + 23)    //可供分配的利润
#define      CJ_TQFDGJ		(LRFPB_BEGIN + 24)    //提取法定盈余公积
#define      CJ_TQGYJ		(LRFPB_BEGIN + 25)    //提取法定公益金
#define      CJ_TQZGJL		(LRFPB_BEGIN + 26)    //提取职工奖励及福利基金
#define      CJ_TQCBJJ		(LRFPB_BEGIN + 27)    //提取储备基金
#define      CJ_TQQYFZ		(LRFPB_BEGIN + 28)    //提取企业发展基金
#define      CJ_LRGHTZ		(LRFPB_BEGIN + 29)    //利润归还投资

#define      CJ_KGGDFPLR	(LRFPB_BEGIN + 30)    //可供股东分配利润
#define      CJ_YFYXGL		(LRFPB_BEGIN + 31)    //应付优先股股利
#define      CJ_TQRYGJ		(LRFPB_BEGIN + 32)    //提取任意盈余公积
#define      CJ_YFPTGL		(LRFPB_BEGIN + 33)    //应付普通股股利
#define      CJ_ZZGB		(LRFPB_BEGIN + 34)    //转作股本的普通股股利
#define      CJ_LWFPLR		(LRFPB_BEGIN + 35)    //未分配利润


#define      CJ_YYFYL		(LRFPB_BEGIN + 49)    //营业费用率
#define      CJ_CWFYL		(LRFPB_BEGIN + 50)    //财务费用率
#define      CJ_YYCBBL		(LRFPB_BEGIN + 51)    //营业成本比率
#define      CJ_XSMLL		(LRFPB_BEGIN + 52)    //销售毛利率
#define      CJ_ZYYWLRL		(LRFPB_BEGIN + 53)    //主营业务利润率
#define      CJ_YYLRL		(LRFPB_BEGIN + 54)    //营业利润率
#define      CJ_SQLRL		(LRFPB_BEGIN + 55)    //税前利润率
#define      CJ_SHLRL		(LRFPB_BEGIN + 56)    //税后利润率

// 理财帐户，用于帐户相关得理财数据
#define		 LCZH_BEGIN		(SM_FD_BEGIN + 400)	  // 701

#define		 LCZH_JHBH		(LCZH_BEGIN + 1)	  // 计划编号
#define		 LCZH_USERID	(LCZH_BEGIN + 2)	  // 用户ID
#define		 LCZH_ZDRQ		(LCZH_BEGIN + 3)	  // 计划开始的时间	
#define		 LCZH_JHCG		(LCZH_BEGIN + 4)	  // 计划周期	
#define		 LCZH_ZXZT		(LCZH_BEGIN + 5)	  // 计划执行状态	
#define		 LCZH_WTSL		(LCZH_BEGIN + 6)	  // 委托数量	
#define		 LCZH_MMD		(LCZH_BEGIN + 7)	  // 买入点价格
#define		 LCZH_ZYJG		(LCZH_BEGIN + 8)	  // 止盈价格
#define		 LCZH_MMTJ		(LCZH_BEGIN + 9)	  // 买卖条件
#define		 LCZH_ZSFS		(LCZH_BEGIN + 10)	  // 止损方式	
#define		 LCZH_ZXZTNAME	(LCZH_BEGIN + 11)	  // 计划执行状态的名称
#define		 LCZH_NOTE		(LCZH_BEGIN + 12)     // 交易计划的备注		
#define		 LCZH_USERNAME	(LCZH_BEGIN + 13)     // 帐户的名称 
#define		 LCZH_ZSJG		(LCZH_BEGIN + 14)	  // 止损价格	
#define		 LCZH_LASTZSJG	(LCZH_BEGIN + 15)	  // 最后一个止损价格	
#define		 LCZH_BBJ		(LCZH_BEGIN + 16)	  // 保本价格
#define		 LCZH_CGTS		(LCZH_BEGIN + 17)	  // 持股天数
#define		 LCZH_ZBGZ_TYPE	 (LCZH_BEGIN + 18)	  // 指标跟踪的操作类型
#define		 LCZH_ZBGZ_PRICE (LCZH_BEGIN + 19)	  // 指标跟踪的成交价格
#define		 LCZH_ZBGZ_NAME  (LCZH_BEGIN + 20)	  // 指标跟踪的指标名称
#define		 LCZH_BCFX		(LCZH_BEGIN + 21)	  // 本次风险
#define		 LCZH_YQYL		(LCZH_BEGIN + 22)	  // 预期盈利
#define		 LCZH_END		(LCZH_BEGIN + 79)	  // 780

// 通用数据项目，用户高级网页选股返回的数据 SuperServerSelectStock
#define		 SSSS_BEGIN		(SM_FD_BEGIN + 480)	  // 781	
#define		 SSSS_COMM_1	(SSSS_BEGIN  + 1)	  // 782	
#define		 SSSS_COMM_2	(SSSS_BEGIN  + 2)	  // 783	
#define		 SSSS_COMM_3	(SSSS_BEGIN  + 3)	  // 784
#define		 SSSS_COMM_4	(SSSS_BEGIN  + 4)     // 785
#define		 SSSS_COMM_5	(SSSS_BEGIN  + 5)	  // 786
#define		 SSSS_COMM_6	(SSSS_BEGIN  + 6)	  // 787	
#define		 SSSS_COMM_7	(SSSS_BEGIN  + 7)	  // 788
#define		 SSSS_COMM_8	(SSSS_BEGIN  + 8)	  // 789	
#define		 SSSS_COMM_9	(SSSS_BEGIN  + 9)	  // 790	
#define		 SSSS_COMM_10	(SSSS_BEGIN  + 10)	  // 791
#define		 SSSS_COMM_11	(SSSS_BEGIN  + 11)	  // 792	
#define		 SSSS_COMM_12	(SSSS_BEGIN  + 12)	  // 793	
#define		 SSSS_COMM_13	(SSSS_BEGIN  + 13)	  // 794
#define		 SSSS_COMM_14	(SSSS_BEGIN  + 14)    // 795
#define		 SSSS_COMM_15	(SSSS_BEGIN  + 15)	  // 796
#define		 SSSS_COMM_16	(SSSS_BEGIN  + 16)	  // 797	
#define		 SSSS_COMM_17	(SSSS_BEGIN  + 17)	  // 798
#define		 SSSS_COMM_18	(SSSS_BEGIN  + 18)	  // 799	
#define		 SSSS_END		(SSSS_BEGIN  + 19)	  // 800


// 股权分置
#define		GQFZS_BEGIN		(SM_FD_BEGIN + 500)		  //	801

#define		CJ_GQFZ_FH			(GQFZS_BEGIN + 1)    //股权分置分红
#define		CJ_GQFZ_SG			(GQFZS_BEGIN + 2)    //股权分置送股
#define		CJ_GQFZ_SM			(GQFZS_BEGIN + 3)    //股权分置说明
#define		CJ_GQFZ_GOU_XQGS	(GQFZS_BEGIN + 4)	//每份认购权证的行权股数
#define		CJ_GQFZ_GOU_XQJG	(GQFZS_BEGIN + 5)	//认购权证行权价格
#define		CJ_GQFZ_GOU_QZGS	(GQFZS_BEGIN + 6)	//流通股股东每10股或赠认购权证股数
#define		CJ_GQFZ_GU_XQGS		(GQFZS_BEGIN + 7)	//每份认沽权证的行权股数
#define		CJ_GQFZ_GU_XQJG		(GQFZS_BEGIN + 8)	//认沽权证行权价格
#define		CJ_GQFZ_GU_QZGS		(GQFZS_BEGIN + 9)	//流通股股东每10股或赠认沽权证股数
#define		CJ_GQFZ_SUOGU		(GQFZS_BEGIN + 10)	//非流通股股东每10股缩为x股
#define		CJ_GQFZ_GQDJR		(GQFZS_BEGIN + 11)	//股权登记日
#define		CJ_GQFZ_SSLTR		(GQFZS_BEGIN + 12)	//上市流通日
#define		CJ_GQFZ_XJFFR		(GQFZS_BEGIN + 13)	//现金发放日
#define		CJ_GQFZ_BZ			(GQFZS_BEGIN + 14)	//备注

#define		GQFZS_END			(GQFZS_BEGIN + 19)	//	820

// 个人版交易计划数据
#define		JYJH_BEGIN				(SM_FD_BEGIN + 520) // 821
#define		JYJH_STOCK_TOTAL		(JYJH_BEGIN + 1)	// 每个股票交易计划的总数 
#define		JYJH_STOCK_FINISH		(JYJH_BEGIN + 2)	// 每个股票交易计划的已完成数 
#define		JYJH_STOCK_SUCC			(JYJH_BEGIN + 3)	// 每个股票交易计划的成功次数
#define		JYJH_STOCK_SUCC_RATE	(JYJH_BEGIN + 4)	// 每个股票交易计划的成功率
#define		JYJH_STOCK_WIN_RATE		(JYJH_BEGIN + 5)	// 每个股票交易计划的总收益率

//外汇期权信息(根据招行外汇接口定义的)
#define		FXQQ_BEGIN				(SM_FD_BEGIN + 570)		// 871
#define		FXQQ_HBD				FXQQ_BEGIN 				//货币对(如: EURUSD)
#define		FXQQ_DQR				(FXQQ_BEGIN + 1)		//到期日(如: 06-07-31)
#define		FXQQ_ZXJG				(FXQQ_BEGIN + 2)		//执行价格(如: 1.2892)
#define		FXQQ_QQZL				(FXQQ_BEGIN + 3)		//期权种类(看涨C、看跌P)
#define		FXQQ_END				(SM_FD_BEGIN + 579)		// 880

// 权证信息 
#define QZXX_BEGIN				(SM_FD_BEGIN + 580)		// 881
#define QZXX_BDZQ				(QZXX_BEGIN + 0)		//标的证券
#define QZXX_QZLX				(QZXX_BEGIN + 1)		//权证类型
#define QZXX_QZYE				(QZXX_BEGIN + 2)		//权证余额
#define QZXX_JSFS				(QZXX_BEGIN + 3)		//结算方式
#define QZXX_XQFS				(QZXX_BEGIN + 4)		//行权方式
#define QZXX_JSJG				(QZXX_BEGIN + 5)		//结算价格
#define QZXX_XQJG				(QZXX_BEGIN + 6)		//行权价格
#define QZXX_XQBL				(QZXX_BEGIN + 7)		//行权比例
#define QZXX_QSRQ				(QZXX_BEGIN + 8)		//起始日期 
#define QZXX_JZRQ				(QZXX_BEGIN + 9)		//截止日期
#define QZXX_SYRQ				(QZXX_BEGIN + 10)		//使用日期
#define QZXX_END				(SM_FD_BEGIN + 599)		// 900

//九、 现金流量表
//XJLLB
#define XJLLB_BEGIN				SM_FD_BEGIN + 600	//901

#define      CJ_XQSRQ			(XJLLB_BEGIN + 0)    //报表起始日期
#define      CJ_JYR_XS			(XJLLB_BEGIN + 1)    //销售商品提供劳务收到的现金
#define      CJ_JYR_ZJ			(XJLLB_BEGIN + 2)    //收到的租金
#define      CJ_JYR_SFFH		(XJLLB_BEGIN + 3)    //收到的税费返还
#define      CJ_JYR_QT			(XJLLB_BEGIN + 4)    //收到的其它与经营活动有关的现金
#define      CJ_JYRXJ			(XJLLB_BEGIN + 5)    //经营活动产生的现金流入小计
#define      CJ_JYC_GM			(XJLLB_BEGIN + 6)    //购买商品接受劳务支付的现金
#define      CJ_JYC_ZL			(XJLLB_BEGIN + 7)    //经营租赁所支付的现金
#define      CJ_JYC_GZ			(XJLLB_BEGIN + 8)    //支付给职工以及为职工支付的现金
#define      CJ_JYC_ZZS			(XJLLB_BEGIN + 9)    //支付的增值税款
#define      CJ_JYC_SDS			(XJLLB_BEGIN + 10)   //支付的所得税款
#define      CJ_JYC_QTS			(XJLLB_BEGIN + 11)   //支付的除增值税所得税以外的其他税费
#define      CJ_JYC_QT			(XJLLB_BEGIN + 12)   //支付的其他预经营活动有关的现金
#define      CJ_JYCXJ			(XJLLB_BEGIN + 13)   //经营活动产生的现金流出小计
#define      CJ_JYJE			(XJLLB_BEGIN + 14)   //经营活动产生的现金流量净额
#define      CJ_TZR_HB			(XJLLB_BEGIN + 15)   //收回投资所收到的现金
#define      CJ_TZR_SYXJ		(XJLLB_BEGIN + 16)   //取得投资收益所收到的现金
#define      CJ_TZR_CQZC		(XJLLB_BEGIN + 17)   //处置固定资产无形资产和其他长期资产而收到的现金净额
#define      CJ_TZR_QT			(XJLLB_BEGIN + 18)   //收到的其他与投资活动有关的现金金净额
#define      CJ_TZRXJ			(XJLLB_BEGIN + 19)   //投资活动所产生的现金流入小计
#define      CJ_TZC_CQZC		(XJLLB_BEGIN + 20)   //购建固定资产无形资产和其他长期资产所支付的现金
#define      CJ_TZC_QYTZ		(XJLLB_BEGIN + 21)   //权益性投资所支付的现金金
#define      CJ_TZC_ZQTZ		(XJLLB_BEGIN + 22)   //债权性投资所支付的现金
#define      CJ_TZC_QT			(XJLLB_BEGIN + 23)   //支付的其他与投资活动有关的现金
#define      CJ_TZCXJ			(XJLLB_BEGIN + 24)   //投资活动所产生的现金流出小计
#define      CJ_TZJE			(XJLLB_BEGIN + 25)   //投资活动所产生的现金流量净额
#define      CJ_MZR_QYTZ		(XJLLB_BEGIN + 26)   //吸收权益性投资所收到的现金
#define      CJ_MZR_FXZQ		(XJLLB_BEGIN + 27)   //发行债券所收到的现金
#define      CJ_MZR_JZ			(XJLLB_BEGIN + 28)   //借债所收到的现金
#define      CJ_MZR_QT			(XJLLB_BEGIN + 29)   //收到的其他与筹资活动有关的现金
#define      CJ_MZRXJ			(XJLLB_BEGIN + 30)   //筹资活动产生的现金流入小计
#define      CJ_MZC_CHZW		(XJLLB_BEGIN + 31)   //偿还债务所支付的现金
#define      CJ_MZC_MZFY		(XJLLB_BEGIN + 32)   //发生筹资费用搜索支付的现金
#define      CJ_MZC_FPGL		(XJLLB_BEGIN + 33)   //分配股利或利润所支付的现金
#define      CJ_MZC_CFLX		(XJLLB_BEGIN + 34)   //偿付利息所支付的现金
#define      CJ_MZC_RZZL		(XJLLB_BEGIN + 35)   //融资租赁所支付的现金
#define      CJ_MZC_JZCZ		(XJLLB_BEGIN + 36)   //减少注册资本支付的现金
#define      CJ_MZC_QT			(XJLLB_BEGIN + 37)   //支付的其他与筹资活动有关的现金
#define      CJ_MZCXJ			(XJLLB_BEGIN + 38)   //筹资活动产生的现金流出小计
#define      CJ_MZJE			(XJLLB_BEGIN + 39)   //筹资活动产生的现金流量净额
#define      CJ_HLBD			(XJLLB_BEGIN + 40)   //汇率变动对现金的影响额
#define      CJ_XJJZJ			(XJLLB_BEGIN + 41)   //现金及现金等价物净增加额
#define      CJ_XSSGQ			(XJLLB_BEGIN + 42)   //少数股东损益
#define      CJ_JTZCJZZB		(XJLLB_BEGIN + 43)   //计提的资产减值准备
#define      CJ_GDZCZJ			(XJLLB_BEGIN + 44)   //固定资产折旧
#define      CJ_WXZCTX			(XJLLB_BEGIN + 45)   //无形资产摊销
#define      CJ_QTZCTX			(XJLLB_BEGIN + 46)   //长期待摊费用摊销
#define      CJ_CZSS			(XJLLB_BEGIN + 47)   //处置固定资产无形资产和其他长期资产的损失（减收益）
#define      CJ_GDZCSS			(XJLLB_BEGIN + 48)   //固定资产报废损失
#define      CJ_XCWFY			(XJLLB_BEGIN + 49)   //财务费用
#define      CJ_TZSS			(XJLLB_BEGIN + 50)   //投资损失（减收益）
#define      CJ_XDYSKDX			(XJLLB_BEGIN + 51)   //递延税款贷项（减借项）
#define      CJ_CHJS			(XJLLB_BEGIN + 52)   //存货的减少（减增加）
#define      CJ_JYYSJS			(XJLLB_BEGIN + 53)   //经营性应收项目的减少（减增加）
#define      CJ_JYYFJS			(XJLLB_BEGIN + 54)   //经营性应付项目的增加（减减少）
#define      CJ_ZZSZJJE			(XJLLB_BEGIN + 55)   //增值税增加净额（减减少）
#define      CJ_QT				(XJLLB_BEGIN + 56)   //其他
#define      CJ_ZWZZB			(XJLLB_BEGIN + 57)   //债务转为资本
#define      CJ_YNDQZQ			(XJLLB_BEGIN + 58)   //一年内到期的可转换公司债券
#define      CJ_RZGDZC			(XJLLB_BEGIN + 59)   //融资租入固定资产
#define      CJ_XJQMYE			(XJLLB_BEGIN + 60)   //现金的期末余额
#define      CJ_XJQCYE			(XJLLB_BEGIN + 61)   //现金的期初余额
#define      CJ_DJWQMYE			(XJLLB_BEGIN + 62)   //现金等价物的期末余额
#define      CJ_DJWQCYE			(XJLLB_BEGIN + 63)   //现金等价物的期初余额

//十、 计算项目
#define JSXM_BEGIN				SM_FD_BEGIN + 700	//1001

#define      CJ_GBSYL			(JSXM_BEGIN + 0)    //股本收益率
#define      CJ_MGYL			(JSXM_BEGIN + 1)    //每股盈利
#define      CJ_YSZKZZL			(JSXM_BEGIN + 2)    //应收帐款周转率
#define      CJ_YSZKZZTS		(JSXM_BEGIN + 3)    //应收帐款周转天数
#define      CJ_MGJZC			(JSXM_BEGIN + 4)    //每股净资产
#define      CJ_JZCTZXS			(JSXM_BEGIN + 5)    //净资产调整系数K值
#define      CJ_SXFYZZL			(JSXM_BEGIN + 6)    //三项费用增长率
#define      CJ_CHZZL			(JSXM_BEGIN + 7)    //存货周转率
#define      CJ_CHZZTS			(JSXM_BEGIN + 9)    //存货周转天数
#define      CJ_GDZCZZL			(JSXM_BEGIN + 10)   //固定资产周转率
#define      CJ_ZZCZZL			(JSXM_BEGIN + 11)   //总资产周转率
#define      CJ_GQZZL			(JSXM_BEGIN + 12)   //股东权益周转率
#define      CJ_ZYYWSRZZL		(JSXM_BEGIN + 13)   //主营业务收入增长率
#define      CJ_ZCSYL			(JSXM_BEGIN + 14)   //资产收益率
#define      CJ_JZCSYL			(JSXM_BEGIN + 15)   //净资产收益率
#define      CJ_ZZCHBL			(JSXM_BEGIN + 16)   //总资产回报率
#define      CJ_XSXJZYSRBL		(JSXM_BEGIN + 17)   //销售商品收到现金与主营业务收入比率
#define      CJ_JYXJLRBL		(JSXM_BEGIN + 18)   //经营活动产生的现金流量净额与净利润比率
#define      CJ_MGXJZJ			(JSXM_BEGIN + 19)   //每股现金及现金等价物净增加额

#define HXLC_BEGIN				(SM_FD_BEGIN + 809)	// 1110 核新理财
#define CJ_STAR					(HXLC_BEGIN + 0)	// 星级

#define CJ_STAR_PLATE			(HXLC_BEGIN + 1)	// x:星级-y:盘面
#define CJ_GROW_PLATE			(HXLC_BEGIN + 2)	// x:成长性-y:盘面
#define CJ_WALK_PLATE			(HXLC_BEGIN + 3)	// x:走势-y:盘面
#define CJ_RISK_PLATE			(HXLC_BEGIN + 4)	// x:风险-y:盘面

#define CJ_STOCK_DIARY			(HXLC_BEGIN + 10)	// 股市日记的显示

#define CJ_PRICE_MEMO			(HXLC_BEGIN + 86)	// 1196 价格区间备注
#define CJ_PRICE_LOW			(HXLC_BEGIN + 87)	// 1197	价格区间低价格
#define CJ_PRICE_UP				(HXLC_BEGIN + 88)	// 1198 价格区间高价格
#define HXLC_END				(HXLC_BEGIN + 89)	// 1199

//大单统计的数据项目
#define	CJ_TJ_ZJLR				1333				//资金流入
#define	CJ_TJ_ZJLC				1334				//资金流出

#define CJ_REAL_BEGIN1			1335				//会实时变化的财务数据开始1
#define CJ_DD_Z_BUY				1340				//主动买入股数
#define CJ_DD_Z_BUY_COUNT		1341				//主动买入次数
#define CJ_DD_Z_SELL			1342				//主动卖出股数
#define CJ_DD_Z_SELL_COUNT		1343				//主动卖出次数

#define CJ_DD_B_BUY				1344				//被动买入股数
#define CJ_DD_B_BUY_COUNT		1345				//被动买入次数
#define CJ_DD_B_SELL			1346				//被动卖出股数
#define CJ_DD_B_SELL_COUNT		1347				//被动卖出次数

#define CJ_REAL_END1			1349				//会实时变化的财务数据结束1

#define CJ_REAL_BEGIN2			1380				//会实时变化的财务数据开始2
#define CJ_DD_Z_BUY_AMT			1380				//主动买入金额
#define CJ_DD_Z_SELL_AMT		1381				//主动卖出金额
#define CJ_DD_B_BUY_AMT			1382				//被动买入金额
#define CJ_DD_B_SELL_AMT		1383				//被动卖出金额

#define CJ_REAL_END2			1400				//会实时变化的财务数据结束2

//十一、基金项目

#define	JJXM_BEGIN				SM_FD_BEGIN + 1100	// 1401

#define	JJXM_END				SM_FD_BEGIN + 1300	// 1601

// 增加的股本结构
#define GBJG2_BEGIN				SM_FD_BEGIN + 1369	// 1670
#define CJ_AG					GBJG2_BEGIN + 4		// 1674 流通A股
#define GBJG2_END				SM_FD_BEGIN + 1374	// 1675

// 十大股东
#define SDGD_BEGIN				SM_FD_BEGIN + 1375	// 1676
#define SDGD_END				SM_FD_END	+ 1394	// 1695

// 利润分配2
#define LRFP2_BEGIN				SM_FD_BEGIN + 1429	// 1730
#define LRFP2_END				SM_FD_END	+ 1441	// 1742

// 现金流量
#define	XJLL2_BEGIN				SM_FD_BEGIN + 1444	// 1745
#define XJLL2_END				SM_FD_END	+ 1455	// 1756

// 资产负债
#define ZCFZ2_BEGIN				SM_FD_BEGIN + 1456	// 1757
#define ZCFZ2_END				SM_FD_END	+ 1522	// 1823

// 利润分配3
#define LRFP3_BEGIN				SM_FD_BEGIN + 1524	// 1825
#define LRFP3_END				SM_FD_BEGIN + 1614	// 1915

// 财务附注
#define CWFZ_BEGIN				SM_FD_BEGIN + 1615	// 1916
#define CWFZ_END				SM_FD_END	+ 1642	// 1943

// 国债资料
#define GZZL_BEGIN				SM_FD_BEGIN	+ 1649	// 1950
#define GZZL_END				SM_FD_END	+ 1662	// 1963

#define	SM_FD_END				SM_FD_BEGIN + 1800	//2101 财经数据库数据项定义值的结束

///////////////////////////////////////////////////////////////////////////////////////////
//委托数据项(预留100个，可以从高位扩展）
#define SM_WT_BEGIN			SM_FD_END + 1			//2102 委托数据定义开始
#define SM_WT_END			SM_WT_BEGIN + 100		//2202 委托数据定义结束

/////////////////////////////////////////////////////////////////////////////////////////
//内部函数，无公式。
#define SM_FUNC_BEGIN		SM_WT_END + 1			//函数定义开始 =2203
//
//引用函数											//2204
#define SM_FUNC_BACKSET		(SM_FUNC_BEGIN + 1)		//
#define SM_FUNC_BARSCOUNT	(SM_FUNC_BEGIN + 2)		//
#define SM_FUNC_BARSLAST	(SM_FUNC_BEGIN + 3)		//
#define SM_FUNC_BARSSINCE	(SM_FUNC_BEGIN + 4)		//
#define SM_FUNC_COUNT		(SM_FUNC_BEGIN + 5)		//
#define SM_FUNC_DMA			(SM_FUNC_BEGIN + 6)		//
#define SM_FUNC_EMA			(SM_FUNC_BEGIN + 7)		//
#define SM_FUNC_FILTER		(SM_FUNC_BEGIN + 8)		//
#define SM_FUNC_HHV			(SM_FUNC_BEGIN + 9)		//
#define SM_FUNC_HHVBARS		(SM_FUNC_BEGIN + 10)	//
#define SM_FUNC_LLV			(SM_FUNC_BEGIN + 11)	//
#define SM_FUNC_LLVBARS		(SM_FUNC_BEGIN + 12)	//
#define SM_FUNC_MA			(SM_FUNC_BEGIN + 13)	//
#define SM_FUNC_REF			(SM_FUNC_BEGIN + 14)	//
#define SM_FUNC_SMA			(SM_FUNC_BEGIN + 15)	//
#define SM_FUNC_SUM			(SM_FUNC_BEGIN + 16)	//求和
#define SM_FUNC_SUMBARS		(SM_FUNC_BEGIN + 17)	//
#define SM_FUNC_WMA			(SM_FUNC_BEGIN + 18)	//加权移动平均
#define SM_FUNC_REFX		(SM_FUNC_BEGIN + 19)	//向后引用
//逻辑函数											//2224
#define SM_FUNC_IF			(SM_FUNC_BEGIN + 21)	//
#define SM_FUNC_ISDOWN		(SM_FUNC_BEGIN + 22)	//
#define SM_FUNC_ISEQUAL		(SM_FUNC_BEGIN + 23)	//
#define SM_FUNC_ISUP		(SM_FUNC_BEGIN + 24)	//
//算术函数											//2234
#define SM_FUNC_ABS			(SM_FUNC_BEGIN + 31)	//绝对值
#define SM_FUNC_BETWEEN		(SM_FUNC_BEGIN + 32)	//
#define SM_FUNC_CROSS		(SM_FUNC_BEGIN + 33)	//
#define SM_FUNC_LONGCROSS	(SM_FUNC_BEGIN + 34)	//
#define SM_FUNC_MAX			(SM_FUNC_BEGIN + 35)	//最大值
#define SM_FUNC_MIN			(SM_FUNC_BEGIN + 36)	//最小值
#define SM_FUNC_MOD			(SM_FUNC_BEGIN + 37)	//
#define SM_FUNC_NOT			(SM_FUNC_BEGIN + 38)	//
#define SM_FUNC_RANGE		(SM_FUNC_BEGIN + 39)	//
#define SM_FUNC_REVERSE		(SM_FUNC_BEGIN + 40)	//
#define SM_FUNC_SGN			(SM_FUNC_BEGIN + 41)	//
#define SM_FUNC_SUBSAMEDAY	(SM_FUNC_BEGIN + 42)	//同一天减
//数学函数											
#define SM_FUNC_DIV			(SM_FUNC_BEGIN + 49)	//
#define SM_FUNC_RAND		(SM_FUNC_BEGIN + 50)	//
#define SM_FUNC_ACOS		(SM_FUNC_BEGIN + 51)	////2254
#define SM_FUNC_ASIN		(SM_FUNC_BEGIN + 52)	//
#define SM_FUNC_ATAN		(SM_FUNC_BEGIN + 53)	//
#define SM_FUNC_CEILING		(SM_FUNC_BEGIN + 54)	//
#define SM_FUNC_COS			(SM_FUNC_BEGIN + 55)	//余弦
#define SM_FUNC_EXP			(SM_FUNC_BEGIN + 56)	//
#define SM_FUNC_FLOOR		(SM_FUNC_BEGIN + 57)	//
#define SM_FUNC_INTPART		(SM_FUNC_BEGIN + 58)	//
#define SM_FUNC_LN			(SM_FUNC_BEGIN + 59)	//
#define SM_FUNC_LOG			(SM_FUNC_BEGIN + 60)	//
#define SM_FUNC_POW			(SM_FUNC_BEGIN + 61)	//
#define SM_FUNC_SIN			(SM_FUNC_BEGIN + 62)	//正弦
#define SM_FUNC_SQRT		(SM_FUNC_BEGIN + 63)	//
#define SM_FUNC_TAN			(SM_FUNC_BEGIN + 64)	//
#define SM_FUNC_GZSY		(SM_FUNC_BEGIN + 65)	//求非最后付息周期的国债收益率公式
#define SM_FUNC_SYFX		(SM_FUNC_BEGIN + 66)	//求剩余国债付息次数
#define SM_FUNC_XCFX		(SM_FUNC_BEGIN + 67)	//求国债下次付息日期

//统计函数											//
#define SM_FUNC_SKEW		(SM_FUNC_BEGIN + 69)	//分布的偏斜度
#define SM_FUNC_KURT		(SM_FUNC_BEGIN + 70)	//数据集的峰值
#define SM_FUNC_AVEDEV		(SM_FUNC_BEGIN + 71)	//
#define SM_FUNC_DEVSQ		(SM_FUNC_BEGIN + 72)	//
#define SM_FUNC_FORCAST		(SM_FUNC_BEGIN + 73)	//
#define SM_FUNC_SLOPE		(SM_FUNC_BEGIN + 74)	//
#define SM_FUNC_STD			(SM_FUNC_BEGIN + 75)	//
#define SM_FUNC_STDP		(SM_FUNC_BEGIN + 76)	//
#define SM_FUNC_VAR			(SM_FUNC_BEGIN + 77)	//
#define SM_FUNC_VARP		(SM_FUNC_BEGIN + 78)	//
#define SM_FUNC_RELATE		(SM_FUNC_BEGIN + 79)	//相关系数
#define SM_FUNC_COVAR		(SM_FUNC_BEGIN + 80)	//协方差
//指标函数											//2284
#define SM_FUNC_COST		(SM_FUNC_BEGIN + 81)	//
#define SM_FUNC_PEAK		(SM_FUNC_BEGIN + 82)	//
#define SM_FUNC_PEAKBARS	(SM_FUNC_BEGIN + 83)	//
#define SM_FUNC_SAR			(SM_FUNC_BEGIN + 84)	//
#define SM_FUNC_SARTURN		(SM_FUNC_BEGIN + 85)	//
#define SM_FUNC_TROUGH		(SM_FUNC_BEGIN + 86)	//
#define SM_FUNC_TROUGHBARS	(SM_FUNC_BEGIN + 87)	//
#define SM_FUNC_WINNER		(SM_FUNC_BEGIN + 88)	//
#define SM_FUNC_ZIG			(SM_FUNC_BEGIN + 89)	//
#define SM_FUNC_PWINNER		(SM_FUNC_BEGIN + 90)	//远期获利比例
#define SM_FUNC_FLATZIG		(SM_FUNC_BEGIN + 92)	//
//													//2294
#define SM_FUNC_ISNULL		(SM_FUNC_BEGIN + 91)	//
//财务
#define SM_FUNC_LASTREP		(SM_FUNC_BEGIN + 94)	//取最近报表
#define SM_FUNC_REPDATE		(SM_FUNC_BEGIN + 95)	//取报表日期
#define SM_FUNC_GETREPTYPE	(SM_FUNC_BEGIN + 96)	//取报表类型
#define SM_FUNC_REP			(SM_FUNC_BEGIN + 97)	//取同期报表
#define SM_FUNC_YEARREP		(SM_FUNC_BEGIN + 98)	//取年报
#define SM_FUNC_MIDREP		(SM_FUNC_BEGIN + 99)	//取中报
#define SM_FUNC_QUARTERREP	(SM_FUNC_BEGIN + 100)	//取季报
//时间函数											//2304
#define SM_FUNC_FORMATTIME		(SM_FUNC_BEGIN + 101)	//
#define SM_FUNC_VALIDBEGINTIME	(SM_FUNC_BEGIN + 102)	//起始时间
#define SM_FUNC_VALIDENDTIME	(SM_FUNC_BEGIN + 103)	//终止时间
#define SM_FUNC_BARPOS			(SM_FUNC_BEGIN + 104)	//K线位置
#define SM_FUNC_FROMNIGHT		(SM_FUNC_BEGIN + 106)	//
#define SM_FUNC_FROMOPEN		(SM_FUNC_BEGIN + 107)	//
#define SM_FUNC_TRADETIME		(SM_FUNC_BEGIN + 108)	//总开盘时间
#define SM_FUNC_COUNTTIME		(SM_FUNC_BEGIN + 109)	//
//复权													//2313
#define SM_FUNC_FUQUAN			(SM_FUNC_BEGIN + 110)	//复权
#define SM_FUNC_FUQUAN_ADVANCE	(SM_FUNC_BEGIN + 110)	//高级复权
#define SM_FUNC_FUQUAN_BACK		(SM_FUNC_BEGIN + 111)	//向后复权
#define SM_FUNC_FUQUAN_FOREWARD	(SM_FUNC_BEGIN + 112)	//向前复权
#define IS_FUNC_FUQUAN(x)		((x)>=SM_FUNC_FUQUAN && (x)<=SM_FUNC_FUQUAN_FOREWARD)
//
#define SM_FUNC_CM				(SM_FUNC_BEGIN + 113)	//成本分布
#define SM_FUNC_PERPRICE		(SM_FUNC_BEGIN + 114)	//分价
//
#define SM_FUNC_GROUPDATA		(SM_FUNC_BEGIN + 116)	//取相关代码数据项统计值
#define SM_FUNC_PLACEOFSORT		(SM_FUNC_BEGIN + 117)	//取数据项排名位置
#define SM_FUNC_INDEXDATA		(SM_FUNC_BEGIN + 118)	//取大盘数据项
//板块指数														//2323
#define SM_FUNC_BLOCKINDEX		(SM_FUNC_BEGIN + 120)	//板块指数计算
#define SM_FUNC_BLOCKSUM		(SM_FUNC_BEGIN + 121)	//板块求和
#define SM_FUNC_BLOCKMAX		(SM_FUNC_BEGIN + 122)	//板块最大值
#define SM_FUNC_BLOCKMIN		(SM_FUNC_BEGIN + 123)	//板块最小值
#define SM_FUNC_BLOCKAVG		(SM_FUNC_BEGIN + 124)	//板块平均
#define SM_FUNC_BLOCKSTD		(SM_FUNC_BEGIN + 125)	//板块标准差
#define SM_FUNC_BLOCKCOUNT		(SM_FUNC_BEGIN + 126)	//取板块股票数
#define SM_FUNC_BLOCKLEAD		(SM_FUNC_BEGIN + 129)	//取板块领先股票数据项
#define SM_FUNC_BLOCKDATA		(SM_FUNC_BEGIN + 130)	//板块统计
//
#define SM_FUNC_PERIODNAME		(SM_FUNC_BEGIN + 140)	//取当前周期名称
#define SM_FUNC_INBLOCK			(SM_FUNC_BEGIN + 141)	//判断当前代码是否属于某板块
#define SM_FUNC_BROKERINFO		(SM_FUNC_BEGIN + 142)	//取港股券商编号信息
//兼容分析家函数
#define SM_FUNC_RGB				(SM_FUNC_BEGIN + 148)	//RGB颜色
#define SM_FUNC_STRIP			(SM_FUNC_BEGIN + 149)	//渐变色
#define SM_FUNC_DYNAINFO		(SM_FUNC_BEGIN + 150)	//取实时行情
#define SM_FUNC_FINANCE			(SM_FUNC_BEGIN + 151)	//取财务数据
#define SM_FUNC_DRAWICON		(SM_FUNC_BEGIN + 152)	//画图标
#define SM_FUNC_DRAWLINE		(SM_FUNC_BEGIN + 153)	//画直线
#define SM_FUNC_DRAWTEXT		(SM_FUNC_BEGIN + 154)	//画文字
#define SM_FUNC_POLYLINE		(SM_FUNC_BEGIN + 155)	//画折线
#define SM_FUNC_STICKLINE		(SM_FUNC_BEGIN + 156)	//画柱线
#define SM_FUNC_DRAWBMP			(SM_FUNC_BEGIN + 157)	//画位图
#define SM_FUNC_DRAWGBK			(SM_FUNC_BEGIN + 158)	//条件填充背景
#define SM_FUNC_DRAWGBKLAST		(SM_FUNC_BEGIN + 159)	//最后条件填充背景
#define SM_FUNC_FILLRGN			(SM_FUNC_BEGIN + 160)	//条件填充区域
#define SM_FUNC_PARTLINE		(SM_FUNC_BEGIN + 161)	//条件画线
#define SM_FUNC_TIPTEXT			(SM_FUNC_BEGIN + 162)	//提示文字
#define SM_FUNC_VERTLINE		(SM_FUNC_BEGIN + 163)	//画垂直线
#define SM_FUNC_ZIGLINE			(SM_FUNC_BEGIN + 164)	//画锯齿线
#define SM_FUNC_HORLINE			(SM_FUNC_BEGIN + 165)	//画水平线
#define SM_FUNC_DWAWOWNER		(SM_FUNC_BEGIN + 166)	//自定绘图格式
#define SM_FUNC_ANGLELINE		(SM_FUNC_BEGIN + 167)	//角度线
#define SM_FUNC_DRAWWATERMARK	(SM_FUNC_BEGIN + 168)	//最后条件填充背景
//
#define SM_FUNC_INDEXO			(SM_FUNC_BEGIN + 170)	//大盘开盘价
#define SM_FUNC_INDEXC			(SM_FUNC_BEGIN + 171)	//大盘收盘价
#define SM_FUNC_INDEXH			(SM_FUNC_BEGIN + 172)	//大盘最高价
#define SM_FUNC_INDEXL			(SM_FUNC_BEGIN + 173)	//大盘最低价
#define SM_FUNC_INDEXV			(SM_FUNC_BEGIN + 174)	//大盘成交量
#define SM_FUNC_INDEXM			(SM_FUNC_BEGIN + 175)	//大盘成交量
//字符串函数
#define SM_FUNC_STRFIND			(SM_FUNC_BEGIN + 180)	//字符串查找
#define SM_FUNC_STRLEFT			(SM_FUNC_BEGIN + 181)	//字符串左部
#define SM_FUNC_STRMID			(SM_FUNC_BEGIN + 182)	//字符串中部
#define SM_FUNC_STRRIGHT		(SM_FUNC_BEGIN + 183)	//字符串右部
#define SM_FUNC_TOSTRING		(SM_FUNC_BEGIN + 184)	//转换成字符串
#define SM_FUNC_STKNAME			(SM_FUNC_BEGIN + 185)	//股票名称
//"麒麟短线王"独具特色的不传之秘
#define SM_FUNC_QL_SQZD			(SM_FUNC_BEGIN + 200)	//神奇涨跌趋势
//农历转换
#define SM_FUNC_SOLARTERM		(SM_FUNC_BEGIN + 201)	//节气
#define SM_FUNC_LUNARDATE		(SM_FUNC_BEGIN + 202)	//农历
//日期函数
#define SM_FUNC_DATE			(SM_FUNC_BEGIN + 203)
#define SM_FUNC_YEAR			(SM_FUNC_BEGIN + 204)
#define SM_FUNC_MONTH			(SM_FUNC_BEGIN + 205)
#define SM_FUNC_DAY				(SM_FUNC_BEGIN + 206)
#define SM_FUNC_HOUR			(SM_FUNC_BEGIN + 207)
#define SM_FUNC_MINUTE			(SM_FUNC_BEGIN + 208)
#define SM_FUNC_TIME			(SM_FUNC_BEGIN + 209)
#define SM_FUNC_WEEKDAY			(SM_FUNC_BEGIN + 210)

#define SM_FUNC_WARRANTCALC		(SM_FUNC_BEGIN + 211)
//
#define SM_FUNC_STAT_BUYVOL			(SM_FUNC_BEGIN + 212)	//买入大单成交量 
#define SM_FUNC_STAT_BUYCOUNT		(SM_FUNC_BEGIN + 213)	//买入大单个数 
#define SM_FUNC_STAT_SELLVOL		(SM_FUNC_BEGIN + 214)	//卖出大单成交量 
#define SM_FUNC_STAT_SELLCOUNT		(SM_FUNC_BEGIN + 215)	//卖出大单个数 
//
#define SM_FUNC_UPPERPRICE		(SM_FUNC_BEGIN + 216)	//涨停价格
#define SM_FUNC_LOWERPRICE		(SM_FUNC_BEGIN + 217)	//跌停价格
#define SM_FUNC_BONDYIELD		(SM_FUNC_BEGIN + 219)	//收益率

#define SM_FUNC_ISLASTBAR		(SM_FUNC_BEGIN + 220)	//是否是最后一个周期
//修改局部变量
#define SM_FUNC_SETVALUE		(SM_FUNC_BEGIN + 221)	//设置历史和未来的某个值

#define SM_FUNC_BONDMACDISCRETE	(SM_FUNC_BEGIN + 222)	//麦式久期K线
#define SM_FUNC_BONDPRICE		(SM_FUNC_BEGIN + 223)	//全价
#define SM_FUNC_REMAINPERIOD	(SM_FUNC_BEGIN + 224)	//剩余期限225-227，iFinD预留
#define SM_FUNC_BONDVALUE		(SM_FUNC_BEGIN + 228)	//纯债价值 
//gyk通达信函数定义
//引用函数
#define SM_FUNC_TMA		        (SM_FUNC_BEGIN + 230)	//TMA移动平均
#define SM_FUNC_TR		        (SM_FUNC_BEGIN + 231)	//真实波幅
#define SM_FUNC_DRAWNULL	    (SM_FUNC_BEGIN + 232)	//无效数
#define SM_FUNC_CURRBARSCOUNT	(SM_FUNC_BEGIN + 105)	//到最后交易日的周期数：和客户端保持一致
#define SM_FUNC_TOTALBARSCOUNT	(SM_FUNC_BEGIN + 234)	//总的周期数
#define SM_FUNC_BARSNSINCE		(SM_FUNC_BEGIN + 235)	//N周期内首个条件成立位置
#define SM_FUNC_BARSLASTCOUNT	(SM_FUNC_BEGIN + 236)	//条件连续成立次数
#define SM_FUNC_HOD		        (SM_FUNC_BEGIN + 237)	//高值名次
#define SM_FUNC_LOD		        (SM_FUNC_BEGIN + 238)	//低值名次
#define SM_FUNC_REFV		    (SM_FUNC_BEGIN + 239)	//引用若干周期前的数据(未作平滑处理),按REF实现
#define SM_FUNC_REFXV		    (SM_FUNC_BEGIN + 240)	//引用若干周期后的数据(平滑处理)
#define SM_FUNC_REFDATE		    (SM_FUNC_BEGIN + 241)	//指定引用
#define SM_FUNC_FILTERX		    (SM_FUNC_BEGIN + 242)	//反向过滤
#define SM_FUNC_TFILTER		    (SM_FUNC_BEGIN + 243)	//交易信号过滤：过滤连续出现的交易信号???
#define SM_FUNC_TTFILTER		(SM_FUNC_BEGIN + 244)	//过滤多空交易信号???
#define SM_FUNC_MEMA		    (SM_FUNC_BEGIN + 245)	//平滑移动平均
#define SM_FUNC_EXPMA		    (SM_FUNC_BEGIN + 246)	//指数移动平均
#define SM_FUNC_EXPMEMA		    (SM_FUNC_BEGIN + 247)	//指数平滑移动平均,别名实现，即EMA
#define SM_FUNC_XMA		        (SM_FUNC_BEGIN + 248)	//偏移移动平均
#define SM_FUNC_CONST		    (SM_FUNC_BEGIN + 249)	//取值设为常数
#define SM_FUNC_TOPRANGE		(SM_FUNC_BEGIN + 250)	//当前值是近多少周期内的最大值
#define SM_FUNC_LOWRANGE		(SM_FUNC_BEGIN + 251)	//当前值是近多少周期内的最小值
#define SM_FUNC_FINDHIGH		(SM_FUNC_BEGIN + 252)	//寻找指定周期内的特定最大值
#define SM_FUNC_FINDHIGHBARS	(SM_FUNC_BEGIN + 253)	//寻找指定周期内的特定最大值到当期周期的周期数
#define SM_FUNC_FINDLOW		    (SM_FUNC_BEGIN + 254)	//寻找指定周期内的特定最小值
#define SM_FUNC_FINDLOWBARS		(SM_FUNC_BEGIN + 255)	//寻找指定周期内的特定最小值到当期周期的周期数

//逻辑函数
#define SM_FUNC_UPNDAY          (SM_FUNC_BEGIN + 260)   //连涨N天
#define SM_FUNC_DOWNNDAY        (SM_FUNC_BEGIN + 261)   //连跌N天
#define SM_FUNC_NDAY            (SM_FUNC_BEGIN + 262)   //连续N天存在X>Y
#define SM_FUNC_EXIST           (SM_FUNC_BEGIN + 263)   //N天内存在条件满足
#define SM_FUNC_EVERY           (SM_FUNC_BEGIN + 264)   //N天内一直存在条件满足
#define SM_FUNC_LAST            (SM_FUNC_BEGIN + 265)   //持续存在
#define SM_FUNC_TESTSKIP        (SM_FUNC_BEGIN + 266)   //是否就此返回
//算术函数
#define SM_FUNC_IFN             (SM_FUNC_BEGIN + 267)   //逻辑判断
//数学函数
#define SM_FUNC_FRACPART        (SM_FUNC_BEGIN + 268)   //去变量小数部分
#define SM_FUNC_ROUND           (SM_FUNC_BEGIN + 269)   //返回整数的数值
#define SM_FUNC_SIGN            (SM_FUNC_BEGIN + 270)   //返回符号
//时间函数
#define SM_FUNC_TFILT           (SM_FUNC_BEGIN + 271)   //对指定时间段数据进行过滤
#define SM_FUNC_DATETODAY       (SM_FUNC_BEGIN + 272)   //指定到1990.12.19的天数
#define SM_FUNC_DAYTODATE       (SM_FUNC_BEGIN + 273)   //求1990.12.19后第若干天的日期
#define SM_FUNC_TIMETOSEC       (SM_FUNC_BEGIN + 274)   //求指定时刻距离0时有多长
#define SM_FUNC_SECTOTIME       (SM_FUNC_BEGIN + 275)   //求0时后若干秒是什么时间
//财务数据
#define SM_FUNC_TOTALCAPITAL    (SM_FUNC_BEGIN + 276)   //当前总股本
#define SM_FUNC_CAPITAL		    (SM_FUNC_BEGIN + 277)	//流通股本(手)
//行情函数
#define SM_FUNC_ISBUYORDER		    (SM_FUNC_BEGIN + 280)	//主动性买单
#define SM_FUNC_ISSELLORDER		    (SM_FUNC_BEGIN + 281)	//被动性卖单
#define SM_FUNC_DCLOSE		    (SM_FUNC_BEGIN + 282)	//下一个收盘价之字转向的收盘价
#define SM_FUNC_DOPEN		    (SM_FUNC_BEGIN + 283)	//至下一个收盘价的之字转向间的第一个开盘价
#define SM_FUNC_DHIGH		    (SM_FUNC_BEGIN + 284)	//至下一个收盘价的之字转向间的最高价
#define SM_FUNC_DLOW		    (SM_FUNC_BEGIN + 285)	//至下一个收盘价的之字转向间的最低价
#define SM_FUNC_DVOL		    (SM_FUNC_BEGIN + 286)	//至下一个收盘价的之字转向间的累积量*100
#define SM_FUNC_NAMELIKE		    (SM_FUNC_BEGIN + 287)	//模糊股票名称
#define SM_FUNC_CODELIKE		    (SM_FUNC_BEGIN + 288)	//模糊股票代码

#define SM_FUNC_END			(SM_FUNC_BEGIN + 300)		//函数定义结束

// 内部函数扩展
#define SM_EXT_FUNC_BEGIN             0x00010000 + SM_FUNC_BEGIN

#define SM_EXT_FUNC_DRAWTEXTABS       (SM_EXT_FUNC_BEGIN + 1)	            //绝对位置显示文字
#define SM_EXT_FUNC_DRAWTEXTREL       (SM_EXT_FUNC_BEGIN + 2)	            //相对位置显示文字
#define SM_EXT_FUNC_DRAWRECTABS       (SM_EXT_FUNC_BEGIN + 3)	            //绝对位置画矩形
#define SM_EXT_FUNC_DRAWRECTREL       (SM_EXT_FUNC_BEGIN + 4)	            //相对位置画矩形
#define SM_EXT_FUNC_DRAWFLAGTEXT      (SM_EXT_FUNC_BEGIN + 5)	            //浮动文字
#define SM_EXT_FUNC_FLOATRGN          (SM_EXT_FUNC_BEGIN + 6)	            //浮动填充区域
#define SM_EXT_FUNC_FLOATSTICK        (SM_EXT_FUNC_BEGIN + 7)	            //浮动柱状线
#define SM_EXT_FUNC_PERCENTBAR        (SM_EXT_FUNC_BEGIN + 8)	            //绘制纵向百分比柱
#define SM_EXT_FUNC_HORPERCNETBAR     (SM_EXT_FUNC_BEGIN + 9)	            //绘制横向百分比柱
#define SM_EXT_FUNC_DYNAMICICON       (SM_EXT_FUNC_BEGIN + 10)	            //绘制动态图标
#define SM_EXT_FUNC_DRAWCIRCLE        (SM_EXT_FUNC_BEGIN + 11)	            //绘制圆

#define SM_EXT_FUNC_FILLRECT          (SM_EXT_FUNC_BEGIN + 12)	            //矩形
#define SM_EXT_FUNC_RADIALLINE        (SM_EXT_FUNC_BEGIN + 13)	            //射线
#define SM_EXT_FUNC_REGRESSION        (SM_EXT_FUNC_BEGIN + 14)	            //回归线
#define SM_EXT_FUNC_REGRESSIONCHNL    (SM_EXT_FUNC_BEGIN + 15)	            //回归通道线
#define SM_EXT_FUNC_EQLPERIOD         (SM_EXT_FUNC_BEGIN + 16)	            //等周期线
#define SM_EXT_FUNC_FIBONACCICYCLE    (SM_EXT_FUNC_BEGIN + 17)	            //斐波那契周期线
#define SM_EXT_FUNC_LUCASCYCLE        (SM_EXT_FUNC_BEGIN + 18)	            //卢卡斯周期线
#define SM_EXT_FUNC_VERGOLDEN         (SM_EXT_FUNC_BEGIN + 19)	            //垂直黄金分割线
#define SM_EXT_FUNC_PERCENTAGE        (SM_EXT_FUNC_BEGIN + 20)	            //调整百分比线
#define SM_EXT_FUNC_HORGOLDLINE       (SM_EXT_FUNC_BEGIN + 21)	            //水平黄金分割线
#define SM_EXT_FUNC_HORPARALLE        (SM_EXT_FUNC_BEGIN + 22)	            //水平平行线
#define SM_EXT_FUNC_GOLDCIRCLES       (SM_EXT_FUNC_BEGIN + 23)	            //黄金分割同心圆
#define SM_EXT_FUNC_HELIX             (SM_EXT_FUNC_BEGIN + 24)	            //螺旋线
#define SM_EXT_FUNC_GANNBOX           (SM_EXT_FUNC_BEGIN + 25)	            //江恩箱
#define SM_EXT_FUNC_ELLIPSE           (SM_EXT_FUNC_BEGIN + 26)	            //椭圆
#define SM_EXT_FUNC_GANNLINE          (SM_EXT_FUNC_BEGIN + 27)	            //上下甘氏线

#define SM_EXT_FUNC_END               SM_EXT_FUNC_BEGIN + 300

//
//用户自定义
#define SM_USERS_BEGIN		(SM_FUNC_END + 1)			//用户自定义开始

#define SM_USERS_EXTERN		(SM_USERS_BEGIN + 1)		//自定义函数

#define SM_USERS_END		(SM_USERS_BEGIN + 1000)		//用户自定义结束

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//文本信息ID定义
#define SM_TEXT_BEGIN				(SM_USERS_END + 1)		//文本信息ID定义开始(3505)

#define SM_TEXT_STARTUP				(SM_TEXT_BEGIN + 0)		//起始页面

#define	SM_TEXT_EXCHANGENEWS		(SM_TEXT_BEGIN + 1)		//交易所新闻
#define	SM_TEXT_EXCHANGEBULLETIN	(SM_TEXT_BEGIN + 2)		//交易所公告
#define	SM_TEXT_JOBBERINFO			(SM_TEXT_BEGIN + 3)		//券商信息
#define	SM_TEXT_JOBBERBULLETIN		(SM_TEXT_BEGIN + 4)		//券商公告
#define	SM_TEXT_JOBBERWEB			(SM_TEXT_BEGIN + 5)		//券商网站
#define SM_TEXT_POPMSG				(SM_TEXT_BEGIN + 6)		//紧急公告
#define SM_TEXT_ROLLMSG				(SM_TEXT_BEGIN + 7)		//滚动公告

#define	SM_TEXT_STOCKINFO			(SM_TEXT_BEGIN + 11)	//个股资料
#define	SM_TEXT_STOCKREVIEW			(SM_TEXT_BEGIN + 12)	//个股每日评论
#define	SM_TEXT_CORPNEWS			(SM_TEXT_BEGIN + 13)	//公司新闻
#define	SM_TEXT_CORPBULLETIN		(SM_TEXT_BEGIN + 14)	//公司公告
#define	SM_TEXT_STOCKREAL			(SM_TEXT_BEGIN + 15)	//个股实时评论
#define	SM_TEXT_STOCKHQ				(SM_TEXT_BEGIN + 16)	//个股行情
#define SM_TEXT_COMPANYWEB			(SM_TEXT_BEGIN + 17)	//公司网站
#define SM_TEXT_DEFAULTLSZX			(SM_TEXT_BEGIN + 18)	//默认个股历史资讯
#define SM_TEXT_DEFAULTFSZX			(SM_TEXT_BEGIN + 19)	//默认个股分时资讯

#define	SM_TEXT_NEWSCENTER			(SM_TEXT_BEGIN + 21)	//新闻中心
#define	SM_TEXT_TODAYNEWS			(SM_TEXT_BEGIN + 22)	//今日导读
#define	SM_TEXT_ONLINEASK			(SM_TEXT_BEGIN + 23)	//在线咨询
#define	SM_TEXT_STATFORM			(SM_TEXT_BEGIN + 24)	//统计报表
#define	SM_TEXT_RESEARCHREPORT		(SM_TEXT_BEGIN + 25)	//研究报告
#define	SM_TEXT_TRADEANALYSIS		(SM_TEXT_BEGIN + 26)	//行业分析
#define	SM_TEXT_TRADEBULLETIN		(SM_TEXT_BEGIN + 27)	//行业分析
#define	SM_TEXT_POLICY				(SM_TEXT_BEGIN + 28)	//政策法规
#define	SM_TEXT_KNOWLEDGE			(SM_TEXT_BEGIN + 29)	//证券知识

#define SM_TEXT_RUBBISH				(SM_TEXT_BEGIN + 44)	//板块升级 3549
#define SM_TEXT_COMMMINE			(SM_TEXT_BEGIN + 45)	//通用历史信息地雷
#define SM_TEXT_MINMINE				(SM_TEXT_BEGIN + 46)	//通用分时信息地雷
#define SM_TEXT_POPIE				(SM_TEXT_BEGIN + 47)	//板块升级 3552
#define SM_TEXT_RUBBISH2			(SM_TEXT_BEGIN + 48)	//板块升级 3553	--老版本还会使用
#define SM_TEXT_STOCKBLOCK			(SM_TEXT_BEGIN + 49)	//板块升级 3554
#define SM_TEXT_MINECOUNT			(SM_TEXT_BEGIN + 50)	//信息地雷数目

#define SM_TEXT_END					(SM_TEXT_BEGIN + 100)	//文本信息ID定义结束

#define IS_COMMMINE(a)				(((a) == SM_TEXT_COMMMINE)|| ((a) == SM_TEXT_MINMINE))

/////////////////////////////////////////////////////////////////////////////
#define SF_GETTYPE(x)	(LOWORD(SF_ITEM(x))&~SF_USERDEFINE)

#define _ISHQ(x)				(x >= SM_HQ_BEGIN && x <= SM_HQ_END) 
#define _ISFIN_REAL(x)			((x >= CJ_REAL_BEGIN1 && x <= CJ_REAL_END1) || (x >= CJ_REAL_BEGIN2 && x <= CJ_REAL_END2))
#define _ISFINANCE(x)			(x >= SM_FD_BEGIN	&& x < SM_FD_END)
#define _ISSYS(x)				(x >= SM_FUNC_BEGIN && x < SM_FUNC_END) 
#define _ISEXTERN(x)			(x >= SM_USERS_BEGIN && x < SM_USERS_END)
#define _ISCALC(x)				(x >= SM_FUNC_BEGIN && x < SM_USERS_END) 
#define _ISTEXT(x)				(x >= SM_TEXT_BEGIN	&& x < SM_TEXT_END)
#define _ISBASEEXTRATYPE(x)		(x == SM_HQ_PREVCLOSE || x == SM_HQ_5DAYVOL || x == SM_HQ_SETTLE || x == SM_HQ_SYL)
#define _ISFINTEXTZC(x)			(_ISFINANCE(x) || _ISTEXT(x))
#define _ISEXTRATYPE(x)			(_ISFINTEXTZC(x) || _ISBASEEXTRATYPE(x))
#define _ISCLIENTTYPE(x)		(x == SM_HQ_YVALUE || x == SM_HQ_YSTRVALUE || x == SM_HQ_CODETYPE || x == SM_HQ_MARKETTYPE  \
								 || x == SM_HQ_ZQMC || x == SM_HQ_CODE || x == SM_HQ_TIME)

#define _ISBIGTRADE(x)			((x >= SM_HQ_BIGBUYCOUNT1 && x <= SM_HQ_WAITSELLMONEY2) || (x >= SM_HQ_BIGBUYTICK3 && x <= SM_HQ_WAITSELLMONEY3))
#define _ISFREEBIGORDER(x)		(x >= SM_HQ_FREEBIGORDERTRADE && x <= SM_HQ_FREEBIGORDERVALUE)

/*把宏改成 inline 函数，提高速度*/
inline BOOL SF_ISHQ(DWORD x)
{
	x = SF_GETTYPE(x);
	return _ISHQ(x);
}

inline BOOL SF_ISFIN_REAL(DWORD x) 
{
	x = SF_GETTYPE(x);
	return _ISFIN_REAL(x);
}

inline BOOL SF_ISFINANCE(DWORD x) 
{
	x = SF_GETTYPE(x);
	return _ISFINANCE(x);
}

inline BOOL SF_ISSYS(DWORD x)
{
	x = SF_GETTYPE(x);
	return _ISSYS(x);
}

inline BOOL SF_ISEXTERN(DWORD x)
{
	x = SF_GETTYPE(x);
	return _ISEXTERN(x);
}

inline BOOL SF_ISCALC(DWORD x)
{
	x = SF_GETTYPE(x);
	return _ISCALC(x);
}
inline BOOL SF_ISTEXT(DWORD x)
{
	x = SF_GETTYPE(x);
	return _ISTEXT(x);
}

inline BOOL SF_ISDRAWID(DWORD x)
{
	if(SF_INST(x)==SF_INST_MASK)
	{
		return SF_ISEXTERN(x);
	}
	return FALSE;
}

inline BOOL SF_ISSYSCALC(DWORD x)
{
	return (!SF_ISUSERDEFINE(x) && SF_ISCALC(x));
}

inline BOOL SF_ISSELECT(DWORD x)
{
	if(x & SF_MARK_SELECT)
	{
		return SF_ISEXTERN(x);
	}
	return FALSE;
}

inline BOOL SF_ISBASETYPE(DWORD x)
{
	x = SF_GETTYPE(x);
	return (_ISHQ(x) || _ISFINANCE(x) || _ISTEXT(x));
}

inline BOOL SF_ISBASEEXTRATYPE(DWORD x)
{
	x = SF_GETTYPE(x);
	return _ISBASEEXTRATYPE(x);
}
	                            
inline BOOL SF_ISFINTEXTZC(DWORD x)
{
	x = SF_GETTYPE(x);
	return _ISFINTEXTZC(x);
}

inline BOOL SF_ISEXTRATYPE(DWORD x)
{
	x = SF_GETTYPE(x);
	return _ISEXTRATYPE(x);
}

inline BOOL SF_ISCLIENTTYPE(DWORD x)
{
	x = SF_GETTYPE(x);
	return _ISCLIENTTYPE(x);
}

#define SF_GROUP_MARSK	0x1FFF0000
inline BOOL SF_ISGROUP(DWORD x)
{
	return ((x & SF_GROUP_MARSK) == SF_GROUP_MARSK || x == 0);
}

inline BOOL SF_ISOTHERHQ(DWORD x)
{
	x = SF_ITEM(x);
	return (_ISBIGTRADE(x) || _ISFREEBIGORDER(x));
}
inline DWORD SF_GETGROUPID(DWORD x)
{
	if(x == 0)
	{
		return 0;
	}
	x = SF_GETTYPE(x);
	DWORD dw = 0;
	if(_ISHQ(x))
	{
		dw = SM_HQ_BEGIN;
	}
	else if(_ISSYS(x))
	{
		dw = SM_HQ_BEGIN;
	}
	else if(SF_ISSELECT(x))
	{
		dw = SF_MARK_SELECT | SM_USERS_BEGIN;
	}
	else if(SF_ISUSERDEFINE(x) && _ISEXTERN(x))
	{
		dw = SF_USERDEFINE | SM_USERS_BEGIN;
	}
	else if(_ISEXTERN(x))
	{
		dw = SM_USERS_BEGIN;
	}
	else if(_ISFINANCE(x))
	{
		dw = SM_FD_BEGIN;
	}
	else if(_ISTEXT(x))
	{
		dw = SM_TEXT_BEGIN;
	}
	if(dw != 0)
	{
		dw |= SF_GROUP_MARSK;
	}
	return dw;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//大单数据的定义
#define BIG_BUY			0x00001000	//买入
#define BIG_SELL		0x00002000	//卖出
#define BIG_ACTIVE		0x00000100	//主动
#define BIG_PASSIVE		0x00000200	//被动
#define BIG_LEVEL1		0x00000010	//特大
#define BIG_LEVEL12		0x00000011	//特大（2）
#define BIG_LEVEL2		0x00000020	//大
#define BIG_LEVEL22		0x00000021	//大（2）
#define BIG_LEVEL3		0x00000030	//中
#define BIG_LEVEL32		0x00000031	//中（2）
#define BIG_LEVEL33		0x00000032	//中（3）
#define BIG_LEVEL4		0x00000040	//小

//根据大单类型，取大单的数据项目ID
int32 GetBigTradeID(int32 lBigType, DWORD& dwCount, DWORD& dwMoney, DWORD& dwTick);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma pack()
#endif //_INC_TYPEDEF_H

