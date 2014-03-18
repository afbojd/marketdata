
#ifndef _MARKETDEF_H
#define _MARKETDEF_H

//////////////////////////////////////////////////////////////////////////////////////////////
//
#define MC_MARKET(x)		(BYTE)(x & 0xF8)
#define MC_STOCK(x)			(BYTE)(x & 0x07)
#define MAX_TYPE_STOCK		8

//////////////////////////////////////////////////////////////////////////////////////////////
//!市场代码定义
#define SH_MARKET			(BYTE)0x10	//上证
#define SZ_MARKET			(BYTE)0x20	//深证
#define THS_MARKET			(BYTE)0x30	//同花顺指数
#define QT_MARKET			(BYTE)0x40	//国内期货(1-上海、2-大连、3-郑州、4-桂糖、5-郑粮、6-中国商品)
#define BOCE_MARKET			(BYTE)0x50	//渤海期货
#define FX_MARKET			(BYTE)0x60	//外汇(美汇)
#define HZ_MARKET			(BYTE)0x70	//香港期货(香港期交所)
#define CFF_MARKET			(BYTE)0x80	//中国金融期货
#define STB_MARKET			(BYTE)0x90	//三板市场
#define TJWJS_MARKETA		(BYTE)0xA0	//天津文交所市场
#define HK_MARKET			(BYTE)0xB0	//香港证券(香港联交所)
#define OTC_MARKET			(BYTE)0xC0	//券商OTC行情
#define BI_MARKET			(BYTE)0xD0	//自定义市场（板块指数）
#define INVALID_MARKETE		(BYTE)0xE0	//无效 快捷键操作代码
#define INVALID_MARKETF		(BYTE)0xF0	//无效 股票分类代码
#define INDX_MARKET			(BYTE)0x18	//同花顺指数
#define INVALID_MARKET1		(BYTE)0x28	//无效
#define INVALID_MARKET2		(BYTE)0x38	//无效 ;
#define SSEBOND_MARKET		(BYTE)0x48	//上证固定收益交易平台
#define FXINDX_MARKET		(BYTE)0x58	//外盘指数
#define SWINDEX_MARKET		(BYTE)0x68	//申万指数
#define ZZINDEX_MARKET		(BYTE)0x78	//中证指数
#define IFIND_MARKET		(BYTE)0x88	//IFIND市场行情
#define VALID_MARKET4		(BYTE)0x98	//可用市场代码
#define NYSE_MARKET			(BYTE)0xA8	//纽约交易所(股票)
#define NSDQ_MARKET			(BYTE)0xB8	//纳斯达克
#define US_MARKET			(BYTE)0xC8	//美国其它市场
#define COMEX_MARKET		(BYTE)0xD8	//芝加哥商品交易所
#define OPTIONS_MARKET		(BYTE)0xE8	//个股期权
#define BLOCK_MARKET		(BYTE)0xF8	//板块代码

//////////////////////////////////////////////////////////////////////////////////////////////
//!分类定义
#define MC_Index			(BYTE)0x00
#define MC_Stock			(BYTE)0x07

#define MC_StockA			(BYTE)0x01	//A股
#define MC_StockB			(BYTE)0x02	//B股
#define MC_Bond				(BYTE)0x03	//债券
#define MC_Fund				(BYTE)0x04	//基金
#define MC_Others			(BYTE)0x05	//其它
#define MC_StockQ			(BYTE)0x05	//将退市股票
#define MC_StockH			(BYTE)0x06	//深圳B专H股
#define MC_StockW			(BYTE)0x06	//上证风险警示板

#define MC_Futures			(BYTE)0x01	//期货
#define MC_Futures_SQ		(BYTE)0x01	//上海期货
#define MC_Futures_DQ		(BYTE)0x02	//大连期货
#define MC_Futures_ZQ		(BYTE)0x03	//郑州期货
#define MC_Futures_ZJ		(BYTE)0x04	//桂糖
#define MC_Futures_ZGM		(BYTE)0x05	//郑粮
#define MC_Futures_GD		(BYTE)0x06	//高达期货

#define BOCE_Futures		(BYTE)0x01	//渤海期货	mouyu

#define	MC_Foreign			(BYTE)0x01	//外汇
#define MC_BasedRate        (BYTE)0x01  //基本汇率
#define MC_CrossedRate      (BYTE)0x02  //交叉汇率
#define MC_ReverseRate      (BYTE)0x03  //反向汇率或其它汇率(除基本汇率、交叉汇率以外)
#define MC_FX_OPTION	    (BYTE)0x04  //外汇期权
#define MC_FX_OPTIONEXT     (BYTE)0x05  //外汇到期期权

#define MC_MainBoard		(BYTE)0x01	//主板
#define MC_GEM				(BYTE)0x02	//创业板
#define MC_Warrant			(BYTE)0x03	//认股证
#define MC_Trusts			(BYTE)0x04	//信托基金
#define MC_HKBond			(BYTE)0x05	//香港债券
#define MC_BullBear			(BYTE)0x06	//香港牛熊证

#define MC_Foreign_Index	(BYTE)0x01	//国外指数

#define MC_Index_Futures	(BYTE)0x01	//指数期货
#define MC_Stock_Futures	(BYTE)0x02	//股票期货
#define MC_HIBOR			(BYTE)0x03	//港元利率期货(Hong Kong Interback offered Rate)

#define MC_CFF_Index_Futures	(BYTE)0x01	//中金所指数期货
#define MC_CFF_Bond_Futures		(BYTE)0x02	//中金所国债期货

//NSDQ_MARKET
#define MC_NQNM             (BYTE)0x01  //NQNM 纳斯达克交易所
#define MC_NQSC             (BYTE)0x02  //NQSC 纳斯达克全球精选市场
#define MC_NQBB             (BYTE)0x03  //NQBB 纳斯达克公告牌
#define MC_NQPK             (BYTE)0x04  //NQPK 纳斯达克场外交易市场
#define MC_NQEX             (BYTE)0x05  //NQEX 纳斯达克资本市场

//NYSE_MARKET
#define MC_NYSE             (BYTE)0x01  //NYSE
#define MC_AMEX             (BYTE)0x02  //AMEX
#define MC_CBOE             (BYTE)0x03  //CBOE
#define MC_PACF             (BYTE)0x04  //PACF
#define MC_NYSEINDEX        (BYTE)0x05  //NYSE指数
#define MC_AMEXINDEX        (BYTE)0x06  //AMEX指数
#define MC_PACFINDEX        (BYTE)0x07  //PACF指数

//US_MARKET
#define MC_DOWJ             (BYTE)0x01  //DOWJ
#define MC_DOWJAMERTIME     (BYTE)0x02  //道琼斯指数美国部分 交易时间为9:30-16:00

//COME_MARKET
#define MC_NYMX             (BYTE)0x01  //NYMX


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//根据市场、周期等取文件类，创建市场文件或者数据池的数据结构

#define	FCF_PERIOD_MASK			0x0000FFFF			//周期

#define	FCF_MARKET_MASK				0x00FF0000			//市场 FCF_MARKET_*
#define	FCF_MARKET_STOCK			0x00000000			//股票
#define	FCF_MARKET_Futures			0x00010000			//期货
#define	FCF_MARKET_Foreign			0x00020000			//外汇
#define	FCF_MARKET_HK				0x00040000			//港股
#define	FCF_MARKET_BOND				0x00050000			//债券固定收益
#define	FCF_MARKET_US				0x00060000			//美股
#define	FCF_MARKET_GlobalFutures	0x00070000			//外盘期货
#define	FCF_MARKET_THSIndex			0x00080000			//同花顺指数
#define	FCF_MARKET_OPTIONS			0x00090000			//期权

#define	FCF_OPTION_MASK				0xFF000000			//选项 FCF_OPTION_*
#define	FCF_OPTION_INDEX			0x10000000			//指数，否则个股
#define	FCF_OPTION_TODAY			0x20000000			//实时数据文件
#define	FCF_OPTION_BASE				0x40000000			//使用基本成交明细文件
#define FCF_OPTION_LEVEL2			0x80000000			//level2数据格式


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//市场的属性

#define MOPS_24HS				0x00000001		//!是否是24小时交易的市场，采用不同的收盘方式、今日数据生成
#define MOPS_LEVEL2				0x00000002		//!是否支持Level2数据
#define MOPS_LNAME				0x00000004		//!是否支持长名称的市场
#define MOPS_MAIN				0x00000008		//!是否是统一时间（只有一个时间轴）的市场
#define MOPS_DUPTIME			0x00000010		//!是否允许时间重复（成交明细）
#define MOPS_US					0x00000020		//!是否为美国的市场
#define MOPS_NOINDEX			0x00000040		//!是否没有指数

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32  GetMarketOptions(uint32 uMarketCode, uint32 uMask);


inline BOOL is24HsExchange(uint32 uMarketCode)	
{
	return (GetMarketOptions(uMarketCode, MOPS_24HS) == MOPS_24HS);
}

inline BOOL IsLevel2Market(uint32 uMarketCode)			//!判断是否为支持level2的市场
{
	return (GetMarketOptions(uMarketCode, MOPS_LEVEL2) == MOPS_LEVEL2);
}

void SetLevel2Market(uint32 uMarketCode);				//设置level-2市场
///////////////////////////////////////////////////////////
//!判断是否为支持长名称的市场
inline BOOL IsLongNameMarket(uint32 uMarketCode)
{
	return (GetMarketOptions(uMarketCode, MOPS_LNAME) == MOPS_LNAME);
}

///////////////////////////////////////////////////////////
//!判断是否为统一时间的市场
inline BOOL IsMainTimeMarket(uint32 uMarketCode)
{
	return (GetMarketOptions(uMarketCode, MOPS_MAIN) == MOPS_MAIN);
}

//判断市场是否允许时间重复（成交明细）
inline bool IsDupTimeMarket(uint32 uMarketCode)
{
	return (GetMarketOptions(uMarketCode, MOPS_DUPTIME) == MOPS_DUPTIME);
}

///////////////////////////////////////////////////////////
//!判断是否为美国的市场
inline BOOL IsUSMarket(uint32 uMarketCode)
{
	return (GetMarketOptions(uMarketCode, MOPS_US) == MOPS_US);
}

//!根据市场代码，判断该市场的分类
void GetMarketTypeFromClass(uint32 uMarket, DWORD& dwOptions);

//!判断是否是开放式基金
BOOL IsOpenEndedFund(LPCTSTR lpszCode);		

//市场代码对应表
BYTE   GetMarketCodeOld(LPCTSTR lpszMarket);
uint32 GetMarketCodeNew(LPCTSTR lpszMarket);
LPCTSTR GetMarketString(uint32 uMarketCode);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//股票名称类型的定义
#define MK_STOCKNAME_NORMAL			0x0000			//正常显示的名称
#define MK_STOCKNAME_TRADE			0x0100			//交易代码
#define MK_STOCKNAME_ENGLISH		0x0200			//英文名称
#define MK_STOCKNAME_ALIAS			0x0300			//别名
#define MK_STOCKNAME_HISTORY		0x0400			//曾用名
#define MK_STOCKNAME_FULLNAME		0x0500			//全称

#define MK_STOCKNAME_TYPE_MASK		0xFF00			//名称类型的掩码
#define MK_STOCKNAME_INDEX_MASK		0x00FF			//相同类型个数的掩码

//股票名称类型的字符定义。正常显示的没有定义
const TCHAR  MK_C_STOCKNAME_NORMAL    = _T('n');	//正常显示的名称
const TCHAR  MK_C_STOCKNAME_TRADE     = _T('t');	//交易代码
const TCHAR  MK_C_STOCKNAME_ENGLISH   = _T('e');	//英文名称
const TCHAR  MK_C_STOCKNAME_ALIAS     = _T('a');	//别名
const TCHAR  MK_C_STOCKNAME_HISTORY   = _T('h');	//曾用名
const TCHAR  MK_C_STOCKNAME_FULLNAME  = _T('f');	//全称

WORD    GetStockNameTypeCode(LPCTSTR lpszType);					//根据字符串转换成类型代码
LPCTSTR GetStockNameTypeString(WORD wNameType, TCHAR* pszType);		//根据类型代码转换成字符串

//遍历股票名称的函数
//!函数原型 int32 func(LPCTSTR lpszCode, LPCTSTR lpszName, WORD wNameType, LPCTSTR lpszAbbr)
//!参数分别是 代码 名称 名称类型 简称
typedef fastdelegate::FastDelegate4<LPCTSTR, LPCTSTR, WORD, LPCTSTR, int32>	_funcStockName;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
新的代码规则（市场和分类）定义
1、市场分类代码由原来的 1 个字节扩充到 4 个字节
2、市场分类代码规则
   1）第一个字节：兼容字节，用于区分旧的定义。 固定为：U(0x55)
   2）第二 三 个字节：市场代码。必须是大写字母
   3）第四个字节：分类代码。必须是大小字母，不同的市场之间允许重复
3、证券代码规则：
   1）长度不限
   2）全部由可见字符组成（字母、数字、特殊字符等）
   3）大小写敏感
4、为了处理方便，市场分类代码使用 uint32 表示，字节序使用小端（little-endian）。

*/
 
//市场代码定义
const uint32 MARKET_SH	=  0x00485300;	//上海交易所						"SH"	
const uint32 MARKET_SZ	=  0x005A5300;	//深圳交易所						"SZ"
const uint32 MARKET_RF	=  0x00465200;	//同花顺指数						"RF"
const uint32 MARKET_CF	=  0x00464300;	//中国商品期货（上海、大连、郑州）	"CF"
const uint32 MARKET_BF	=  0x00464200;	//渤海期货							"BF"
const uint32 MARKET_FX	=  0x00584600;	//外汇								"FX"
const uint32 MARKET_HF	=  0x00464800;	//香港期货							"HF"
const uint32 MARKET_IF	=  0x00464900;	//中国金融期货						"IF"
const uint32 MARKET_ST	=  0x00545300;	//三板								"ST"
const uint32 MARKET_TW	=  0x00575400;	//天津文交所						"TW"
const uint32 MARKET_HK	=  0x004B4800;	//香港交易所						"HK"
const uint32 MARKET_OT	=  0x00544F00;	//券商OTC							"OT"
const uint32 MARKET_BI	=  0x00494200;	//客户端板块指数					"BI"
const uint32 MARKET_TI	=  0x00495400;	//同花顺指数（旧）					"TI"
const uint32 MARKET_FB	=  0x00424600;	//固定收益(Fixed Income)			"FB"
const uint32 MARKET_FI	=  0x00494600;	//外盘指数							"FI"
const uint32 MARKET_SW	=  0x00575300;	//申万指数							"SW"
const uint32 MARKET_ZZ	=  0x005A5A00;	//中证指数							"ZZ"
const uint32 MARKET_ID	=  0x00444900;	//IFinD市场							"ZZ"
const uint32 MARKET_NY	=  0x00594E00;	//纽约交易所						"NY"
const uint32 MARKET_NQ	=  0x00514E00;	//纳斯达克交易所					"NQ"
const uint32 MARKET_US	=  0x00535500;	//美国其他交易所					"US"
const uint32 MARKET_CM	=  0x004D4300;	//芝加哥商品						"CM"
const uint32 MARKET_IB	=  0x00424900;	//银行间市场						"IB"
const uint32 MARKET_SO	=  0x004F5300;	//上海期权							"SO"

const uint32 MARKET_UU	=  0x00555500;	//未知的市场						"UU"


//代码分类定义

//字符的定义

const uint32 CLASS_A = 0x41000000;		//A
const uint32 CLASS_B = 0x42000000;		//B
const uint32 CLASS_C = 0x43000000;		//C
const uint32 CLASS_D = 0x44000000;		//D
const uint32 CLASS_E = 0x45000000;		//E
const uint32 CLASS_F = 0x46000000;		//F
const uint32 CLASS_G = 0x47000000;		//G
const uint32 CLASS_H = 0x48000000;		//H
const uint32 CLASS_I = 0x49000000;		//I
const uint32 CLASS_J = 0x4A000000;		//J
const uint32 CLASS_L = 0x4C000000;		//L
const uint32 CLASS_M = 0x4D000000;		//M
const uint32 CLASS_N = 0x4E000000;		//N
const uint32 CLASS_O = 0x4F000000;		//O
const uint32 CLASS_P = 0x50000000;		//P
const uint32 CLASS_Q = 0x51000000;		//Q
const uint32 CLASS_R = 0x52000000;		//R
const uint32 CLASS_S = 0x53000000;		//S
const uint32 CLASS_T = 0x54000000;		//T
const uint32 CLASS_U = 0x55000000;		//U
const uint32 CLASS_W = 0x57000000;		//W
const uint32 CLASS_X = 0x58000000;		//X
const uint32 CLASS_Y = 0x59000000;		//Y
const uint32 CLASS_Z = 0x5A000000;		//Z


//所有的市场
#define NMC_Index				CLASS_I		//I	指数						0x00
#define NMC_Stock				CLASS_S		//S	股票						0x01
#define NMC_Others				CLASS_Z		//Z	其它，没有明确的分类

#define NMC_UNKNOWN				CLASS_U		//U	未知的，在不知道分类的情况下，用这个字符表示

//沪深（MARKET_SH 、MARKET_SZ）
#define NMC_StockA				CLASS_A		//A	A股							0x01
#define NMC_StockB				CLASS_B		//B	B股							0x02
#define NMC_Bond				CLASS_D		//D	债券						0x03
#define NMC_Fund				CLASS_J		//J	基金（和老版本兼容）		0x04
#define NMC_CEFund				CLASS_F		//F	封闭式基金
#define NMC_OEFund				CLASS_N		//N	开放式基金
#define NMC_ETF					CLASS_E		//E	ETF
#define NMC_LOF					CLASS_L		//L	LOF
#define NMC_DELIST				CLASS_P		//P	退市整理					0x05

//上证（MARKET_SH）
#define NMC_ST					CLASS_T		//T	上证风险警示板（ST）		0x06
#define NMC_OPTION				CLASS_O		//O	期权

//深证（MARKET_SZ）
#define NMC_B2H					CLASS_H		//H	深圳B转H股					0x06

//港股（MARKET_HK）
#define NMC_MainBoard			CLASS_M		//M 主板						0x01
#define NMC_GEM					CLASS_G		//G 创业板						0x02	
#define NMC_Warrant				CLASS_W		//W 认股证（权证）				0x03
#define NMC_Trusts				CLASS_T		//T 信托基金					0x04
#define NMC_HKBond				CLASS_D		//D 香港债券					0x05
#define NMC_BullBear			CLASS_B		//B 香港牛熊证					0x06

//国内期货（MARKET_CF）
#define NMC_Futures_SQ			CLASS_S		//S 上海期货					0x01
#define NMC_Futures_DQ			CLASS_D		//D 大连期货					0x02
#define NMC_Futures_ZQ			CLASS_Z		//Z 郑州期货					0x03
#define NMC_Futures_ZJ			CLASS_T		//T 桂糖						0x04
#define NMC_Futures_ZGM			CLASS_L		//L 郑粮						0x05
#define NMC_Futures_GD			CLASS_X		//X 高达期货					0x06

//渤海期货（MARKET_BF）
#define NMC_Futures_BOCE		CLASS_F		//F 渤海期货					0x01

//外汇（MARKET_FX）
#define NMC_BasedRate			CLASS_B		//B 基本汇率					0x01
#define NMC_CrossedRate			CLASS_C		//C 交叉汇率					0x02
#define NMC_ReverseRate			CLASS_R		//R 反向汇率或其它汇率(除基本汇率、交叉汇率以外)	0x03
#define NMC_FX_OPTION			CLASS_O		//O 外汇期权					0x04
#define NMC_FX_OPTIONEXT		CLASS_N		//N 外汇到期期权				0x05

//香港期货（MARKET_HF）
#define NMC_Index_Futures		CLASS_F		//F 指数期货					0x01
#define NMC_Stock_Futures		CLASS_S		//S 股票期货					0x02
#define NMC_HIBOR				CLASS_R		//R 港元利率期货(Hong Kong Interback offered Rate)	0x03

//中国金融期货（中金所）
#define NMC_CFF_Index_Futures	CLASS_F		//F 中金所指数期货				0x01
#define NMC_CFF_Bond_Futures	CLASS_B		//B	中金所国债期货				0x02

//纳斯达克（MARKET_NQ）
#define NMC_NQNM				CLASS_Q		//Q 纳斯达克交易所				0x01
#define NMC_NQSC				CLASS_S		//S 纳斯达克全球精选市场		0x02
#define NMC_NQBB				CLASS_B		//B 纳斯达克公告牌				0x03
#define NMC_NQPK				CLASS_P		//P 纳斯达克场外交易市场		0x04
#define NMC_NQEX				CLASS_E		//E 纳斯达克资本市场			0x05

//纽约交易所（MARKET_NY）
#define NMC_NYSE				CLASS_N		//N 纽约证券交易所（NYSE）		0x01
#define NMC_AMEX				CLASS_A		//A 美国证券交易所（AMEX）		0x02
#define NMC_CBOE				CLASS_C		//C 芝加哥期权交易所（CBOE）	0x03
#define NMC_PACF				CLASS_P		//P ？？						0x04
#define NMC_NYSEINDEX			CLASS_I		//I 纽约证券交易所指数			0x05
#define NMC_AMEXINDEX			CLASS_M		//M 美国证券交易所指数			0x06
#define NMC_PACFINDEX			CLASS_N		//N ？？指数					0x07

//美国其他交易所（MARKET_US）
#define NMC_DOWJ				CLASS_D		//D 道琼斯指数系列股票			0x01
#define NMC_DOWJAMERTIME		CLASS_A		//道琼斯指数美国部分 交易时间为9:30-16:00	0x02

//芝加哥商品交易所（MARKET_CM）
#define NMC_NYMX				CLASS_N		//N 纽约商品交易所（NYMX）		0x01

#define NMK_MASK				0x00FFFF00		//市场的掩码
#define NMK_CLASS				0xFF000000		//市场分类的掩码

inline uint32 NMC_MARKET(uint32 uMarket)
{
	if(uMarket & NMK_MASK)
	{
		return (uMarket & NMK_MASK);
	}
	else
	{
		return MC_MARKET((BYTE)uMarket);
	}
}

inline uint32 NMC_CLASS(uint32 uMarket)
{
	if(uMarket & NMK_CLASS)
	{
		return (uMarket & NMK_CLASS);
	}
	else
	{
		return MC_STOCK((BYTE)uMarket);
	}
}

#define NMK_NEW				_T('U')					//新版本的第一个字符。用于区分新老版本的格式
#define NMK_LEN				4						//市场代码的长度

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//外部需要的工具函数
#define M2N_OPS_MARKET		0x0001		//只是转换成新的市场，不考虑代码分类
namespace code
{
	//! 取输入代码字符串的市场代码
	/*!
	*\param  lpszCode	包含市场信息的代码字符串
	*\return 返回市场代码，不进行新老转换，即如果原来是老格式的字符串，就返回老的。
	*/
	uint32 GetMarket(LPCTSTR lpszCode);

	//! 取输入代码字符串的代码
	/*!
	*\param  lpszCode		包含市场信息的代码字符串
	*\return 返回不包含市场信息的字符串
	*/
	const wchar_t* GetCode(const wchar_t* lpszCode);
	const char* GetCode(const char* lpszCode);

	//! 取输入代码字符串的代码
	/*!
	*\param  lpszCode		包含市场信息的代码字符串
	*\param  uMarketCode	返回市场代码，不进行新老转换，即如果原来是老格式的字符串，就返回老的。
	*\return 返回不包含市场信息的字符串
	*/
	LPCTSTR GetCode(LPCTSTR lpszCode, uint32& uMarketCode);

	//! 合并市场和代码
	/*!
	*\param  uMarketCode	市场代码，支持新老格式的市场
	*\param  lpszCode		只有代码的字符串
	*\param  szCode			保存转换后的代码。
	*\param  nLength		szCode 的长度，必须保留结束符（\0）的位置。如果 lpszCode 太长会截断
	*\return 返回 szCode
	*\remarks 如果是老版本的市场代码，返回的字符串就是老版本的，否则是新版本的。
	*/
	LPCTSTR MergeCode(uint32 uMarketCode, LPCTSTR lpszCode, TCHAR* szCode, int32 nLength);

	//! 把老格式的市场转换成新格式
	/*!
	*\param  cMarket	老格式的市场
	*\param  uOptions	转换的属性，见定义：M2N_OPS_*
	*\return 如果转换失败，返回 0 ，否则返回转换后的市场代码
	*\remarks 
	*/
	uint32 Market2New(BYTE cMarket, uint32 uOptions);

	//! 把老格式的市场转换成新格式
	/*!
	*\param  uMarket	新老格式的市场
	*\param  uOptions	转换的属性，见定义：M2N_OPS_*
	*\return 如果转换失败，返回 0 ，否则返回转换后的市场代码
	*\remarks 如果是新格式的市场，直接返回
	*/
	uint32 Market2New(uint32 uMarket, uint32 uOptions);

	//! 比较两个市场
	/*!
	*\param  uMarket	市场代码，支持新老格式
	*\param  uCompare	参与比较的市场。必须是新的格式
	*\return 如果市场相同，返回 true 。否则返回 false
	*\remarks 
	*/
	bool IsMarket(uint32 uMarket, uint32 uCompare);

	//! 比较两个市场分类
	/*!
	*\param  uMarket	市场代码和分类，支持新老格式
	*\param  uCompare	参与比较的分类。必须是新的格式（NMC_*）
	*\return 如果分类相同，返回 true 。否则返回 false
	*\remarks 
	*/
	bool IsClass(uint32 uMarket, uint32 uCompare);

	//! 字符串转换成合法的代码字符串
	/*!
	*\param  lpszText	字符串。支持新老格式。比如 16 17  SH USH  USHA
	*\param  szCode		转换后的标准代码字符串。 老格式的变成：0x11 等 ，新格式的第一个字符为 U 
	*\return 返回市场占用的字符个数。老版本的返回 1 ，新版本根据不同情况返回 1 2 3 4
	*\remarks  
	*/
	int32 Str2Code(LPCTSTR lpszText, TCHAR* szCode);

	//! 字符串转换成合法的市场代码（uint32）
	/*!
	*\param  lpszText	字符串。支持新老格式。比如 16 17  SH USH  USHA
	*\return  合法的市场代码（包含分类）。可以是老格式的。
	*\remarks  
	*/
	uint32 Str2Market(LPCTSTR lpszText);

	//! 市场代码转换成字符串
	/*!
	*\param  uMarket	市场代码，支持新老格式
	*\param  szText		返回转换后的字符串。如果是老市场，转换成如 16 17 ，新市场转换成：USHA，如果没有分类，转换成 USH
	*\return  暂时没有定义
	*\remarks  szText 的长度必须足够，至少 5 个字符长度。
	*/
	int32 Market2Str(uint32 uMarket, TCHAR* szText);

	/*
		市场代码的数组，可以代替原来的固定长度的数组（如：BYTE cMarket[32]）
	*/
	class CMarketArray
	{
	public:
		CMarketArray();
		CMarketArray(uint32* pMarket, int32 nMarketCount);
		~CMarketArray();
	public:
		//! 在数组最后增加一个市场，返回数组的大小。
		int32 Add(uint32 uMarket);
		//! 在给定的位置 nPos 插入一个市场，返回数组的大小。如果 nPos < 0，则在数组最后增加一个市场。
		int32 Insert(uint32 uMarket, int32 nPos);

		//! 在数组最后增加多个市场，返回数组的大小。
		int32 Append(uint32* pMarket, int32 nMarketCount);
		//! 顺序查找，如果找到就不增加，返回 -1，否则在数组最后增加一个市场，返回数组的大小。
		int32 FindAdd(uint32 uMarket);

		//! 顺序查找，如果找到返回市场所在的索引值，否则返回 -1 。
		int32 Find(uint32 uMarket);
		
		//! 顺序查找，如果找到就删除这个市场，返回数组的大小，否则返回 -1 。
		int32 Remove(uint32 uMarket);
		//! 删除 nPos 位置的市场，如果 nPos 合法就删除，并返回数组的大小，否则返回 -1 。
		int32 RemoveAt(int32 nPos);

		//! 克隆函数
		void Clone(const CMarketArray& ayMarket);

		//! 判断数组是否为空
		bool IsEmpty();

		//! 返回市场数据的指针
		uint32* GetMarket();

		//! 返回数组的大小
		int32  GetSize();

		//! 设置数组的大小。如果 lNewSize <= 0 ，清空整个数组。如果 lNewSize 比现有的数组小，则只是设置大小，不重新分配内存。
		int32 SetSize(int32 lNewSize);

		//! 市场按照从小到大排序
		void SortMarket();

		//! 【】操作符，不检查 nIndex 的合法性。
		uint32& operator[](int32 nIndex);
	private:
		typedef baratol::CTLArray<uint32>	_array_uint32;

		_array_uint32	m_ay;
	};
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_MARKETDEF_H


