#ifndef _PERIODDEF_H
#define _PERIODDEF_H

/////////////////////////////////////////////////////////////////////
//时间的格式
#define UT_TIME_SECOND			0			//精确到秒
#define UT_TIME_MINUTE			1			//精确到分钟
#define UT_TIME_DAY				2			//精确到日

//分析周期
#define PD_BASE(x)		(x & 0xFF00)		//取基本周期
#define PD_TIMES(x)		(x & 0x00FF)		//取周期数

#define MIN_5					5			//5分钟K线

#define SEC_5					5			//5秒K线

#define PD_REAL_NUM				3
#define PD_BASE_OFFSET			12

#define UT_NOW					0x0000		//实时数据，不保存历史
#define UT_HISNOW				0x0001		//历史实时数据
#define UT_TRACE				0x1000		//成交明细
#define UT_LEVEL2				0x1C00		//记录逐笔成交、买卖盘、撤单等数据，不放入数据池
#define UT_MINUTE				0x2000		//分钟走势
											//低八位表示分钟
											//0 表示一分钟
#define UT_HISMINUTE			0x2001		//历史分钟走势

#define UT_KLINE_BEG			0x3000		//K线周期的开始
#define UT_MIN					0x3000		//1 5 15 30 60 120分钟K线
											//低八位表示分钟
											//0 表示一分钟

#define UT_SECOND				0x3100		//秒K线
#define UT_DAY					0x4000		//日线
											//低八位表示天
											//0 表示一天
#define UT_WEEK					0x5000		//周线
#define UT_MONTH				0x6000		//月线
#define UT_YEAR					0x7000		//年线
#define UT_KLINE_END			0x7FFF		//K线周期的结束

#define UT_FINANCECALC			0x9000		//财务计算

#define UT_CACHEPERIOD			0xA000		//缓存周期
#define UT_OTHERPERIOD			0xB000		//其他数据下载周期
#define UT_FINPERIOD			0xC000		//财经数据下载周期

#define UT_TEXTPERIOD			0xD000		//文本周期
#define UT_SERVERPUSH			0xDC00		//主站主动推送的数据，不放入数据池

#define UT_EXTRA_PERIOD			0xE000		//特殊周期，存放数据如成交明细和分钟走势用到得前收盘

#define UT_MARKET_PERIOD		0xF100		//取市场信息文件，其实不是周期。
#define UT_STAT_PERIOD			0xF200		//统计计算

#define UT_NONE_PERIOD			0xFFFF		//无周期
#define UT_ALL_PERIOD			0xFFFE		//全部周期，用于表示所有周期的场合

///////////////////////////////////////////////////////////////////////////////////////
#define PD_DAYUNIT(x)			(x < UT_KLINE_BEG  && x >= UT_TRACE)		//判断是否以天为单位
#define PD_KLINE(x)				(x >= UT_KLINE_BEG && x <= UT_KLINE_END)	//判断是否是K线周期

///////////////////////////////////////////////////////////////////////////////////////
//UT_SERVERPUSH 的低位表示数据类型
#define PUSH_REALORDER			0x0001		//推送的短线精灵数据
#define PUSH_RO_REQUEST			0x0002		//请求后推送的短线精灵数据
#define PUSH_RO_STAT			0x0003		//请求统计的短线精灵数据

///////////////////////////////////////////////////////////////////////////////////
//UT_LEVEL2 的低位表示数据文件的类型
#define LEV2_TICK				0x0001		//逐笔成交明细
#define LEV2_BUYWAWAL			0x0002		//个股进入‘委买撤单排名’的撤单信息
#define LEV2_SELLWAWAL			0x0003		//个股进入‘委卖撤单排名’的撤单信息
#define LEV2_BUYORDER			0x0005		//最优逐笔买入价位
#define LEV2_SELLORDER			0x0006		//最优逐笔卖出价位
#define LEV2_ORDER				0x0007		//逐笔委托
#define	LEV2_TRACE				0x0008		//成交明细
#define	LEV2_LEVELS				0x0009		//N档数据

#define LEV2_STAT_VOL			0x0010		//成交量价位统计，分价表
#define LEV2_STAT_CLASS			0x0011		//成交大单统计
#define LEV2_SERIES				0x0012		//拖拉机单
#define LEV2_STAT_CLOUD			0x0013		//成交量统计，成交云
#define LEV2_STAT_SERIES		0x0014		//统计拖拉机单
#define LEV2_STAT_MONEY			0x0015		//成交金额档位统计

#define LEV2_BIGTRADE			0x0020		//大单明细

#define LEV2_MSG				0x0080		//一些排名的信息文件，不需要进行转码处理

#define LEV2_BUYRWARANK			0x0082		//个股即时委买撤单排名
#define LEV2_SELLRWARANK		0x0083		//个股即时委卖撤单排名

#define LEV2_BUYTWARANK			0x0084 		//个股累计委买撤单排名
#define LEV2_SELLTWARANK		0x0089 		//个股累计委卖撤单排名

#define LEV2_INDUSTRYRANK		0x0087		//行业排名
#define LEV2_SECURITYRANK		0x0088		//行业内个股排名

#define LEV2_IND_CHG_RANK		0x008A		//行业换手排名
#define LEV2_SEC_CHG_RANK		0x008B		//行业内个股换手排名

#define LEV2_IND_RISE_RANK		0x008C		//行业涨速排名
#define LEV2_SEC_RISE_RANK		0x008D		//行业内个股涨速排名

#define LEV2_ALLSERIES			0x0092		//所有代码的拖拉机单

///////////////////////////////////////////////////////////////////////////////////
//买卖方向判断
#define	STD_SELL		0x4		//卖盘成交，方向买，外盘
#define	STD_BUY			0x0		//买盘成交，方向卖，内盘

#define	STD_TICK		0x80	//根据逐笔成交判断

#define STD_VOLUME0		0x0

#define STD_VOLUME1		0x1
#define STD_VOLUME2		0x2
#define STD_VOLUME3		0x3

#define	STD_VSELL1		(STD_SELL | STD_VOLUME1)
#define	STD_VBUY1		(STD_BUY  | STD_VOLUME1)
#define	STD_VSELL2		(STD_SELL | STD_VOLUME2)
#define	STD_VBUY2		(STD_BUY  | STD_VOLUME2)
#define	STD_VSELL3		(STD_SELL | STD_VOLUME3)
#define	STD_VBUY3		(STD_BUY  | STD_VOLUME3)

#define STD_NOVOL		0xF							//没有成交

#define IS_NORMALVOL(x)   (x >= 0 && x != (int32)STD_NOVOL)			//正常的成交量分类

/////////////////////////////////////////////////////////////////////////////////////
//周期转换的返回值
#define MT_CPT_ERROR				-1				//错误，不能转换周期
#define MT_CPT_UPDATETIME			1				//需要合并的时间

//时间转换返回值
#define		MT_CAT_UPDATE			0			//更新
#define		MT_CAT_ADD				1			//增加
#define		MT_CAT_OVERLAY			2			//覆盖

#define		MT_CAT_ERROR			-1			//错误

#endif //_PERIODDEF_H



