
#ifndef _MARKETDEF_H
#define _MARKETDEF_H

//////////////////////////////////////////////////////////////////////////////////////////////
//
#define MC_MARKET(x)		(BYTE)(x & 0xF8)
#define MC_STOCK(x)			(BYTE)(x & 0x07)
#define MAX_TYPE_STOCK		8

//////////////////////////////////////////////////////////////////////////////////////////////
//!�г����붨��
#define SH_MARKET			(BYTE)0x10	//��֤
#define SZ_MARKET			(BYTE)0x20	//��֤
#define THS_MARKET			(BYTE)0x30	//ͬ��˳ָ��
#define QT_MARKET			(BYTE)0x40	//�����ڻ�(1-�Ϻ���2-������3-֣�ݡ�4-���ǡ�5-֣����6-�й���Ʒ)
#define BOCE_MARKET			(BYTE)0x50	//�����ڻ�
#define FX_MARKET			(BYTE)0x60	//���(����)
#define HZ_MARKET			(BYTE)0x70	//����ڻ�(����ڽ���)
#define CFF_MARKET			(BYTE)0x80	//�й������ڻ�
#define STB_MARKET			(BYTE)0x90	//�����г�
#define TJWJS_MARKETA		(BYTE)0xA0	//����Ľ����г�
#define HK_MARKET			(BYTE)0xB0	//���֤ȯ(���������)
#define OTC_MARKET			(BYTE)0xC0	//ȯ��OTC����
#define BI_MARKET			(BYTE)0xD0	//�Զ����г������ָ����
#define INVALID_MARKETE		(BYTE)0xE0	//��Ч ��ݼ���������
#define INVALID_MARKETF		(BYTE)0xF0	//��Ч ��Ʊ�������
#define INDX_MARKET			(BYTE)0x18	//ͬ��˳ָ��
#define INVALID_MARKET1		(BYTE)0x28	//��Ч
#define INVALID_MARKET2		(BYTE)0x38	//��Ч ;
#define SSEBOND_MARKET		(BYTE)0x48	//��֤�̶����潻��ƽ̨
#define FXINDX_MARKET		(BYTE)0x58	//����ָ��
#define SWINDEX_MARKET		(BYTE)0x68	//����ָ��
#define ZZINDEX_MARKET		(BYTE)0x78	//��ָ֤��
#define IFIND_MARKET		(BYTE)0x88	//IFIND�г�����
#define VALID_MARKET4		(BYTE)0x98	//�����г�����
#define NYSE_MARKET			(BYTE)0xA8	//ŦԼ������(��Ʊ)
#define NSDQ_MARKET			(BYTE)0xB8	//��˹���
#define US_MARKET			(BYTE)0xC8	//���������г�
#define COMEX_MARKET		(BYTE)0xD8	//֥�Ӹ���Ʒ������
#define OPTIONS_MARKET		(BYTE)0xE8	//������Ȩ
#define BLOCK_MARKET		(BYTE)0xF8	//������

//////////////////////////////////////////////////////////////////////////////////////////////
//!���ඨ��
#define MC_Index			(BYTE)0x00
#define MC_Stock			(BYTE)0x07

#define MC_StockA			(BYTE)0x01	//A��
#define MC_StockB			(BYTE)0x02	//B��
#define MC_Bond				(BYTE)0x03	//ծȯ
#define MC_Fund				(BYTE)0x04	//����
#define MC_Others			(BYTE)0x05	//����
#define MC_StockQ			(BYTE)0x05	//�����й�Ʊ
#define MC_StockH			(BYTE)0x06	//����BרH��
#define MC_StockW			(BYTE)0x06	//��֤���վ�ʾ��

#define MC_Futures			(BYTE)0x01	//�ڻ�
#define MC_Futures_SQ		(BYTE)0x01	//�Ϻ��ڻ�
#define MC_Futures_DQ		(BYTE)0x02	//�����ڻ�
#define MC_Futures_ZQ		(BYTE)0x03	//֣���ڻ�
#define MC_Futures_ZJ		(BYTE)0x04	//����
#define MC_Futures_ZGM		(BYTE)0x05	//֣��
#define MC_Futures_GD		(BYTE)0x06	//�ߴ��ڻ�

#define BOCE_Futures		(BYTE)0x01	//�����ڻ�	mouyu

#define	MC_Foreign			(BYTE)0x01	//���
#define MC_BasedRate        (BYTE)0x01  //��������
#define MC_CrossedRate      (BYTE)0x02  //�������
#define MC_ReverseRate      (BYTE)0x03  //������ʻ���������(���������ʡ������������)
#define MC_FX_OPTION	    (BYTE)0x04  //�����Ȩ
#define MC_FX_OPTIONEXT     (BYTE)0x05  //��㵽����Ȩ

#define MC_MainBoard		(BYTE)0x01	//����
#define MC_GEM				(BYTE)0x02	//��ҵ��
#define MC_Warrant			(BYTE)0x03	//�Ϲ�֤
#define MC_Trusts			(BYTE)0x04	//���л���
#define MC_HKBond			(BYTE)0x05	//���ծȯ
#define MC_BullBear			(BYTE)0x06	//���ţ��֤

#define MC_Foreign_Index	(BYTE)0x01	//����ָ��

#define MC_Index_Futures	(BYTE)0x01	//ָ���ڻ�
#define MC_Stock_Futures	(BYTE)0x02	//��Ʊ�ڻ�
#define MC_HIBOR			(BYTE)0x03	//��Ԫ�����ڻ�(Hong Kong Interback offered Rate)

#define MC_CFF_Index_Futures	(BYTE)0x01	//�н���ָ���ڻ�
#define MC_CFF_Bond_Futures		(BYTE)0x02	//�н�����ծ�ڻ�

//NSDQ_MARKET
#define MC_NQNM             (BYTE)0x01  //NQNM ��˹��˽�����
#define MC_NQSC             (BYTE)0x02  //NQSC ��˹���ȫ��ѡ�г�
#define MC_NQBB             (BYTE)0x03  //NQBB ��˹��˹�����
#define MC_NQPK             (BYTE)0x04  //NQPK ��˹��˳��⽻���г�
#define MC_NQEX             (BYTE)0x05  //NQEX ��˹����ʱ��г�

//NYSE_MARKET
#define MC_NYSE             (BYTE)0x01  //NYSE
#define MC_AMEX             (BYTE)0x02  //AMEX
#define MC_CBOE             (BYTE)0x03  //CBOE
#define MC_PACF             (BYTE)0x04  //PACF
#define MC_NYSEINDEX        (BYTE)0x05  //NYSEָ��
#define MC_AMEXINDEX        (BYTE)0x06  //AMEXָ��
#define MC_PACFINDEX        (BYTE)0x07  //PACFָ��

//US_MARKET
#define MC_DOWJ             (BYTE)0x01  //DOWJ
#define MC_DOWJAMERTIME     (BYTE)0x02  //����˹ָ���������� ����ʱ��Ϊ9:30-16:00

//COME_MARKET
#define MC_NYMX             (BYTE)0x01  //NYMX


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����г������ڵ�ȡ�ļ��࣬�����г��ļ��������ݳص����ݽṹ

#define	FCF_PERIOD_MASK			0x0000FFFF			//����

#define	FCF_MARKET_MASK				0x00FF0000			//�г� FCF_MARKET_*
#define	FCF_MARKET_STOCK			0x00000000			//��Ʊ
#define	FCF_MARKET_Futures			0x00010000			//�ڻ�
#define	FCF_MARKET_Foreign			0x00020000			//���
#define	FCF_MARKET_HK				0x00040000			//�۹�
#define	FCF_MARKET_BOND				0x00050000			//ծȯ�̶�����
#define	FCF_MARKET_US				0x00060000			//����
#define	FCF_MARKET_GlobalFutures	0x00070000			//�����ڻ�
#define	FCF_MARKET_THSIndex			0x00080000			//ͬ��˳ָ��
#define	FCF_MARKET_OPTIONS			0x00090000			//��Ȩ

#define	FCF_OPTION_MASK				0xFF000000			//ѡ�� FCF_OPTION_*
#define	FCF_OPTION_INDEX			0x10000000			//ָ�����������
#define	FCF_OPTION_TODAY			0x20000000			//ʵʱ�����ļ�
#define	FCF_OPTION_BASE				0x40000000			//ʹ�û����ɽ���ϸ�ļ�
#define FCF_OPTION_LEVEL2			0x80000000			//level2���ݸ�ʽ


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�г�������

#define MOPS_24HS				0x00000001		//!�Ƿ���24Сʱ���׵��г������ò�ͬ�����̷�ʽ��������������
#define MOPS_LEVEL2				0x00000002		//!�Ƿ�֧��Level2����
#define MOPS_LNAME				0x00000004		//!�Ƿ�֧�ֳ����Ƶ��г�
#define MOPS_MAIN				0x00000008		//!�Ƿ���ͳһʱ�䣨ֻ��һ��ʱ���ᣩ���г�
#define MOPS_DUPTIME			0x00000010		//!�Ƿ�����ʱ���ظ����ɽ���ϸ��
#define MOPS_US					0x00000020		//!�Ƿ�Ϊ�������г�
#define MOPS_NOINDEX			0x00000040		//!�Ƿ�û��ָ��

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32  GetMarketOptions(uint32 uMarketCode, uint32 uMask);


inline BOOL is24HsExchange(uint32 uMarketCode)	
{
	return (GetMarketOptions(uMarketCode, MOPS_24HS) == MOPS_24HS);
}

inline BOOL IsLevel2Market(uint32 uMarketCode)			//!�ж��Ƿ�Ϊ֧��level2���г�
{
	return (GetMarketOptions(uMarketCode, MOPS_LEVEL2) == MOPS_LEVEL2);
}

void SetLevel2Market(uint32 uMarketCode);				//����level-2�г�
///////////////////////////////////////////////////////////
//!�ж��Ƿ�Ϊ֧�ֳ����Ƶ��г�
inline BOOL IsLongNameMarket(uint32 uMarketCode)
{
	return (GetMarketOptions(uMarketCode, MOPS_LNAME) == MOPS_LNAME);
}

///////////////////////////////////////////////////////////
//!�ж��Ƿ�Ϊͳһʱ����г�
inline BOOL IsMainTimeMarket(uint32 uMarketCode)
{
	return (GetMarketOptions(uMarketCode, MOPS_MAIN) == MOPS_MAIN);
}

//�ж��г��Ƿ�����ʱ���ظ����ɽ���ϸ��
inline bool IsDupTimeMarket(uint32 uMarketCode)
{
	return (GetMarketOptions(uMarketCode, MOPS_DUPTIME) == MOPS_DUPTIME);
}

///////////////////////////////////////////////////////////
//!�ж��Ƿ�Ϊ�������г�
inline BOOL IsUSMarket(uint32 uMarketCode)
{
	return (GetMarketOptions(uMarketCode, MOPS_US) == MOPS_US);
}

//!�����г����룬�жϸ��г��ķ���
void GetMarketTypeFromClass(uint32 uMarket, DWORD& dwOptions);

//!�ж��Ƿ��ǿ���ʽ����
BOOL IsOpenEndedFund(LPCTSTR lpszCode);		

//�г������Ӧ��
BYTE   GetMarketCodeOld(LPCTSTR lpszMarket);
uint32 GetMarketCodeNew(LPCTSTR lpszMarket);
LPCTSTR GetMarketString(uint32 uMarketCode);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��Ʊ�������͵Ķ���
#define MK_STOCKNAME_NORMAL			0x0000			//������ʾ������
#define MK_STOCKNAME_TRADE			0x0100			//���״���
#define MK_STOCKNAME_ENGLISH		0x0200			//Ӣ������
#define MK_STOCKNAME_ALIAS			0x0300			//����
#define MK_STOCKNAME_HISTORY		0x0400			//������
#define MK_STOCKNAME_FULLNAME		0x0500			//ȫ��

#define MK_STOCKNAME_TYPE_MASK		0xFF00			//�������͵�����
#define MK_STOCKNAME_INDEX_MASK		0x00FF			//��ͬ���͸���������

//��Ʊ�������͵��ַ����塣������ʾ��û�ж���
const TCHAR  MK_C_STOCKNAME_NORMAL    = _T('n');	//������ʾ������
const TCHAR  MK_C_STOCKNAME_TRADE     = _T('t');	//���״���
const TCHAR  MK_C_STOCKNAME_ENGLISH   = _T('e');	//Ӣ������
const TCHAR  MK_C_STOCKNAME_ALIAS     = _T('a');	//����
const TCHAR  MK_C_STOCKNAME_HISTORY   = _T('h');	//������
const TCHAR  MK_C_STOCKNAME_FULLNAME  = _T('f');	//ȫ��

WORD    GetStockNameTypeCode(LPCTSTR lpszType);					//�����ַ���ת�������ʹ���
LPCTSTR GetStockNameTypeString(WORD wNameType, TCHAR* pszType);		//�������ʹ���ת�����ַ���

//������Ʊ���Ƶĺ���
//!����ԭ�� int32 func(LPCTSTR lpszCode, LPCTSTR lpszName, WORD wNameType, LPCTSTR lpszAbbr)
//!�����ֱ��� ���� ���� �������� ���
typedef fastdelegate::FastDelegate4<LPCTSTR, LPCTSTR, WORD, LPCTSTR, int32>	_funcStockName;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
�µĴ�������г��ͷ��ࣩ����
1���г����������ԭ���� 1 ���ֽ����䵽 4 ���ֽ�
2���г�����������
   1����һ���ֽڣ������ֽڣ��������־ɵĶ��塣 �̶�Ϊ��U(0x55)
   2���ڶ� �� ���ֽڣ��г����롣�����Ǵ�д��ĸ
   3�����ĸ��ֽڣ�������롣�����Ǵ�С��ĸ����ͬ���г�֮�������ظ�
3��֤ȯ�������
   1�����Ȳ���
   2��ȫ���ɿɼ��ַ���ɣ���ĸ�����֡������ַ��ȣ�
   3����Сд����
4��Ϊ�˴����㣬�г��������ʹ�� uint32 ��ʾ���ֽ���ʹ��С�ˣ�little-endian����

*/
 
//�г����붨��
const uint32 MARKET_SH	=  0x00485300;	//�Ϻ�������						"SH"	
const uint32 MARKET_SZ	=  0x005A5300;	//���ڽ�����						"SZ"
const uint32 MARKET_RF	=  0x00465200;	//ͬ��˳ָ��						"RF"
const uint32 MARKET_CF	=  0x00464300;	//�й���Ʒ�ڻ����Ϻ���������֣�ݣ�	"CF"
const uint32 MARKET_BF	=  0x00464200;	//�����ڻ�							"BF"
const uint32 MARKET_FX	=  0x00584600;	//���								"FX"
const uint32 MARKET_HF	=  0x00464800;	//����ڻ�							"HF"
const uint32 MARKET_IF	=  0x00464900;	//�й������ڻ�						"IF"
const uint32 MARKET_ST	=  0x00545300;	//����								"ST"
const uint32 MARKET_TW	=  0x00575400;	//����Ľ���						"TW"
const uint32 MARKET_HK	=  0x004B4800;	//��۽�����						"HK"
const uint32 MARKET_OT	=  0x00544F00;	//ȯ��OTC							"OT"
const uint32 MARKET_BI	=  0x00494200;	//�ͻ��˰��ָ��					"BI"
const uint32 MARKET_TI	=  0x00495400;	//ͬ��˳ָ�����ɣ�					"TI"
const uint32 MARKET_FB	=  0x00424600;	//�̶�����(Fixed Income)			"FB"
const uint32 MARKET_FI	=  0x00494600;	//����ָ��							"FI"
const uint32 MARKET_SW	=  0x00575300;	//����ָ��							"SW"
const uint32 MARKET_ZZ	=  0x005A5A00;	//��ָ֤��							"ZZ"
const uint32 MARKET_ID	=  0x00444900;	//IFinD�г�							"ZZ"
const uint32 MARKET_NY	=  0x00594E00;	//ŦԼ������						"NY"
const uint32 MARKET_NQ	=  0x00514E00;	//��˹��˽�����					"NQ"
const uint32 MARKET_US	=  0x00535500;	//��������������					"US"
const uint32 MARKET_CM	=  0x004D4300;	//֥�Ӹ���Ʒ						"CM"
const uint32 MARKET_IB	=  0x00424900;	//���м��г�						"IB"
const uint32 MARKET_SO	=  0x004F5300;	//�Ϻ���Ȩ							"SO"

const uint32 MARKET_UU	=  0x00555500;	//δ֪���г�						"UU"


//������ඨ��

//�ַ��Ķ���

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


//���е��г�
#define NMC_Index				CLASS_I		//I	ָ��						0x00
#define NMC_Stock				CLASS_S		//S	��Ʊ						0x01
#define NMC_Others				CLASS_Z		//Z	������û����ȷ�ķ���

#define NMC_UNKNOWN				CLASS_U		//U	δ֪�ģ��ڲ�֪�����������£�������ַ���ʾ

//���MARKET_SH ��MARKET_SZ��
#define NMC_StockA				CLASS_A		//A	A��							0x01
#define NMC_StockB				CLASS_B		//B	B��							0x02
#define NMC_Bond				CLASS_D		//D	ծȯ						0x03
#define NMC_Fund				CLASS_J		//J	���𣨺��ϰ汾���ݣ�		0x04
#define NMC_CEFund				CLASS_F		//F	���ʽ����
#define NMC_OEFund				CLASS_N		//N	����ʽ����
#define NMC_ETF					CLASS_E		//E	ETF
#define NMC_LOF					CLASS_L		//L	LOF
#define NMC_DELIST				CLASS_P		//P	��������					0x05

//��֤��MARKET_SH��
#define NMC_ST					CLASS_T		//T	��֤���վ�ʾ�壨ST��		0x06
#define NMC_OPTION				CLASS_O		//O	��Ȩ

//��֤��MARKET_SZ��
#define NMC_B2H					CLASS_H		//H	����BתH��					0x06

//�۹ɣ�MARKET_HK��
#define NMC_MainBoard			CLASS_M		//M ����						0x01
#define NMC_GEM					CLASS_G		//G ��ҵ��						0x02	
#define NMC_Warrant				CLASS_W		//W �Ϲ�֤��Ȩ֤��				0x03
#define NMC_Trusts				CLASS_T		//T ���л���					0x04
#define NMC_HKBond				CLASS_D		//D ���ծȯ					0x05
#define NMC_BullBear			CLASS_B		//B ���ţ��֤					0x06

//�����ڻ���MARKET_CF��
#define NMC_Futures_SQ			CLASS_S		//S �Ϻ��ڻ�					0x01
#define NMC_Futures_DQ			CLASS_D		//D �����ڻ�					0x02
#define NMC_Futures_ZQ			CLASS_Z		//Z ֣���ڻ�					0x03
#define NMC_Futures_ZJ			CLASS_T		//T ����						0x04
#define NMC_Futures_ZGM			CLASS_L		//L ֣��						0x05
#define NMC_Futures_GD			CLASS_X		//X �ߴ��ڻ�					0x06

//�����ڻ���MARKET_BF��
#define NMC_Futures_BOCE		CLASS_F		//F �����ڻ�					0x01

//��㣨MARKET_FX��
#define NMC_BasedRate			CLASS_B		//B ��������					0x01
#define NMC_CrossedRate			CLASS_C		//C �������					0x02
#define NMC_ReverseRate			CLASS_R		//R ������ʻ���������(���������ʡ������������)	0x03
#define NMC_FX_OPTION			CLASS_O		//O �����Ȩ					0x04
#define NMC_FX_OPTIONEXT		CLASS_N		//N ��㵽����Ȩ				0x05

//����ڻ���MARKET_HF��
#define NMC_Index_Futures		CLASS_F		//F ָ���ڻ�					0x01
#define NMC_Stock_Futures		CLASS_S		//S ��Ʊ�ڻ�					0x02
#define NMC_HIBOR				CLASS_R		//R ��Ԫ�����ڻ�(Hong Kong Interback offered Rate)	0x03

//�й������ڻ����н�����
#define NMC_CFF_Index_Futures	CLASS_F		//F �н���ָ���ڻ�				0x01
#define NMC_CFF_Bond_Futures	CLASS_B		//B	�н�����ծ�ڻ�				0x02

//��˹��ˣ�MARKET_NQ��
#define NMC_NQNM				CLASS_Q		//Q ��˹��˽�����				0x01
#define NMC_NQSC				CLASS_S		//S ��˹���ȫ��ѡ�г�		0x02
#define NMC_NQBB				CLASS_B		//B ��˹��˹�����				0x03
#define NMC_NQPK				CLASS_P		//P ��˹��˳��⽻���г�		0x04
#define NMC_NQEX				CLASS_E		//E ��˹����ʱ��г�			0x05

//ŦԼ��������MARKET_NY��
#define NMC_NYSE				CLASS_N		//N ŦԼ֤ȯ��������NYSE��		0x01
#define NMC_AMEX				CLASS_A		//A ����֤ȯ��������AMEX��		0x02
#define NMC_CBOE				CLASS_C		//C ֥�Ӹ���Ȩ��������CBOE��	0x03
#define NMC_PACF				CLASS_P		//P ����						0x04
#define NMC_NYSEINDEX			CLASS_I		//I ŦԼ֤ȯ������ָ��			0x05
#define NMC_AMEXINDEX			CLASS_M		//M ����֤ȯ������ָ��			0x06
#define NMC_PACFINDEX			CLASS_N		//N ����ָ��					0x07

//����������������MARKET_US��
#define NMC_DOWJ				CLASS_D		//D ����˹ָ��ϵ�й�Ʊ			0x01
#define NMC_DOWJAMERTIME		CLASS_A		//����˹ָ���������� ����ʱ��Ϊ9:30-16:00	0x02

//֥�Ӹ���Ʒ��������MARKET_CM��
#define NMC_NYMX				CLASS_N		//N ŦԼ��Ʒ��������NYMX��		0x01

#define NMK_MASK				0x00FFFF00		//�г�������
#define NMK_CLASS				0xFF000000		//�г����������

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

#define NMK_NEW				_T('U')					//�°汾�ĵ�һ���ַ��������������ϰ汾�ĸ�ʽ
#define NMK_LEN				4						//�г�����ĳ���

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�ⲿ��Ҫ�Ĺ��ߺ���
#define M2N_OPS_MARKET		0x0001		//ֻ��ת�����µ��г��������Ǵ������
namespace code
{
	//! ȡ��������ַ������г�����
	/*!
	*\param  lpszCode	�����г���Ϣ�Ĵ����ַ���
	*\return �����г����룬����������ת���������ԭ�����ϸ�ʽ���ַ������ͷ����ϵġ�
	*/
	uint32 GetMarket(LPCTSTR lpszCode);

	//! ȡ��������ַ����Ĵ���
	/*!
	*\param  lpszCode		�����г���Ϣ�Ĵ����ַ���
	*\return ���ز������г���Ϣ���ַ���
	*/
	const wchar_t* GetCode(const wchar_t* lpszCode);
	const char* GetCode(const char* lpszCode);

	//! ȡ��������ַ����Ĵ���
	/*!
	*\param  lpszCode		�����г���Ϣ�Ĵ����ַ���
	*\param  uMarketCode	�����г����룬����������ת���������ԭ�����ϸ�ʽ���ַ������ͷ����ϵġ�
	*\return ���ز������г���Ϣ���ַ���
	*/
	LPCTSTR GetCode(LPCTSTR lpszCode, uint32& uMarketCode);

	//! �ϲ��г��ʹ���
	/*!
	*\param  uMarketCode	�г����룬֧�����ϸ�ʽ���г�
	*\param  lpszCode		ֻ�д�����ַ���
	*\param  szCode			����ת����Ĵ��롣
	*\param  nLength		szCode �ĳ��ȣ����뱣����������\0����λ�á���� lpszCode ̫����ض�
	*\return ���� szCode
	*\remarks ������ϰ汾���г����룬���ص��ַ��������ϰ汾�ģ��������°汾�ġ�
	*/
	LPCTSTR MergeCode(uint32 uMarketCode, LPCTSTR lpszCode, TCHAR* szCode, int32 nLength);

	//! ���ϸ�ʽ���г�ת�����¸�ʽ
	/*!
	*\param  cMarket	�ϸ�ʽ���г�
	*\param  uOptions	ת�������ԣ������壺M2N_OPS_*
	*\return ���ת��ʧ�ܣ����� 0 �����򷵻�ת������г�����
	*\remarks 
	*/
	uint32 Market2New(BYTE cMarket, uint32 uOptions);

	//! ���ϸ�ʽ���г�ת�����¸�ʽ
	/*!
	*\param  uMarket	���ϸ�ʽ���г�
	*\param  uOptions	ת�������ԣ������壺M2N_OPS_*
	*\return ���ת��ʧ�ܣ����� 0 �����򷵻�ת������г�����
	*\remarks ������¸�ʽ���г���ֱ�ӷ���
	*/
	uint32 Market2New(uint32 uMarket, uint32 uOptions);

	//! �Ƚ������г�
	/*!
	*\param  uMarket	�г����룬֧�����ϸ�ʽ
	*\param  uCompare	����Ƚϵ��г����������µĸ�ʽ
	*\return ����г���ͬ������ true �����򷵻� false
	*\remarks 
	*/
	bool IsMarket(uint32 uMarket, uint32 uCompare);

	//! �Ƚ������г�����
	/*!
	*\param  uMarket	�г�����ͷ��֧࣬�����ϸ�ʽ
	*\param  uCompare	����Ƚϵķ��ࡣ�������µĸ�ʽ��NMC_*��
	*\return ���������ͬ������ true �����򷵻� false
	*\remarks 
	*/
	bool IsClass(uint32 uMarket, uint32 uCompare);

	//! �ַ���ת���ɺϷ��Ĵ����ַ���
	/*!
	*\param  lpszText	�ַ�����֧�����ϸ�ʽ������ 16 17  SH USH  USHA
	*\param  szCode		ת����ı�׼�����ַ����� �ϸ�ʽ�ı�ɣ�0x11 �� ���¸�ʽ�ĵ�һ���ַ�Ϊ U 
	*\return �����г�ռ�õ��ַ��������ϰ汾�ķ��� 1 ���°汾���ݲ�ͬ������� 1 2 3 4
	*\remarks  
	*/
	int32 Str2Code(LPCTSTR lpszText, TCHAR* szCode);

	//! �ַ���ת���ɺϷ����г����루uint32��
	/*!
	*\param  lpszText	�ַ�����֧�����ϸ�ʽ������ 16 17  SH USH  USHA
	*\return  �Ϸ����г����루�������ࣩ���������ϸ�ʽ�ġ�
	*\remarks  
	*/
	uint32 Str2Market(LPCTSTR lpszText);

	//! �г�����ת�����ַ���
	/*!
	*\param  uMarket	�г����룬֧�����ϸ�ʽ
	*\param  szText		����ת������ַ�������������г���ת������ 16 17 �����г�ת���ɣ�USHA�����û�з��࣬ת���� USH
	*\return  ��ʱû�ж���
	*\remarks  szText �ĳ��ȱ����㹻������ 5 ���ַ����ȡ�
	*/
	int32 Market2Str(uint32 uMarket, TCHAR* szText);

	/*
		�г���������飬���Դ���ԭ���Ĺ̶����ȵ����飨�磺BYTE cMarket[32]��
	*/
	class CMarketArray
	{
	public:
		CMarketArray();
		CMarketArray(uint32* pMarket, int32 nMarketCount);
		~CMarketArray();
	public:
		//! �������������һ���г�����������Ĵ�С��
		int32 Add(uint32 uMarket);
		//! �ڸ�����λ�� nPos ����һ���г�����������Ĵ�С����� nPos < 0�����������������һ���г���
		int32 Insert(uint32 uMarket, int32 nPos);

		//! ������������Ӷ���г�����������Ĵ�С��
		int32 Append(uint32* pMarket, int32 nMarketCount);
		//! ˳����ң�����ҵ��Ͳ����ӣ����� -1�������������������һ���г�����������Ĵ�С��
		int32 FindAdd(uint32 uMarket);

		//! ˳����ң�����ҵ������г����ڵ�����ֵ�����򷵻� -1 ��
		int32 Find(uint32 uMarket);
		
		//! ˳����ң�����ҵ���ɾ������г�����������Ĵ�С�����򷵻� -1 ��
		int32 Remove(uint32 uMarket);
		//! ɾ�� nPos λ�õ��г������ nPos �Ϸ���ɾ��������������Ĵ�С�����򷵻� -1 ��
		int32 RemoveAt(int32 nPos);

		//! ��¡����
		void Clone(const CMarketArray& ayMarket);

		//! �ж������Ƿ�Ϊ��
		bool IsEmpty();

		//! �����г����ݵ�ָ��
		uint32* GetMarket();

		//! ��������Ĵ�С
		int32  GetSize();

		//! ��������Ĵ�С����� lNewSize <= 0 ������������顣��� lNewSize �����е�����С����ֻ�����ô�С�������·����ڴ档
		int32 SetSize(int32 lNewSize);

		//! �г����մ�С��������
		void SortMarket();

		//! ����������������� nIndex �ĺϷ��ԡ�
		uint32& operator[](int32 nIndex);
	private:
		typedef baratol::CTLArray<uint32>	_array_uint32;

		_array_uint32	m_ay;
	};
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_MARKETDEF_H


