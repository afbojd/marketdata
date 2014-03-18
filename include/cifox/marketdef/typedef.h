#ifndef _INC_TYPEDEF_H
#define _INC_TYPEDEF_H

#pragma pack(1)
/////////////////////////////////////////////////////////////////////////////
/*
  ������Ŀ��˵��

1������������Ķ���ֵ�� DWORD ��ʾ
   |<- 31 - 22 ->|<- 21 - 16 ->|<- 15 ->|<- 14 - 12 ->|<- 11 - 0 ->|
     ��Ŀʵ��     �Զ�����չ    ϵͳ      ��������      ������Ŀ
  
   ������Ŀ��  �ֶα�ʾ��ÿ�α�ʾһ�����ͣ������������ݡ��������ݵ�
   �������ͣ�  ������ DTE_* ��ʾ�ַ�������������������
   ϵͳ��      ��ʾ���û��Զ���ģ�����ϵͳ�ġ������λΪ 1 ��ʾ�û��Զ��� SF_USERDEFINE
   �Զ�����չ��������Ŀ�������ˣ�ʹ�������չ���� 6 λ�������� 32 ������չ��
   ��Ŀʵ����  ���ڼ��㹫ʽ�ڲ�����������ID���䡣���������֣�ʵ���͸�λ��־ SF_INST_MASK SF_MARK_MASK

2����������������һЩԼ��
	1���������ڷ�Ϊ���ࣺʵʱ���ɽ���ϸ����ʱ��K�ߣ���������K�ߺ���K�ߵȣ�
	2���������ڣ������������е�
	3����ʵʱ��K����һ��������Ϣ���𲽼��ٵĹ��̡���ȡ����ת��Ĺ��̣���Щ����ֻ��ʵʱ���������о���Ϊ�˼�����������

3��������Ŀ�ķ��� ����4095����
	1���������ݣ��ֶΣ�1-300��SM_HQ_BEGIN - SM_HQ_END�������ע�ͻ�򵥵�˵��������Ŀ���ĸ����ڵģ�������ϸ��ȷ�е�
	   ������ �ļ� /cifox/datapool/poolstruct.cpp �� /cifox/datapool/poolstruct_l2.cpp ���涨��ÿ���г�ÿ�����ڵ����ݽṹ
	   �������ݲ�Ҫ��չ����Щ������Ը��ã�����ֻ�����һ���г������ݶ��壩��
    2���������ݣ� �ֶΣ�301-2101��SM_FD_BEGIN - SM_FD_END�����ﶨ��Ĳ�����ȫ����������Ŀ��������������Ŀ���ļ� formula.ini
	3��ί�����ݣ� �ֶΣ�2102-2202��SM_WT_BEGIN - SM_WT_END��ί���û���ʹ�õ�һЩ������Ŀ
	4���ڲ������� �ֶΣ�2203-2503��SM_FUNC_BEGIN - SM_FUNC_END�������ʹ�õ��ڲ������������Ĺ�ʽ���ļ� formula.ini
	5���ⲿ������ �ֶΣ�2504-3504��SM_USERS_BEGIN - SM_USERS_END��ͨ����ʽ�༭����д�Ĺ�ʽ�����ļ� formula.ini
	6����Ѷ���ݣ� �ֶΣ�3505-3605��SM_TEXT_BEGIN - SM_TEXT_END������Ѷ��ص�������Ŀ�������Ķ������ļ� formula.ini
	7��δ����ģ� �ֶΣ�3606-4095

4�����ļ���ʹ��
	1������ļ�������Ϊ������Ŀ��˵���ĵ���
	2����ֹ����ʹ������ļ�������ʹ������ļ�����ĺꡣ
*/
#define	SF_INST_MASK		0x1FC00000			//��Ŀʵ������
#define SF_EXT_MASK			0x003F0000			//�Զ�����չ
#define SF_USERDEFINE		0x00008000			//�û��Զ���
#define	SF_ITEM_MASK		0xFFFF8FFF			//������Ŀ����
#define	SF_TYPE_MASK		0x00007000			//������������

//������Ŀ��λ��־
#define SF_MARK_MASK		0xE0000000
#define SF_MARK_SIGN		0x80000000			//���Ϊ��־������Ϣ���׵�
#define SF_MARK_SELECT		0x40000000			//ѡ�ɵ������־
#define SF_MARK_TEMP		0x20000000			//��ʱ������Ŀ���������վ���صļ�����Ŀ

//
#define	SF_INST_BEGIN		0x00400000			//��Ŀʵ����ʼֵlsb

#define	SF_INST_POS			22
#define SF_MAX_EXT			0x3F

//#define SF_BASEID(x)		((DWORD)(x) & ~(SF_INST_MASK|SF_MARK_MASK))
#define SF_BASEID(x)		((DWORD)(x) & ~((SF_INST_MASK|SF_MARK_MASK)&~SF_MARK_SELECT))
#define SF_DRAWID(x)		((DWORD)(x) | SF_INST_MASK)

#define SF_ISUSERDEFINE(x)	((DWORD)(x) & SF_USERDEFINE)
#define SF_ISSIGN(x)		((DWORD)(x) & SF_MARK_SIGN)
#define SF_ISEXT(x)			((DWORD)(x) & SF_EXT_MASK)

////////////////////////////////////////////////////////////////////////////////////////////
//���λ��ʾ�Ƿ������Ŀ
//��������
#define DTE_CHAR		0x1000			//�ַ���������С�ڵ��� 8��
#define DTE_STRING		0x2000			//�ַ��������ȴ��� 8��
#define DTE_LONG		0x3000			//����
#define DTE_TIMELONG	0x4000			//ʱ���TLLong���ݽṹ������壬������ʱ�䡣
#define DTE_DOUBLE		0x5000			//������
#define DTE_MEMO		0x6000			//�������ı�ע������
#define DTE_HXLONG		0x7000			//�ṹ��������

#define SF_ITEM(x)		((DWORD)(x) & SF_ITEM_MASK)	//ȡID
#define SF_TYPE(x)		((DWORD)(x) & SF_TYPE_MASK)	//ȡ��������
#define SF_INST(x)		((DWORD)(x) & SF_INST_MASK)	//ȡ������Ŀʵ��

//��ֵ
#ifndef SS_MINTIME
#define SS_MINTIME		100000000		//��Сʱ��
#endif
#define PI				3.141592653589793238462643383279

#define GET_MAX_COUNT		10000		//ȡ���ݵ�������
#define DTE_CHAR_NULL		_T("NUL")		//�ַ�����ֵ
#define DTE_LONG_NULL		TSH_LONG_MIN		//������ֵ
#define DTE_DATETIME_NULL	SS_MINTIME		//����ʱ���ֵ
//#define DTE_DOUBLE_NULL		DBL_MIN			//��������ֵ
#define DTE_COLOR_NULL		0x7fffffff		//��ɫCOLORREF

#define IsColorNull(x)		((x) == DTE_COLOR_NULL)
#define SetColorNull(x)		(x) = DTE_COLOR_NULL

///////////////////////////////////////////////////////////////////////////
//��Ʊ�����������
//���м۸񡢳ɽ����ĵ�λ�ǡ�Ԫ����
//���еĳɽ����ĵ�λ�ǡ��ɡ���
//
#define	SM_HQ_BEGIN			0						//�����������ֵ�Ŀ�ʼ

#define SM_HQ_TIME			(SM_HQ_BEGIN + 1)		//�������ڣ���ͬ��ʽ

#define SM_HQ_MARKETTYPE	(SM_HQ_BEGIN + 2)		//�г���� �������ڣ�ʵʱ
#define SM_HQ_CODETYPE		(SM_HQ_BEGIN + 3)		//֤ȯ���� �������ڣ�ʵʱ
#define SM_HQ_CODECODE		(SM_HQ_BEGIN + 4)		//֤ȯ���� �������ڣ�ʵʱ
#define SM_HQ_CODE			(SM_HQ_BEGIN + 5)		//֤ȯ����+֤ȯ���� �������ڣ�ʵʱ
#define SM_HQ_PREVCLOSE		(SM_HQ_BEGIN + 6)		//ǰһ�յ����̼�  �������ڣ���������
#define SM_HQ_OPENPRICE		(SM_HQ_BEGIN + 7)		//���̼� �������ڣ�K��
#define SM_HQ_HIGHPRICE		(SM_HQ_BEGIN + 8)		//��߼� �������ڣ�K��
#define SM_HQ_LOWPRICE		(SM_HQ_BEGIN + 9)		//��ͼ� �������ڣ�K��
#define SM_HQ_NEWPRICE		(SM_HQ_BEGIN + 10)		//���¼� �������ڣ�ʵʱ
#define SM_HQ_CLOSEPRICE	(SM_HQ_BEGIN + 11)		//���̼� �������ڣ�K��

#define SM_HQ_VOLCLASS		(SM_HQ_BEGIN + 12)		//�ɽ������ࣺ����3������2������1���Ե�������1������2������3��
													//ָ�����һ�ʳɽ��ķ������

#define SM_HQ_VOLUME		(SM_HQ_BEGIN + 13)		//�ɽ���
#define SM_HQ_OUTVOL		(SM_HQ_BEGIN + 14)		//���̳ɽ���
#define SM_HQ_INVOL			(SM_HQ_BEGIN + 15)		//���̳ɽ���
#define SM_HQ_ZEROVOL		(SM_HQ_BEGIN + 16)		//�Ե��ɽ���

#define SM_HQ_OPENVOL		(SM_HQ_BEGIN + 17)		//���̳ɽ��� �������ڣ�K��
#define SM_HQ_VOLAMOUNT		(SM_HQ_BEGIN + 18)		//�ɽ�����

#define SM_HQ_MONEY			(SM_HQ_BEGIN + 19)		//�ɽ����

#define SM_HQ_BUYPRICE		(SM_HQ_BEGIN + 20)		//���γɽ�ʱ��ί�������
#define SM_HQ_SELLPRICE		(SM_HQ_BEGIN + 21)		//���γɽ�ʱ��ί��������

#define SM_HQ_BUYCOUNT		(SM_HQ_BEGIN + 22)		//ί��������
													//���ڸ��ɣ�������������֮��
													//����ָ��������ָ�����й�Ʊ����������֮��
#define SM_HQ_SELLCOUNT		(SM_HQ_BEGIN + 23)		//ί��������
													//���ڸ��ɣ�������������֮��
													//����ָ��������ָ�����й�Ʊ����������֮��
//���Ը�����Ч����ʼ �� �������ڣ�ʵʱ��
#define SM_HQ_BUYPRICE1		(SM_HQ_BEGIN + 24)		//ί������۸�һ
#define SM_HQ_BUYCOUNT1		(SM_HQ_BEGIN + 25)		//ί����������һ
#define SM_HQ_BUYPRICE2		(SM_HQ_BEGIN + 26)		//ί������۸��
#define SM_HQ_BUYCOUNT2		(SM_HQ_BEGIN + 27)		//ί������������
#define SM_HQ_BUYPRICE3		(SM_HQ_BEGIN + 28)		//ί������۸���
#define SM_HQ_BUYCOUNT3		(SM_HQ_BEGIN + 29)		//ί������������
#define SM_HQ_SELLPRICE1	(SM_HQ_BEGIN + 30)		//ί�������۸�һ
#define SM_HQ_SELLCOUNT1	(SM_HQ_BEGIN + 31)		//ί����������һ
#define SM_HQ_SELLPRICE2	(SM_HQ_BEGIN + 32)		//ί�������۸��
#define SM_HQ_SELLCOUNT2	(SM_HQ_BEGIN + 33)		//ί������������
#define SM_HQ_SELLPRICE3	(SM_HQ_BEGIN + 34)		//ί�������۸���
#define SM_HQ_SELLCOUNT3	(SM_HQ_BEGIN + 35)		//ί������������
//���Ը�����Ч������

//����ָ����Ч����ʼ �� �������ڣ�ʵʱ��
#define SM_HQ_INDEXTYPE		(SM_HQ_BEGIN + 36)		//ָ�����ࣺ0-�ۺ�ָ�� 1-A�� 2-B��
#define SM_HQ_TOTALSTOCK	(SM_HQ_BEGIN + 37)		//�����Ʊ����
#define SM_HQ_RISECOUNT		(SM_HQ_BEGIN + 38)		//���Ǽ���
#define SM_HQ_FALLCOUNT		(SM_HQ_BEGIN + 39)		//�µ�����
#define SM_HQ_INDEXLEAD		(SM_HQ_BEGIN + 40)		//����ָ��
#define SM_HQ_RISETREND		(SM_HQ_BEGIN + 41)		//��������
#define SM_HQ_FALLTREND		(SM_HQ_BEGIN + 42)		//�µ�����
#define SM_HQ_NEWMONEY		(SM_HQ_BEGIN + 43)		//���һ�ʳɽ����(�ֶ�)
//����ָ����Ч������

#define SM_HQ_ZQMC_BIG5		(SM_HQ_BEGIN + 44)		//֤ȯ����(��������)
#define SM_HQ_5DAYVOL		(SM_HQ_BEGIN + 45)		//�����ܳɽ���  �������ڣ�ʵʱ
#define SM_HQ_ZQMC_ENG		(SM_HQ_BEGIN + 46)		//֤ȯ����(Ӣ��)

#define SM_HQ_ZQMC_UNI		(SM_HQ_BEGIN + 47)		//֤ȯ����(Unicode)
#define SM_HQ_5PERRISE		(SM_HQ_BEGIN + 48)		//������ǵ���  �������ڣ�ʵʱ
#define SM_HQ_NEWVOL		(SM_HQ_BEGIN + 49)		//���һ�ʳɽ���(����) �������ڣ�ʵʱ �ɽ���ϸ

#define SM_HQ_PERWAVE		(SM_HQ_BEGIN + 50)		//��� û��ʹ�ù������Ը��á�yhm
#define SM_HQ_PERVOL		(SM_HQ_BEGIN + 51)		//���� û��ʹ�ù������Ը��á�yhm
#define SM_HQ_COMM			(SM_HQ_BEGIN + 52)		//ί�� û��ʹ�ù������Ը��á�yhm
#define SM_HQ_PERCOMM		(SM_HQ_BEGIN + 53)		//ί�� û��ʹ�ù������Ը��á�yhm
#define SM_HQ_AVERAGE		(SM_HQ_BEGIN + 54)		//���� û��ʹ�ù������Ը��á�yhm

#define SM_HQ_ZQMC			(SM_HQ_BEGIN + 55)		//֤ȯ����(��������) �������ڣ�ʵʱ
#define SM_HQ_SERIAL		(SM_HQ_BEGIN + 56)		//��� �������ڣ�ʵʱ
#define SM_HQ_VALIDBEGIN	(SM_HQ_BEGIN + 57)		//��Чʱ�俪ʼ �������ڣ�ʵʱ
#define SM_HQ_VALIDEND		(SM_HQ_BEGIN + 58)		//��Чʱ����� �������ڣ�ʵʱ
#define SM_HQ_ZQMC_DISPLAY	(SM_HQ_BEGIN + 59)		//֤ȯ����(������) �������ڣ�ʵʱ

//�����ڻ���Ч����ʼ ���������ڣ�ʵʱ����reuse begin��
#define SM_HQ_VARIETY		(SM_HQ_CODE)			//��Լ�� = ����
#define SM_HQ_TRANNO		(SM_HQ_BEGIN + 60)		//
#define SM_HQ_ID			(SM_HQ_BEGIN + 61)		//
#define SM_HQ_ITEMNO		(SM_HQ_BEGIN + 62)		//
#define SM_HQ_EXCH			(SM_HQ_BEGIN + 63)		//������
#define SM_HQ_STATUS		(SM_HQ_BEGIN + 64)		//״̬
#define SM_HQ_INTEREST		(SM_HQ_BEGIN + 65)		//�ֲ���
#define SM_HQ_SETTLE		(SM_HQ_BEGIN + 66)		//�����(�����)
#define SM_HQ_HISHIGH		(SM_HQ_BEGIN + 67)		//ʷ���
#define SM_HQ_HISLOW		(SM_HQ_BEGIN + 68)		//ʷ���
#define SM_HQ_UPPERLIM		(SM_HQ_BEGIN + 69)		//��ͣ��
#define SM_HQ_LOWERLIM		(SM_HQ_BEGIN + 70)		//��ͣ��
#define	SM_HQ_NOWINTEREST	(SM_HQ_BEGIN + 71)		//����
#define SM_HQ_TSETTLE		(SM_HQ_BEGIN + 72)		//������
#define SM_HQ_PREINTEREST	(SM_HQ_BEGIN + 73)		//��ֲ���
#define SM_HQ_PREDELTA		(SM_HQ_BEGIN + 74)		//����ʵ��
#define SM_HQ_CURRDELTA		(SM_HQ_BEGIN + 75)		//����ʵ��
//�����ڻ���Ч������ ��reuse end��

//���������Ч-��ʼ ���������ڣ�ʵʱ��
#define SM_FX_PK			(SM_HQ_CODE)			//���� + ����
#define SM_FX_NAME			(SM_HQ_ZQMC)			//��������
#define SM_FX_TIME			(SM_HQ_TIME)			//���� + ʱ�� (ɨ��仯�ã��������նˣ����ı�ͷ��ֻ����ǰʱ��)
#define	SM_FX_YCLOSE		(SM_HQ_PREVCLOSE)		//����
#define	SM_FX_OPEN			(SM_HQ_OPENPRICE)		//����
#define	SM_FX_HIGH			(SM_HQ_HIGHPRICE)		//���
#define SM_FX_LOW			(SM_HQ_LOWPRICE)		//���
#define	SM_FX_LAST			(SM_HQ_NEWPRICE)		//����
#define	SM_FX_CLOSE			(SM_HQ_CLOSEPRICE)		//���̼�

#define SM_FX_BUYPRICE		(SM_HQ_BUYPRICE)		//ί���
#define SM_FX_SELLPRICE		(SM_HQ_SELLPRICE)		//ί����
#define SM_FX_BUYPRICE1		(SM_HQ_BUYPRICE1)
#define SM_FX_BUYPRICE2		(SM_HQ_BUYPRICE2)
#define SM_FX_BUYPRICE3		(SM_HQ_BUYPRICE3)
#define SM_FX_SELLPRICE1	(SM_HQ_SELLPRICE1)
#define SM_FX_SELLPRICE2	(SM_HQ_SELLPRICE2)
#define SM_FX_SELLPRICE3	(SM_HQ_SELLPRICE3)
#define SM_FX_VOLAMOUNT		(SM_HQ_VOLAMOUNT)		//�ɽ�����
#define SM_FX_ZCVL			(SM_HQ_PERCOMM)			//������
//���������Ч-����

//������Ѱ���Ч����ʼ  ί���������ҵ���
#define SM_HQ_FREEBIGORDERTRADE	(SM_HQ_BEGIN + 76)		//ί��������󵵵Ľ��׷���
#define SM_HQ_FREEBIGORDERGRADE	(SM_HQ_BEGIN + 77)		//ί��������󵵵ĵ�λ
#define SM_HQ_FREEBIGORDERPRICE	(SM_HQ_BEGIN + 78)		//ί��������󵵵ļ۸�
#define SM_HQ_FREEBIGORDERVALUE	(SM_HQ_BEGIN + 79)		//ί��������󵵵���
//������Ѱ���Ч-����

//���Թ�ծ��Ч����ʼ ���������ڣ�ʵʱ��
#define SM_HQ_YJLX			(SM_HQ_BEGIN + 80)		//Ӧ����Ϣ
//���Թ�ծ��Ч������
#define SM_HQ_SYL2			(SM_HQ_BEGIN + 81)		//�����LOF��̬��ֵ �������ڣ�ʵʱ
#define SM_HQ_TIME2			(SM_HQ_BEGIN + 82)		//ͬһ���ļ�����ĵڶ���ʱ��ֵ�������ж��ֺ��� �������ڣ�ʵʱ

#define SM_HQ_PRENAME		(SM_HQ_BEGIN + 83)		//֤ȯ���ǰ׺ �������ڣ�ʵʱ

#define SM_HQ_INDUSTRY		(SM_HQ_BEGIN + 84)		//������ҵ �������ڣ�ʵʱ

//#define SM_NO_USE			(SM_HQ_BEGIN + 85)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 86)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 87)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 88)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 89)		//

#define SM_HQ_LTSZ			(SM_HQ_BEGIN + 90)		//��ͨ��ֵ������������ �������ڣ�ʵʱ
#define SM_HQ_SYL			(SM_HQ_BEGIN + 91)		//��ӯ�ʣ����������� �������ڣ�ʵʱ
#define SM_HQ_ZSZ			(SM_HQ_BEGIN + 92)		//����ֵ������������ �������ڣ�ʵʱ
#define SM_HQ_JYDW			(SM_HQ_BEGIN + 93)		//���׵�λ �������ڣ�ʵʱ
#define SM_HQ_HBDW			(SM_HQ_BEGIN + 94)		//���ҵ�λ �������ڣ�ʵʱ
#define SM_HQ_YEARHIGH		(SM_HQ_BEGIN + 95)		//52����� �������ڣ�ʵʱ
#define SM_HQ_YEARLOW		(SM_HQ_BEGIN + 96)		//52����� �������ڣ�ʵʱ

#define SM_HQ_TEXTNUM		(SM_HQ_BEGIN + 97)		//ʵʱ��Ѷ���� �������ڣ�ʵʱ

#define SM_HQ_YVALUE		(SM_HQ_BEGIN + 98)		//��괦Y�������ֵ ����
#define SM_HQ_YSTRVALUE		(SM_HQ_BEGIN + 99)		//��괦Y������ֵ���ַ��� ����

//#define SM_NO_USE			(SM_HQ_BEGIN + 100)		//

#define SM_TRADE_RESULT		(SM_HQ_BEGIN + 101)		//����ϵͳ����������
//
//���Ը�����Ч����ʼ  - ���������� ���������ڣ�ʵʱ��
#define SM_HQ_BUYPRICE6		(SM_HQ_BEGIN + 102)		//ί������۸���
#define SM_HQ_BUYCOUNT6		(SM_HQ_BEGIN + 103)		//ί������������
#define SM_HQ_SELLPRICE6	(SM_HQ_BEGIN + 104)		//ί�������۸���
#define SM_HQ_SELLCOUNT6	(SM_HQ_BEGIN + 105)		//ί������������

#define SM_HQ_BUYPRICE7		(SM_HQ_BEGIN + 106)		//ί������۸���
#define SM_HQ_BUYCOUNT7		(SM_HQ_BEGIN + 107)		//ί������������
#define SM_HQ_SELLPRICE7	(SM_HQ_BEGIN + 108)		//ί�������۸���
#define SM_HQ_SELLCOUNT7	(SM_HQ_BEGIN + 109)		//ί������������

#define SM_HQ_BUYPRICE8		(SM_HQ_BEGIN + 110)		//ί������۸��
#define SM_HQ_BUYCOUNT8		(SM_HQ_BEGIN + 111)		//ί������������
#define SM_HQ_SELLPRICE8	(SM_HQ_BEGIN + 112)		//ί�������۸��
#define SM_HQ_SELLCOUNT8	(SM_HQ_BEGIN + 113)		//ί������������

#define SM_HQ_BUYPRICE9		(SM_HQ_BEGIN + 114)		//ί������۸��
#define SM_HQ_BUYCOUNT9		(SM_HQ_BEGIN + 115)		//ί������������
#define SM_HQ_SELLPRICE9	(SM_HQ_BEGIN + 116)		//ί�������۸��
#define SM_HQ_SELLCOUNT9	(SM_HQ_BEGIN + 117)		//ί������������
		
#define SM_HQ_BUYPRICE10	(SM_HQ_BEGIN + 118)		//ί������۸�ʮ
#define SM_HQ_BUYCOUNT10	(SM_HQ_BEGIN + 119)		//ί����������ʮ
#define SM_HQ_SELLPRICE10	(SM_HQ_BEGIN + 120)		//ί�������۸�ʮ
#define SM_HQ_SELLCOUNT10	(SM_HQ_BEGIN + 121)		//ί����������ʮ

#define SM_HQ_AVGBUYPRICE	(SM_HQ_BEGIN + 122)		//ƽ��ί������۸�
#define SM_HQ_ALLBUYCOUNT	(SM_HQ_BEGIN + 123)		//����ί�����������ĺ�
#define SM_HQ_AVGSELLPRICE	(SM_HQ_BEGIN + 124)		//ƽ��ί�������۸�
#define SM_HQ_ALLSELLCOUNT	(SM_HQ_BEGIN + 125)		//����ί�����������ĺ�
//
//#define SM_NO_USE			(SM_HQ_BEGIN + 126)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 127)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 128)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 129)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 130)		//

#define SM_HQ_BID_Q6		(SM_HQ_BEGIN + 131)		//ί������ȯ������
#define SM_HQ_BID_Q7		(SM_HQ_BEGIN + 132)		//ί������ȯ������
#define SM_HQ_BID_Q8		(SM_HQ_BEGIN + 133)		//ί������ȯ������
#define SM_HQ_BID_Q9		(SM_HQ_BEGIN + 134)		//ί������ȯ������
#define SM_HQ_BID_Q10		(SM_HQ_BEGIN + 135)		//ί������ȯ����ʮ
#define SM_HQ_ASK_Q6		(SM_HQ_BEGIN + 136)		//ί������ȯ������
#define SM_HQ_ASK_Q7		(SM_HQ_BEGIN + 137)		//ί������ȯ������
#define SM_HQ_ASK_Q8		(SM_HQ_BEGIN + 138)		//ί������ȯ������
#define SM_HQ_ASK_Q9		(SM_HQ_BEGIN + 139)		//ί������ȯ������
#define SM_HQ_ASK_Q10		(SM_HQ_BEGIN + 140)		//ί������ȯ����ʮ
//
//���Ը�����Ȩ��Ч
#define SM_HQ_AuctionPrice			(SM_HQ_BEGIN + 141)		//�������жϲο��۸�
#define SM_HQ_AuctionQty			(SM_HQ_BEGIN + 142)		//�������жϼ��Ͼ�������ƥ����
#define SM_HQ_ContractID			(SM_HQ_BEGIN + 143)		//��Լ����
#define SM_HQ_UnderlyingID			(SM_HQ_BEGIN + 144)		//���֤ȯ����
#define SM_HQ_UnderlyingSymbol		(SM_HQ_BEGIN + 145)		//����֤ȯ֤ȯ����
#define SM_HQ_UnderlyingType		(SM_HQ_BEGIN + 146)		//���֤ȯ����
#define SM_HQ_OptionType			(SM_HQ_BEGIN + 147)		//ŷʽ��ʽ
#define SM_HQ_CallOrPut				(SM_HQ_BEGIN + 148)		//�Ϲ��Ϲ�
#define SM_HQ_Unit					(SM_HQ_BEGIN + 149)		//��Լ��λ
//������Ȩ-����

#define SM_HQ_BUYPRICE4		(SM_HQ_BEGIN + 150)		//ί������۸���
#define SM_HQ_BUYCOUNT4		(SM_HQ_BEGIN + 151)		//ί������������
#define SM_HQ_SELLPRICE4	(SM_HQ_BEGIN + 152)		//ί�������۸���
#define SM_HQ_SELLCOUNT4	(SM_HQ_BEGIN + 153)		//ί������������
#define SM_HQ_BUYPRICE5		(SM_HQ_BEGIN + 154)		//ί������۸���
#define SM_HQ_BUYCOUNT5		(SM_HQ_BEGIN + 155)		//ί������������
#define SM_HQ_SELLPRICE5	(SM_HQ_BEGIN + 156)		//ί�������۸���
#define SM_HQ_SELLCOUNT5	(SM_HQ_BEGIN + 157)		//ί������������
//���Ը�����Ч������

//#define SM_NO_USE			(SM_HQ_BEGIN + 158)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 159)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 160)		//

//���Ը۹���Ч����ʼ ���������ڣ�ʵʱ����reuse begin��
//��֤L2�������(SM_HQ_HKBQ_BUYROW1 -- SM_HQ_HIGHER_SPREAD)���ο�poolstruct_l2.cpp
#define SM_HQ_HKBQ_BUYROW1	(SM_HQ_BEGIN + 161)		//����ȯ��һ
#define SM_HQ_HKBQ_BUYROW2	(SM_HQ_BEGIN + 162)		//
#define SM_HQ_HKBQ_BUYROW3	(SM_HQ_BEGIN + 163)		//
#define SM_HQ_HKBQ_BUYROW4	(SM_HQ_BEGIN + 164)		//
#define SM_HQ_HKBQ_BUYROW5	(SM_HQ_BEGIN + 165)		//
#define SM_HQ_HKBQ_BUYROW6	(SM_HQ_BEGIN + 166)		//
#define SM_HQ_HKBQ_BUYROW7	(SM_HQ_BEGIN + 167)		//
#define SM_HQ_HKBQ_BUYROW8	(SM_HQ_BEGIN + 168)		//
#define SM_HQ_HKBQ_BUYROW9	(SM_HQ_BEGIN + 169)		//
#define SM_HQ_HKBQ_BUYROW10	(SM_HQ_BEGIN + 170)		//
#define SM_HQ_HKBQ_SELLROW1	(SM_HQ_BEGIN + 171)		//����ȯ��һ
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
#define SM_HQ_BID_Q1		(SM_HQ_BEGIN + 181)		//ί������ȯ����һ
#define SM_HQ_BID_Q2		(SM_HQ_BEGIN + 182)		//ί������ȯ������
#define SM_HQ_BID_Q3		(SM_HQ_BEGIN + 183)		//ί������ȯ������
#define SM_HQ_BID_Q4		(SM_HQ_BEGIN + 184)		//ί������ȯ������
#define SM_HQ_BID_Q5		(SM_HQ_BEGIN + 185)		//ί������ȯ������
#define SM_HQ_ASK_Q1		(SM_HQ_BEGIN + 186)		//ί������ȯ����һ
#define SM_HQ_ASK_Q2		(SM_HQ_BEGIN + 187)		//ί������ȯ������
#define SM_HQ_ASK_Q3		(SM_HQ_BEGIN + 188)		//ί������ȯ������
#define SM_HQ_ASK_Q4		(SM_HQ_BEGIN + 189)		//ί������ȯ������
#define SM_HQ_ASK_Q5		(SM_HQ_BEGIN + 190)		//ί������ȯ������
//
#define SM_HQ_LOWER_SPREAD	(SM_HQ_BEGIN + 191)		//���
#define SM_HQ_HIGHER_SPREAD	(SM_HQ_BEGIN + 192)		//���
#define SM_HQ_PREMINUM		(SM_HQ_BEGIN + 193)		//���
#define SM_HQ_GEARING		(SM_HQ_BEGIN + 194)		//�ܸ˱���
#define SM_HQ_EXERC_PRICE	(SM_HQ_BEGIN + 195)		//��ʹ��
#define SM_HQ_CONV_RATIO	(SM_HQ_BEGIN + 196)		//��������
#define SM_HQ_EXPIRY_DATE	(SM_HQ_BEGIN + 197)		//������
//���Ը۹���Ч������ ��reuse end��

//#define SM_NO_USE			(SM_HQ_BEGIN + 198)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 199)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 200)		//

/////////////////////////////////////////////////////////////////////////////////
//���鶨������䵽300��
//Level2�����ݣ��������ڣ����У�
#define SM_HQ_BIGBUYCOUNT1		(SM_HQ_BEGIN + 201)		//���������ش���
#define SM_HQ_BIGSELLCOUNT1		(SM_HQ_BEGIN + 202)		//���������ش���
#define SM_HQ_BIGBUYCOUNT2		(SM_HQ_BEGIN + 203)		//�����������
#define SM_HQ_BIGSELLCOUNT2		(SM_HQ_BEGIN + 204)		//������������
#define SM_HQ_BIGBUYCOUNT3		(SM_HQ_BEGIN + 205)		//���������е���
#define SM_HQ_BIGSELLCOUNT3		(SM_HQ_BEGIN + 206)		//���������е���
#define SM_HQ_WAITBUYCOUNT1		(SM_HQ_BEGIN + 207)		//���������ش���
#define SM_HQ_WAITSELLCOUNT1	(SM_HQ_BEGIN + 208)		//���������ش���
#define SM_HQ_WAITBUYCOUNT2		(SM_HQ_BEGIN + 209)		//�����������
#define SM_HQ_WAITSELLCOUNT2	(SM_HQ_BEGIN + 210)		//������������
#define SM_HQ_WAITBUYCOUNT3		(SM_HQ_BEGIN + 211)		//���������е���
#define SM_HQ_WAITSELLCOUNT3	(SM_HQ_BEGIN + 212)		//���������е���
#define SM_HQ_BIGBUYCOUNT4		(SM_HQ_BEGIN + 213)		//��������С����
#define SM_HQ_BIGSELLCOUNT4		(SM_HQ_BEGIN + 214)		//��������С����
//
#define SM_HQ_BIGBUYTICK1		(SM_HQ_BEGIN + 215)		//���������ش󵥱���
#define SM_HQ_BIGSELLTICK1		(SM_HQ_BEGIN + 216)		//���������ش󵥱���
#define SM_HQ_BIGBUYTICK2		(SM_HQ_BEGIN + 217)		//��������󵥱���
#define SM_HQ_BIGSELLTICK2		(SM_HQ_BEGIN + 218)		//���������󵥱���
#define SM_HQ_WAITBUYTICK1		(SM_HQ_BEGIN + 219)		//���������ش󵥱���
#define SM_HQ_WAITSELLTICK1		(SM_HQ_BEGIN + 220)		//���������ش󵥱���
#define SM_HQ_WAITBUYTICK2		(SM_HQ_BEGIN + 221)		//��������󵥱���
#define SM_HQ_WAITSELLTICK2		(SM_HQ_BEGIN + 222)		//���������󵥱���
#define SM_HQ_BIGBUYMONEY1		(SM_HQ_BEGIN + 223)		//���������ش󵥽��
#define SM_HQ_BIGSELLMONEY1		(SM_HQ_BEGIN + 224)		//���������ش󵥽��
#define SM_HQ_BIGBUYMONEY2		(SM_HQ_BEGIN + 225)		//��������󵥽��
#define SM_HQ_BIGSELLMONEY2		(SM_HQ_BEGIN + 226)		//���������󵥽��
#define SM_HQ_WAITBUYMONEY1		(SM_HQ_BEGIN + 227)		//���������ش󵥽��
#define SM_HQ_WAITSELLMONEY1	(SM_HQ_BEGIN + 228)		//���������ش󵥽��
#define SM_HQ_WAITBUYMONEY2		(SM_HQ_BEGIN + 229)		//��������󵥽��
#define SM_HQ_WAITSELLMONEY2	(SM_HQ_BEGIN + 230)		//���������󵥽��
#define	SM_HQ_BUYTICK			(SM_HQ_BEGIN + 231)		//���뵥����
#define	SM_HQ_SELLTICK			(SM_HQ_BEGIN + 232)		//����������

#define	SM_HQ_ZJLR				(SM_HQ_BEGIN + 233)		//�ʽ�����
#define	SM_HQ_ZJLC				(SM_HQ_BEGIN + 234)		//�ʽ�����

#define SM_HQ_DDE_UP			(SM_HQ_BEGIN + 235)		//�󵥾�����
#define SM_HQ_DDE_DOWN			(SM_HQ_BEGIN + 236)		//�󵥾�����

#define SM_HQ_BIGBUYMONEY4		(SM_HQ_BEGIN + 237)		//��������С�����
#define SM_HQ_BIGSELLMONEY4		(SM_HQ_BEGIN + 238)		//��������С�����

#define SM_HQ_TICKAMOUNT		(SM_HQ_BEGIN + 239)		//�ɽ�����

#define	SM_HQ_PREYIELD			(SM_HQ_BEGIN + 240)		//��������������
#define	SM_HQ_PREAVGYIELD		(SM_HQ_BEGIN + 241)		//���ռ�Ȩƽ��������
#define	SM_HQ_OPENYIELD			(SM_HQ_BEGIN + 242)		//����������
#define	SM_HQ_HIGHYIELD			(SM_HQ_BEGIN + 243)		//���������
#define	SM_HQ_LOWYIELD			(SM_HQ_BEGIN + 244)		//���������
#define	SM_HQ_LASTYIELD			(SM_HQ_BEGIN + 245)		//����������
#define	SM_HQ_AVGYIELD			(SM_HQ_BEGIN + 246)		//���ռ�Ȩƽ��������

#define SM_HQ_BUYMONEY5			(SM_HQ_BEGIN + 250)		//ί������ǰ�嵵���
#define SM_HQ_SELLMONEY5		(SM_HQ_BEGIN + 251)		//ί������ǰ�嵵���
#define SM_HQ_BUYMONEY10		(SM_HQ_BEGIN + 252)		//ί������ǰʮ�����
#define SM_HQ_SELLMONEY10		(SM_HQ_BEGIN + 253)		//ί������ǰʮ�����

//#define SM_NO_USE			(SM_HQ_BEGIN + 254)		//

#define SM_HQ_BIGBUYTICK3		(SM_HQ_BEGIN + 255)		//���������е�����
#define SM_HQ_BIGSELLTICK3		(SM_HQ_BEGIN + 256)		//���������е�����
#define SM_HQ_WAITBUYTICK3		(SM_HQ_BEGIN + 257)		//���������е�����
#define SM_HQ_WAITSELLTICK3		(SM_HQ_BEGIN + 258)		//���������е�����
#define SM_HQ_BIGBUYMONEY3		(SM_HQ_BEGIN + 259)		//���������е����
#define SM_HQ_BIGSELLMONEY3		(SM_HQ_BEGIN + 260)		//���������е����
#define SM_HQ_WAITBUYMONEY3		(SM_HQ_BEGIN + 261)		//���������е����
#define SM_HQ_WAITSELLMONEY3	(SM_HQ_BEGIN + 262)		//���������е����

//#define SM_NO_USE			(SM_HQ_BEGIN + 263)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 264)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 265)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 266)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 267)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 268)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 269)		//
//#define SM_NO_USE			(SM_HQ_BEGIN + 270)		//

#define SM_HQ_YEARHIGHDATE		(SM_HQ_BEGIN + 271)		//��ʮ�����������
#define SM_HQ_YEARLOWDATE		(SM_HQ_BEGIN + 272)		//��ʮ�����������
#define SM_HQ_HISHIGHDATE		(SM_HQ_BEGIN + 273)		//����������
#define SM_HQ_HISLOWDATE		(SM_HQ_BEGIN + 274)		//����������

#define SM_HQ_NOWLZSTOCK		(SM_HQ_BEGIN + 275)		//���ǹ�
#define SM_HQ_NOWRISELIMITCOUNT	(SM_HQ_BEGIN + 276)		//��ͣ����
#define SM_HQ_NOWFALLLIMITCOUNT	(SM_HQ_BEGIN + 277)		//��ͣ����

#define SM_HQ_NEWPRICEUS		(SM_HQ_BEGIN + 278)		//�̺����¼�
#define SM_HQ_HKRMBMONEY		(SM_HQ_BEGIN + 279)		//�۹�ָ������ҳɽ����

//���Ը�����Ȩ��Ч
#define SM_HQ_ExercisePrice			(SM_HQ_BEGIN + 280)		//��Ȩ��Ȩ��
#define SM_HQ_StartDate				(SM_HQ_BEGIN + 281)		//�׸�������
#define SM_HQ_EndDate				(SM_HQ_BEGIN + 282)		//�������
#define SM_HQ_ExerciseDate			(SM_HQ_BEGIN + 283)		//��Ȩ��Ȩ��
#define SM_HQ_ExpireDate			(SM_HQ_BEGIN + 284)		//��Ȩ������
#define SM_HQ_UpdateVersion			(SM_HQ_BEGIN + 285)		//��Լ�汾��
//#define SM_NO_ClrMmbrLimit		(SM_HQ_BEGIN + 286)		//���׻�Ա�ֲ�����
#define SM_HQ_DeliveryDate			(SM_HQ_BEGIN + 286)		//��Ȩ������
//#define SM_NO_LeavesQty			(SM_HQ_BEGIN + 287)		//δƽ�ֺ�Լ��
//#define SM_HQ_TotalLongPosition	(SM_HQ_BEGIN + 287)		//��ǰ��Լδƽ����

#define SM_HQ_UnderlyingClosePx		(SM_HQ_BEGIN + 288)		//���֤ȯǰ����
#define SM_HQ_PriceLimitType		(SM_HQ_BEGIN + 289)		//�ǵ�����������
//#define SM_NO_PriceUpLimit		(SM_HQ_BEGIN + 290)		//�Ƿ����޼۸�
//#define SM_NO_PriceDownLimit		(SM_HQ_BEGIN + 291)		//�������޼۸�
#define SM_HQ_MarginRatioParam1		(SM_HQ_BEGIN + 290)		//��֤������������һ
#define SM_HQ_MarginRatioParam2		(SM_HQ_BEGIN + 291)		//��֤��������������
#define SM_HQ_MarginUint			(SM_HQ_BEGIN + 292)		//��λ��֤��
//#define SM_NO_MarginRatio			(SM_HQ_BEGIN + 293)		//��֤�����
#define SM_HQ_RoundLot				(SM_HQ_BEGIN + 294)		//������
#define SM_HQ_LmtOrdMinFloor		(SM_HQ_BEGIN + 295)		//�����޼��걨����
#define SM_HQ_LmtOrdMaxFloor		(SM_HQ_BEGIN + 296)		//�����޼��걨����
#define SM_HQ_MktOrdMinFloor		(SM_HQ_BEGIN + 297)		//�����м��걨����
#define SM_HQ_MktOrdMaxFloor		(SM_HQ_BEGIN + 298)		//�����м��걨����
#define SM_HQ_SecurityStatusFlag	(SM_HQ_BEGIN + 299)		//��Ȩ��Լ״̬��Ϣ��ǩ
//������Ȩ-����


#define	SM_HQ_END				SM_HQ_BEGIN + 300		//�����������ֵ�Ľ���

/////////////////////////////////////////////////////////////////////////////////
//�ƾ����ݿ��������
#define	CJ_BBRQ				SM_HQ_TIME			  //����

#define CJ_ITEM_MASK		0xFFF88FFF			  //�ƾ����ݵĻ���������Ŀ����
#define CJ_REPTYPE_MASK		0x00070000			  //�������͵�����

#define CJ_REPTYPE_NONE		0x00000000			  //����Ҫ��
#define	CJ_REPTYPE_SEASON1	0x00010000			  //��һ������
#define CJ_REPTYPE_HALF		0x00020000			  //�б�
#define CJ_REPTYPE_SEASON3	0x00030000			  //����������
#define CJ_REPTYPE_YEAR		0x00040000			  //�걨

#define CJ_ITEM(a)			(CJ_ITEM_MASK & (a))	//ȡ������Ŀ
#define CJ_REPTYPE(a)		(CJ_REPTYPE_MASK & (a))	//ȡ��������


#define CJ_TOPVIEW_BIT		0x00200000				// ��ʶ��topview����
#define CJ_TOPVIEW_DAY		0x00000000				// ��ʶ����������
#define CJ_TOPVIEW_WEEK		0x00400000				// ��ʶ����������
#define CJ_TOPVIEW_MONTH	0x00800000				// ��ʶ����������

#define CJ_IS_TOPVIEW(a)	(CJ_TOPVIEW_BIT & (a))	// �ж��Ƿ���topview������
#define CJ_MAKE_TV_WEEK(a)	(CJ_TOPVIEW_WEEK | (a))	// �ϳ����ߵ�topview������
#define CJ_MAKE_TV_MONTH(a)	(CJ_TOPVIEW_MONTH |(a))	// �ϳ����ߵ�topview������

#define CJ_TOPVIEW_PERIOD(a) ((CJ_TOPVIEW_WEEK|CJ_TOPVIEW_MONTH) & (a))	// �ϳ�

// ����ʱ���ж�. YYYYMMDD
#define IS_SEASON1_DATE(a)	((a)%10000 == 331)	  //�ж������Ƿ��ǵ�һ����������
#define IS_HALF_DATE(a)		((a)%10000 == 630)	  //�ж������Ƿ����б�
#define IS_SEASON3_DATE(a)	((a)%10000 == 930)	  //�ж������Ƿ��ǵ���������
#define IS_YEAR_DATE(a)		((a)%10000 == 1231)	  //�ж������Ƿ����걨


/////////////////////////////////////////////////////////////////////////////////
#define	SM_FD_BEGIN			301					  //301 �ƾ��������ֵ�Ŀ�ʼ

#define	SM_FD_BEGIN2		(SM_HQ_END + 100 + 1)		  //401 ��������������Ŀ�Ŀ�ʼ

//�ġ� �ɱ��ṹ��	
//1�����ݱ����ƣ�GBJG
//2��˵�������й�˾�Ĺɱ���ɼ��䶯�����
//3����ṹ
#define GBJG_BEGIN			SM_FD_BEGIN2		//401

#define      CJ_GBBRQ		(GBJG_BEGIN + 0)	//�ɱ��䶯����
#define      CJ_ZGS			(GBJG_BEGIN + 1)	//�ܹ���
#define      CJ_GJG			(GBJG_BEGIN + 2)	//���ҹ�
#define      CJ_FQRG		(GBJG_BEGIN + 3)	//�����˹�
#define      CJ_FRG			(GBJG_BEGIN + 4)	//���˹�
#define      CJ_NBZGG		(GBJG_BEGIN + 5)	//�ڲ�ְ����
#define      CJ_SHGZG		(GBJG_BEGIN + 6)	//��ṫ�ڹ�
#define      CJ_ZPG			(GBJG_BEGIN + 7)	//ת���
#define      CJ_WZCG		(GBJG_BEGIN + 8)	//���ʳֹ�
#define      CJ_BG			(GBJG_BEGIN + 9)	//B��
#define      CJ_HG			(GBJG_BEGIN + 10)	//H��
#define      CJ_YXG			(GBJG_BEGIN + 11)	//���ȹ�
#define      CJ_KZZ			(GBJG_BEGIN + 12)	//��ת����˾ծȯ
#define      CJ_FXJA		(GBJG_BEGIN + 13)	//A�ɷ��м�
#define      CJ_FXJB		(GBJG_BEGIN + 14)	//B�ɷ��м�
#define      CJ_FXJH		(GBJG_BEGIN + 15)	//H�ɷ��м�
#define      CJ_GBSM		(GBJG_BEGIN + 16)	//�ɱ�˵��
#define      CJ_BDYY		(GBJG_BEGIN + 17)	//�ɱ��䶯ԭ��
#define      CJ_QXBH		(GBJG_BEGIN + 18)	//ȨϢ���
#define      CJ_ZSZ			(GBJG_BEGIN + 19)	//����ֵ
#define      CJ_LTSZ		(GBJG_BEGIN + 20)	//��ͨ��ֵ

#define GBJG_END			(GBJG_BEGIN + 49)	//450

//�塢 ȨϢ���ϱ�	
//1�����ݱ����ƣ�QXZL
//2��˵�������й�˾�ķֺ���ɷ�����
//3����ṹ

#define QXZL_BEGIN			(GBJG_BEGIN + 50)	//451

#define      CJ_QXNF		(QXZL_BEGIN + 0)	//ȨϢ���
#define      CJ_QXSQ		(QXZL_BEGIN + 1)	//ȨϢʱ��
#define      CJ_QXLX		(QXZL_BEGIN + 2)	//ȨϢ����
#define      CJ_SGBL		(QXZL_BEGIN + 3)	//�͹ɱ���
#define      CJ_PGBL		(QXZL_BEGIN + 4)	//��ɱ���
#define      CJ_PGJ			(QXZL_BEGIN + 5)	//��ɼ�
#define      CJ_XJHL		(QXZL_BEGIN + 6)	//�ֽ����
#define      CJ_ZPBL		(QXZL_BEGIN + 7)	//ת�����
#define      CJ_ZPJ			(QXZL_BEGIN + 8)	//ת���
#define      CJ_ZZBL		(QXZL_BEGIN + 9)	//ת������
#define		 CJ_ZFJ			(QXZL_BEGIN + 10)	//������
#define		 CJ_ZFBL		(QXZL_BEGIN + 11)	//��������
#define		 CJ_PXBL		(QXZL_BEGIN + 12)	//��Ϣ����
#define		 CJ_CQCKJ		(QXZL_BEGIN + 13)	//��Ȩ�ο���
#define      CJ_CQXS		(QXZL_BEGIN + 14)    //��Ȩϵ��

#define      CJ_CQR			(QXZL_BEGIN + 15)     //��Ȩ��
#define      CJ_DJR			(QXZL_BEGIN + 16)     //�Ǽ���
#define      CJ_PSSR		(QXZL_BEGIN + 17)     //���������
#define      CJ_PGHLRQQ		(QXZL_BEGIN + 18)    //�ɣ��죩����ʼ��
#define      CJ_PGHLRQZ		(QXZL_BEGIN + 19)    //�ɣ��죩����ֹ��
#define      CJ_QXSM		(QXZL_BEGIN + 20)    //ȨϢ˵��
#define QXZL_END			(QXZL_BEGIN + 49)	//500

//ȨϢ����
#define		 QXLX_D				'D'			//����		
#define		 QXLX_Y				'Y'			//Ԥ��

//���� �ʲ���ծ��
//1�����ݱ����ƣ�ZCFZB
//2��˵�������й�˾���ʲ���ծ�����
//3����
#define ZCFZB_BEGIN			SM_FD_BEGIN + 200	//501

#define      CJ_HBZJ		(ZCFZB_BEGIN + 0)    //�����ʽ�
#define      CJ_DQTZ		(ZCFZB_BEGIN + 1)    //����Ͷ��
#define      CJ_DQTZDJ		(ZCFZB_BEGIN + 2)    //����Ͷ�ʵ���׼��
#define      CJ_YSPJ		(ZCFZB_BEGIN + 3)    //Ӧ��Ʊ��
#define      CJ_YSGL		(ZCFZB_BEGIN + 4)    //Ӧ�չ���
#define      CJ_YSLX		(ZCFZB_BEGIN + 5)    //Ӧ����Ϣ
#define      CJ_YSZK		(ZCFZB_BEGIN + 6)    //Ӧ���ʿ�
#define      CJ_QTYSK		(ZCFZB_BEGIN + 7)    //����Ӧ�տ�
#define      CJ_HZZB		(ZCFZB_BEGIN + 8)    //����׼��
#define      CJ_YSZKJE		(ZCFZB_BEGIN + 9)	 //Ӧ���ʿ��

#define      CJ_YUFZK		(ZCFZB_BEGIN + 10)   //Ԥ���ʿ�
#define      CJ_YSBTK		(ZCFZB_BEGIN + 11)   //Ӧ�ղ�����
#define      CJ_NBYSK		(ZCFZB_BEGIN + 12)   //�ڲ�Ӧ�տ�
#define      CJ_CH			(ZCFZB_BEGIN + 13)   //���
#define      CJ_CHDJZB		(ZCFZB_BEGIN + 14)   //�������׼��
#define      CJ_CHJE		(ZCFZB_BEGIN + 15)   //�������
#define      CJ_DTFY		(ZCFZB_BEGIN + 16)   //��̯����
#define      CJ_YNDQTZ		(ZCFZB_BEGIN + 17)   //һ���ڵ��ڵĳ���ծȯͶ��
#define      CJ_QTLDZC		(ZCFZB_BEGIN + 18)   //���������ʲ�
#define      CJ_LDZCHJ		(ZCFZB_BEGIN + 19)   //�����ʲ��ϼ�

#define      CJ_CQGQTZ		(ZCFZB_BEGIN + 20)   //���ڹ�ȨͶ��
#define      CJ_CQZQTZ		(ZCFZB_BEGIN + 21)   //����ծȯͶ��
#define      CJ_CQTZJZ		(ZCFZB_BEGIN + 22)   //����Ͷ�ʼ�ֵ׼��
#define      CJ_CQTZHJ		(ZCFZB_BEGIN + 23)   //����Ͷ�ʺϼ�
#define      CJ_GDZCYJ		(ZCFZB_BEGIN + 24)   //�̶��ʲ�ԭ��
#define      CJ_LJZJ		(ZCFZB_BEGIN + 25)   //�ۼ��۾�
#define      CJ_GDZCJZ		(ZCFZB_BEGIN + 26)   //�̶��ʲ���ֵ׼��
#define      CJ_GCWZ		(ZCFZB_BEGIN + 27)   //��������
#define      CJ_ZJGC		(ZCFZB_BEGIN + 28)   //�ڽ�����
#define      CJ_ZJGCJZ		(ZCFZB_BEGIN + 29)   //�ڽ����̼�ֵ׼��

#define      CJ_GDZCQL		(ZCFZB_BEGIN + 30)   //�̶��ʲ�����
#define      CJ_GDZCHJ		(ZCFZB_BEGIN + 31)   //�̶��ʲ��ϼ�
#define		 CJ_WXZC		(ZCFZB_BEGIN + 32)   //�����ʲ�
#define      CJ_WXZCJZ		(ZCFZB_BEGIN + 33)   //�����ʲ���ֵ׼��
#define      CJ_CQDTFY		(ZCFZB_BEGIN + 34)   //���ڴ�̯����
#define      CJ_QTCQZC		(ZCFZB_BEGIN + 35)   //���������ʲ�
#define      CJ_WXJQT		(ZCFZB_BEGIN + 36)   //�����ʲ��������ʲ��ϼ�
#define      CJ_DYZC		(ZCFZB_BEGIN + 37)   //�����ʲ�
#define      CJ_DYSKJX		(ZCFZB_BEGIN + 38)   //����˰�����
#define      CJ_DCLLCSS		(ZCFZB_BEGIN + 39)   //�����������ʲ���ʧ

#define      CJ_DCLGCSS		(ZCFZB_BEGIN + 40)   //������̶��ʲ���ʧ
#define      CJ_DCLZCSS		(ZCFZB_BEGIN + 41)   //�������ʲ���ʧ
#define      CJ_ZCZJ		(ZCFZB_BEGIN + 42)   //�ʲ��ܼ�
#define      CJ_DQJK		(ZCFZB_BEGIN + 43)   //���ڽ��
#define      CJ_YFPJ		(ZCFZB_BEGIN + 44)   //Ӧ��Ʊ��
#define      CJ_YFZK		(ZCFZB_BEGIN + 45)   //Ӧ���ʿ�
#define      CJ_YUSZK		(ZCFZB_BEGIN + 46)   //Ԥ���ʿ�
#define      CJ_YFGZ		(ZCFZB_BEGIN + 47)   //Ӧ������
#define      CJ_YFFLF		(ZCFZB_BEGIN + 48)   //Ӧ��������
#define      CJ_YFGL		(ZCFZB_BEGIN + 49)   //Ӧ������

#define      CJ_YJSJ		(ZCFZB_BEGIN + 50)   //Ӧ��˰��
#define      CJ_QTYJK		(ZCFZB_BEGIN + 51)   //����Ӧ����
#define      CJ_QTYFK		(ZCFZB_BEGIN + 52)   //����Ӧ����
#define      CJ_NBYFK		(ZCFZB_BEGIN + 53)   //�ڲ�Ӧ����
#define      CJ_YUTFY		(ZCFZB_BEGIN + 54)   //Ԥ�����
#define      CJ_DKSJ		(ZCFZB_BEGIN + 55)   //����˰��
#define      CJ_YJFZ		(ZCFZB_BEGIN + 56)   //Ԥ�Ƹ�ծ
#define      CJ_YNDQFZ		(ZCFZB_BEGIN + 57)   //һ���ڵ��ڵĳ��ڵĳ��ڸ�ծ
#define      CJ_QTLDFZ		(ZCFZB_BEGIN + 58)   //����������ծ
#define      CJ_LDFZHJ		(ZCFZB_BEGIN + 59)   //������ծ�ϼ�

#define      CJ_CQJK		(ZCFZB_BEGIN + 60)   //���ڽ��
#define      CJ_YFZHK		(ZCFZB_BEGIN + 61)   //Ӧ��ծ��
#define      CJ_CQYFK		(ZCFZB_BEGIN + 62)   //����Ӧ����
#define      CJ_ZXYFK		(ZCFZB_BEGIN + 63)   //ר��Ӧ����
#define      CJ_QTCQFZ		(ZCFZB_BEGIN + 64)   //�������ڸ�ծ
#define      CJ_ZFZZJ		(ZCFZB_BEGIN + 65)   //ס����ת��
#define      CJ_CQFZHJ		(ZCFZB_BEGIN + 66)   //���ڸ�ծ�ϼ�
#define      CJ_DYSKDX		(ZCFZB_BEGIN + 67)   //����˰�����
#define      CJ_FZHJ		(ZCFZB_BEGIN + 68)   //��ծ�ϼ�
#define      CJ_GB			(ZCFZB_BEGIN + 69)   //�ɱ�

#define      CJ_ZBGJ		(ZCFZB_BEGIN + 70)   //�ʱ�����
#define      CJ_YYGJ		(ZCFZB_BEGIN + 71)   //ӯ�๫��
#define      CJ_FDGYJ		(ZCFZB_BEGIN + 72)   //���������
#define      CJ_WFPLR		(ZCFZB_BEGIN + 73)   //δ��������
#define      CJ_GDQYHJ		(ZCFZB_BEGIN + 74)   //�ɶ�Ȩ��ϼ�
#define      CJ_SSGQ		(ZCFZB_BEGIN + 75)   //������Ȩ
#define      CJ_FZGDQY		(ZCFZB_BEGIN + 76)   //��ծ�͹ɶ�Ȩ��ϼ�

//�ʲ���ծ�������Ŀ
#define      CJ_GDZCJE		(ZCFZB_BEGIN + 79)   //�̶��ʲ�����
#define      CJ_LDBL		(ZCFZB_BEGIN + 80)   //��������
#define      CJ_SDBL		(ZCFZB_BEGIN + 81)   //�ٶ�����
#define      CJ_CSDBL		(ZCFZB_BEGIN + 82)   //���ٶ�����
#define      CJ_XJBL		(ZCFZB_BEGIN + 83)   //�ֽ����
#define      CJ_GDQYBL		(ZCFZB_BEGIN + 84)   //�ɶ�Ȩ�����
#define      CJ_ZCFZBL		(ZCFZB_BEGIN + 85)   //�ʲ���ծ����
#define      CJ_ZBFZBL		(ZCFZB_BEGIN + 86)   //�ʱ���ծ����
#define      CJ_CQFZBL		(ZCFZB_BEGIN + 87)   //���ڸ�ծ����
#define      CJ_GQGDZCBL	(ZCFZB_BEGIN + 88)   //�ɶ�Ȩ����̶��ʲ�����
#define      CJ_YXFZBL		(ZCFZB_BEGIN + 89)   //��Ϣ��ծ����
#define      CJ_ZJGCGGXS	(ZCFZB_BEGIN + 90)   //�ڽ����̸ܸ�ϵ��
#define      CJ_YSLDBL		(ZCFZB_BEGIN + 91)   //����Ӧ���ʿ�/�����ʲ�
#define		 CJ_GJJ			(ZCFZB_BEGIN + 92)	 //������

//�ߡ� ������������
//1�����ݱ����ƣ�LRFPB
//2��˵�������й�˾��ĳ��ʱ���ڣ����ꡢһ�꣩����������������
//3����ṹ
#define LRFPB_BEGIN			SM_FD_BEGIN + 300	  //601

#define      CJ_LQSRQ		(LRFPB_BEGIN + 0)	  //������ʼ����
#define      CJ_ZYYWSR		(LRFPB_BEGIN + 1)     //��Ӫҵ������
#define      CJ_ZYYWCB      (LRFPB_BEGIN + 2)     //��Ӫҵ��ɱ�
#define      CJ_ZYYWSJ		(LRFPB_BEGIN + 3)     //��Ӫҵ��˰�𼰸���
#define      CJ_ZYYWLR		(LRFPB_BEGIN + 4)     //��Ӫҵ������
#define      CJ_QTLR		(LRFPB_BEGIN + 5)     //����ҵ������
#define      CJ_YYFY		(LRFPB_BEGIN + 6)     //Ӫҵ����
#define      CJ_GLFY		(LRFPB_BEGIN + 7)     //�������
#define      CJ_CWFY		(LRFPB_BEGIN + 8)     //�������
#define      CJ_YYLR		(LRFPB_BEGIN + 9)     //Ӫҵ����

#define      CJ_TZSY		(LRFPB_BEGIN + 10)    //Ͷ������
#define      CJ_BTSR		(LRFPB_BEGIN + 11)    //��������
#define      CJ_YYWSR		(LRFPB_BEGIN + 12)    //Ӫҵ������
#define      CJ_YYWZC		(LRFPB_BEGIN + 13)    //Ӫҵ��֧��
#define      CJ_LRZE		(LRFPB_BEGIN + 14)    //�����ܶ�
#define      CJ_SDS			(LRFPB_BEGIN + 15)    //����˰
#define      CJ_LSSGQ		(LRFPB_BEGIN + 16)    //������Ȩ
#define      CJ_WQRTZSS		(LRFPB_BEGIN + 17)    //δȷ�ϵ�Ͷ����ʧ
#define      CJ_JLR			(LRFPB_BEGIN + 18)    //������
#define      CJ_SHLR		(LRFPB_BEGIN + 19)    //˰������

#define      CJ_QCWFPLR		(LRFPB_BEGIN + 20)    //�ڳ�ĩ��������
#define      CJ_SQLRTZ		(LRFPB_BEGIN + 21)    //���������ת
#define      CJ_YYGJJZR		(LRFPB_BEGIN + 22)    //ӯ�๫����ת��
#define      CJ_KGFPLR		(LRFPB_BEGIN + 23)    //�ɹ����������
#define      CJ_TQFDGJ		(LRFPB_BEGIN + 24)    //��ȡ����ӯ�๫��
#define      CJ_TQGYJ		(LRFPB_BEGIN + 25)    //��ȡ���������
#define      CJ_TQZGJL		(LRFPB_BEGIN + 26)    //��ȡְ����������������
#define      CJ_TQCBJJ		(LRFPB_BEGIN + 27)    //��ȡ��������
#define      CJ_TQQYFZ		(LRFPB_BEGIN + 28)    //��ȡ��ҵ��չ����
#define      CJ_LRGHTZ		(LRFPB_BEGIN + 29)    //����黹Ͷ��

#define      CJ_KGGDFPLR	(LRFPB_BEGIN + 30)    //�ɹ��ɶ���������
#define      CJ_YFYXGL		(LRFPB_BEGIN + 31)    //Ӧ�����ȹɹ���
#define      CJ_TQRYGJ		(LRFPB_BEGIN + 32)    //��ȡ����ӯ�๫��
#define      CJ_YFPTGL		(LRFPB_BEGIN + 33)    //Ӧ����ͨ�ɹ���
#define      CJ_ZZGB		(LRFPB_BEGIN + 34)    //ת���ɱ�����ͨ�ɹ���
#define      CJ_LWFPLR		(LRFPB_BEGIN + 35)    //δ��������


#define      CJ_YYFYL		(LRFPB_BEGIN + 49)    //Ӫҵ������
#define      CJ_CWFYL		(LRFPB_BEGIN + 50)    //���������
#define      CJ_YYCBBL		(LRFPB_BEGIN + 51)    //Ӫҵ�ɱ�����
#define      CJ_XSMLL		(LRFPB_BEGIN + 52)    //����ë����
#define      CJ_ZYYWLRL		(LRFPB_BEGIN + 53)    //��Ӫҵ��������
#define      CJ_YYLRL		(LRFPB_BEGIN + 54)    //Ӫҵ������
#define      CJ_SQLRL		(LRFPB_BEGIN + 55)    //˰ǰ������
#define      CJ_SHLRL		(LRFPB_BEGIN + 56)    //˰��������

// ����ʻ��������ʻ���ص��������
#define		 LCZH_BEGIN		(SM_FD_BEGIN + 400)	  // 701

#define		 LCZH_JHBH		(LCZH_BEGIN + 1)	  // �ƻ����
#define		 LCZH_USERID	(LCZH_BEGIN + 2)	  // �û�ID
#define		 LCZH_ZDRQ		(LCZH_BEGIN + 3)	  // �ƻ���ʼ��ʱ��	
#define		 LCZH_JHCG		(LCZH_BEGIN + 4)	  // �ƻ�����	
#define		 LCZH_ZXZT		(LCZH_BEGIN + 5)	  // �ƻ�ִ��״̬	
#define		 LCZH_WTSL		(LCZH_BEGIN + 6)	  // ί������	
#define		 LCZH_MMD		(LCZH_BEGIN + 7)	  // �����۸�
#define		 LCZH_ZYJG		(LCZH_BEGIN + 8)	  // ֹӯ�۸�
#define		 LCZH_MMTJ		(LCZH_BEGIN + 9)	  // ��������
#define		 LCZH_ZSFS		(LCZH_BEGIN + 10)	  // ֹ��ʽ	
#define		 LCZH_ZXZTNAME	(LCZH_BEGIN + 11)	  // �ƻ�ִ��״̬������
#define		 LCZH_NOTE		(LCZH_BEGIN + 12)     // ���׼ƻ��ı�ע		
#define		 LCZH_USERNAME	(LCZH_BEGIN + 13)     // �ʻ������� 
#define		 LCZH_ZSJG		(LCZH_BEGIN + 14)	  // ֹ��۸�	
#define		 LCZH_LASTZSJG	(LCZH_BEGIN + 15)	  // ���һ��ֹ��۸�	
#define		 LCZH_BBJ		(LCZH_BEGIN + 16)	  // �����۸�
#define		 LCZH_CGTS		(LCZH_BEGIN + 17)	  // �ֹ�����
#define		 LCZH_ZBGZ_TYPE	 (LCZH_BEGIN + 18)	  // ָ����ٵĲ�������
#define		 LCZH_ZBGZ_PRICE (LCZH_BEGIN + 19)	  // ָ����ٵĳɽ��۸�
#define		 LCZH_ZBGZ_NAME  (LCZH_BEGIN + 20)	  // ָ����ٵ�ָ������
#define		 LCZH_BCFX		(LCZH_BEGIN + 21)	  // ���η���
#define		 LCZH_YQYL		(LCZH_BEGIN + 22)	  // Ԥ��ӯ��
#define		 LCZH_END		(LCZH_BEGIN + 79)	  // 780

// ͨ��������Ŀ���û��߼���ҳѡ�ɷ��ص����� SuperServerSelectStock
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


// ��Ȩ����
#define		GQFZS_BEGIN		(SM_FD_BEGIN + 500)		  //	801

#define		CJ_GQFZ_FH			(GQFZS_BEGIN + 1)    //��Ȩ���÷ֺ�
#define		CJ_GQFZ_SG			(GQFZS_BEGIN + 2)    //��Ȩ�����͹�
#define		CJ_GQFZ_SM			(GQFZS_BEGIN + 3)    //��Ȩ����˵��
#define		CJ_GQFZ_GOU_XQGS	(GQFZS_BEGIN + 4)	//ÿ���Ϲ�Ȩ֤����Ȩ����
#define		CJ_GQFZ_GOU_XQJG	(GQFZS_BEGIN + 5)	//�Ϲ�Ȩ֤��Ȩ�۸�
#define		CJ_GQFZ_GOU_QZGS	(GQFZS_BEGIN + 6)	//��ͨ�ɹɶ�ÿ10�ɻ����Ϲ�Ȩ֤����
#define		CJ_GQFZ_GU_XQGS		(GQFZS_BEGIN + 7)	//ÿ���Ϲ�Ȩ֤����Ȩ����
#define		CJ_GQFZ_GU_XQJG		(GQFZS_BEGIN + 8)	//�Ϲ�Ȩ֤��Ȩ�۸�
#define		CJ_GQFZ_GU_QZGS		(GQFZS_BEGIN + 9)	//��ͨ�ɹɶ�ÿ10�ɻ����Ϲ�Ȩ֤����
#define		CJ_GQFZ_SUOGU		(GQFZS_BEGIN + 10)	//����ͨ�ɹɶ�ÿ10����Ϊx��
#define		CJ_GQFZ_GQDJR		(GQFZS_BEGIN + 11)	//��Ȩ�Ǽ���
#define		CJ_GQFZ_SSLTR		(GQFZS_BEGIN + 12)	//������ͨ��
#define		CJ_GQFZ_XJFFR		(GQFZS_BEGIN + 13)	//�ֽ𷢷���
#define		CJ_GQFZ_BZ			(GQFZS_BEGIN + 14)	//��ע

#define		GQFZS_END			(GQFZS_BEGIN + 19)	//	820

// ���˰潻�׼ƻ�����
#define		JYJH_BEGIN				(SM_FD_BEGIN + 520) // 821
#define		JYJH_STOCK_TOTAL		(JYJH_BEGIN + 1)	// ÿ����Ʊ���׼ƻ������� 
#define		JYJH_STOCK_FINISH		(JYJH_BEGIN + 2)	// ÿ����Ʊ���׼ƻ���������� 
#define		JYJH_STOCK_SUCC			(JYJH_BEGIN + 3)	// ÿ����Ʊ���׼ƻ��ĳɹ�����
#define		JYJH_STOCK_SUCC_RATE	(JYJH_BEGIN + 4)	// ÿ����Ʊ���׼ƻ��ĳɹ���
#define		JYJH_STOCK_WIN_RATE		(JYJH_BEGIN + 5)	// ÿ����Ʊ���׼ƻ�����������

//�����Ȩ��Ϣ(�����������ӿڶ����)
#define		FXQQ_BEGIN				(SM_FD_BEGIN + 570)		// 871
#define		FXQQ_HBD				FXQQ_BEGIN 				//���Ҷ�(��: EURUSD)
#define		FXQQ_DQR				(FXQQ_BEGIN + 1)		//������(��: 06-07-31)
#define		FXQQ_ZXJG				(FXQQ_BEGIN + 2)		//ִ�м۸�(��: 1.2892)
#define		FXQQ_QQZL				(FXQQ_BEGIN + 3)		//��Ȩ����(����C������P)
#define		FXQQ_END				(SM_FD_BEGIN + 579)		// 880

// Ȩ֤��Ϣ 
#define QZXX_BEGIN				(SM_FD_BEGIN + 580)		// 881
#define QZXX_BDZQ				(QZXX_BEGIN + 0)		//���֤ȯ
#define QZXX_QZLX				(QZXX_BEGIN + 1)		//Ȩ֤����
#define QZXX_QZYE				(QZXX_BEGIN + 2)		//Ȩ֤���
#define QZXX_JSFS				(QZXX_BEGIN + 3)		//���㷽ʽ
#define QZXX_XQFS				(QZXX_BEGIN + 4)		//��Ȩ��ʽ
#define QZXX_JSJG				(QZXX_BEGIN + 5)		//����۸�
#define QZXX_XQJG				(QZXX_BEGIN + 6)		//��Ȩ�۸�
#define QZXX_XQBL				(QZXX_BEGIN + 7)		//��Ȩ����
#define QZXX_QSRQ				(QZXX_BEGIN + 8)		//��ʼ���� 
#define QZXX_JZRQ				(QZXX_BEGIN + 9)		//��ֹ����
#define QZXX_SYRQ				(QZXX_BEGIN + 10)		//ʹ������
#define QZXX_END				(SM_FD_BEGIN + 599)		// 900

//�š� �ֽ�������
//XJLLB
#define XJLLB_BEGIN				SM_FD_BEGIN + 600	//901

#define      CJ_XQSRQ			(XJLLB_BEGIN + 0)    //������ʼ����
#define      CJ_JYR_XS			(XJLLB_BEGIN + 1)    //������Ʒ�ṩ�����յ����ֽ�
#define      CJ_JYR_ZJ			(XJLLB_BEGIN + 2)    //�յ������
#define      CJ_JYR_SFFH		(XJLLB_BEGIN + 3)    //�յ���˰�ѷ���
#define      CJ_JYR_QT			(XJLLB_BEGIN + 4)    //�յ��������뾭Ӫ��йص��ֽ�
#define      CJ_JYRXJ			(XJLLB_BEGIN + 5)    //��Ӫ��������ֽ�����С��
#define      CJ_JYC_GM			(XJLLB_BEGIN + 6)    //������Ʒ��������֧�����ֽ�
#define      CJ_JYC_ZL			(XJLLB_BEGIN + 7)    //��Ӫ������֧�����ֽ�
#define      CJ_JYC_GZ			(XJLLB_BEGIN + 8)    //֧����ְ���Լ�Ϊְ��֧�����ֽ�
#define      CJ_JYC_ZZS			(XJLLB_BEGIN + 9)    //֧������ֵ˰��
#define      CJ_JYC_SDS			(XJLLB_BEGIN + 10)   //֧��������˰��
#define      CJ_JYC_QTS			(XJLLB_BEGIN + 11)   //֧���ĳ���ֵ˰����˰���������˰��
#define      CJ_JYC_QT			(XJLLB_BEGIN + 12)   //֧��������Ԥ��Ӫ��йص��ֽ�
#define      CJ_JYCXJ			(XJLLB_BEGIN + 13)   //��Ӫ��������ֽ�����С��
#define      CJ_JYJE			(XJLLB_BEGIN + 14)   //��Ӫ��������ֽ���������
#define      CJ_TZR_HB			(XJLLB_BEGIN + 15)   //�ջ�Ͷ�����յ����ֽ�
#define      CJ_TZR_SYXJ		(XJLLB_BEGIN + 16)   //ȡ��Ͷ���������յ����ֽ�
#define      CJ_TZR_CQZC		(XJLLB_BEGIN + 17)   //���ù̶��ʲ������ʲ������������ʲ����յ����ֽ𾻶�
#define      CJ_TZR_QT			(XJLLB_BEGIN + 18)   //�յ���������Ͷ�ʻ�йص��ֽ�𾻶�
#define      CJ_TZRXJ			(XJLLB_BEGIN + 19)   //Ͷ�ʻ���������ֽ�����С��
#define      CJ_TZC_CQZC		(XJLLB_BEGIN + 20)   //�����̶��ʲ������ʲ������������ʲ���֧�����ֽ�
#define      CJ_TZC_QYTZ		(XJLLB_BEGIN + 21)   //Ȩ����Ͷ����֧�����ֽ��
#define      CJ_TZC_ZQTZ		(XJLLB_BEGIN + 22)   //ծȨ��Ͷ����֧�����ֽ�
#define      CJ_TZC_QT			(XJLLB_BEGIN + 23)   //֧����������Ͷ�ʻ�йص��ֽ�
#define      CJ_TZCXJ			(XJLLB_BEGIN + 24)   //Ͷ�ʻ���������ֽ�����С��
#define      CJ_TZJE			(XJLLB_BEGIN + 25)   //Ͷ�ʻ���������ֽ���������
#define      CJ_MZR_QYTZ		(XJLLB_BEGIN + 26)   //����Ȩ����Ͷ�����յ����ֽ�
#define      CJ_MZR_FXZQ		(XJLLB_BEGIN + 27)   //����ծȯ���յ����ֽ�
#define      CJ_MZR_JZ			(XJLLB_BEGIN + 28)   //��ծ���յ����ֽ�
#define      CJ_MZR_QT			(XJLLB_BEGIN + 29)   //�յ�����������ʻ�йص��ֽ�
#define      CJ_MZRXJ			(XJLLB_BEGIN + 30)   //���ʻ�������ֽ�����С��
#define      CJ_MZC_CHZW		(XJLLB_BEGIN + 31)   //����ծ����֧�����ֽ�
#define      CJ_MZC_MZFY		(XJLLB_BEGIN + 32)   //�������ʷ�������֧�����ֽ�
#define      CJ_MZC_FPGL		(XJLLB_BEGIN + 33)   //���������������֧�����ֽ�
#define      CJ_MZC_CFLX		(XJLLB_BEGIN + 34)   //������Ϣ��֧�����ֽ�
#define      CJ_MZC_RZZL		(XJLLB_BEGIN + 35)   //����������֧�����ֽ�
#define      CJ_MZC_JZCZ		(XJLLB_BEGIN + 36)   //����ע���ʱ�֧�����ֽ�
#define      CJ_MZC_QT			(XJLLB_BEGIN + 37)   //֧������������ʻ�йص��ֽ�
#define      CJ_MZCXJ			(XJLLB_BEGIN + 38)   //���ʻ�������ֽ�����С��
#define      CJ_MZJE			(XJLLB_BEGIN + 39)   //���ʻ�������ֽ���������
#define      CJ_HLBD			(XJLLB_BEGIN + 40)   //���ʱ䶯���ֽ��Ӱ���
#define      CJ_XJJZJ			(XJLLB_BEGIN + 41)   //�ֽ��ֽ�ȼ��ﾻ���Ӷ�
#define      CJ_XSSGQ			(XJLLB_BEGIN + 42)   //�����ɶ�����
#define      CJ_JTZCJZZB		(XJLLB_BEGIN + 43)   //������ʲ���ֵ׼��
#define      CJ_GDZCZJ			(XJLLB_BEGIN + 44)   //�̶��ʲ��۾�
#define      CJ_WXZCTX			(XJLLB_BEGIN + 45)   //�����ʲ�̯��
#define      CJ_QTZCTX			(XJLLB_BEGIN + 46)   //���ڴ�̯����̯��
#define      CJ_CZSS			(XJLLB_BEGIN + 47)   //���ù̶��ʲ������ʲ������������ʲ�����ʧ�������棩
#define      CJ_GDZCSS			(XJLLB_BEGIN + 48)   //�̶��ʲ�������ʧ
#define      CJ_XCWFY			(XJLLB_BEGIN + 49)   //�������
#define      CJ_TZSS			(XJLLB_BEGIN + 50)   //Ͷ����ʧ�������棩
#define      CJ_XDYSKDX			(XJLLB_BEGIN + 51)   //����˰���������
#define      CJ_CHJS			(XJLLB_BEGIN + 52)   //����ļ��٣������ӣ�
#define      CJ_JYYSJS			(XJLLB_BEGIN + 53)   //��Ӫ��Ӧ����Ŀ�ļ��٣������ӣ�
#define      CJ_JYYFJS			(XJLLB_BEGIN + 54)   //��Ӫ��Ӧ����Ŀ�����ӣ������٣�
#define      CJ_ZZSZJJE			(XJLLB_BEGIN + 55)   //��ֵ˰���Ӿ�������٣�
#define      CJ_QT				(XJLLB_BEGIN + 56)   //����
#define      CJ_ZWZZB			(XJLLB_BEGIN + 57)   //ծ��תΪ�ʱ�
#define      CJ_YNDQZQ			(XJLLB_BEGIN + 58)   //һ���ڵ��ڵĿ�ת����˾ծȯ
#define      CJ_RZGDZC			(XJLLB_BEGIN + 59)   //��������̶��ʲ�
#define      CJ_XJQMYE			(XJLLB_BEGIN + 60)   //�ֽ����ĩ���
#define      CJ_XJQCYE			(XJLLB_BEGIN + 61)   //�ֽ���ڳ����
#define      CJ_DJWQMYE			(XJLLB_BEGIN + 62)   //�ֽ�ȼ������ĩ���
#define      CJ_DJWQCYE			(XJLLB_BEGIN + 63)   //�ֽ�ȼ�����ڳ����

//ʮ�� ������Ŀ
#define JSXM_BEGIN				SM_FD_BEGIN + 700	//1001

#define      CJ_GBSYL			(JSXM_BEGIN + 0)    //�ɱ�������
#define      CJ_MGYL			(JSXM_BEGIN + 1)    //ÿ��ӯ��
#define      CJ_YSZKZZL			(JSXM_BEGIN + 2)    //Ӧ���ʿ���ת��
#define      CJ_YSZKZZTS		(JSXM_BEGIN + 3)    //Ӧ���ʿ���ת����
#define      CJ_MGJZC			(JSXM_BEGIN + 4)    //ÿ�ɾ��ʲ�
#define      CJ_JZCTZXS			(JSXM_BEGIN + 5)    //���ʲ�����ϵ��Kֵ
#define      CJ_SXFYZZL			(JSXM_BEGIN + 6)    //�������������
#define      CJ_CHZZL			(JSXM_BEGIN + 7)    //�����ת��
#define      CJ_CHZZTS			(JSXM_BEGIN + 9)    //�����ת����
#define      CJ_GDZCZZL			(JSXM_BEGIN + 10)   //�̶��ʲ���ת��
#define      CJ_ZZCZZL			(JSXM_BEGIN + 11)   //���ʲ���ת��
#define      CJ_GQZZL			(JSXM_BEGIN + 12)   //�ɶ�Ȩ����ת��
#define      CJ_ZYYWSRZZL		(JSXM_BEGIN + 13)   //��Ӫҵ������������
#define      CJ_ZCSYL			(JSXM_BEGIN + 14)   //�ʲ�������
#define      CJ_JZCSYL			(JSXM_BEGIN + 15)   //���ʲ�������
#define      CJ_ZZCHBL			(JSXM_BEGIN + 16)   //���ʲ��ر���
#define      CJ_XSXJZYSRBL		(JSXM_BEGIN + 17)   //������Ʒ�յ��ֽ�����Ӫҵ���������
#define      CJ_JYXJLRBL		(JSXM_BEGIN + 18)   //��Ӫ��������ֽ����������뾻�������
#define      CJ_MGXJZJ			(JSXM_BEGIN + 19)   //ÿ���ֽ��ֽ�ȼ��ﾻ���Ӷ�

#define HXLC_BEGIN				(SM_FD_BEGIN + 809)	// 1110 �������
#define CJ_STAR					(HXLC_BEGIN + 0)	// �Ǽ�

#define CJ_STAR_PLATE			(HXLC_BEGIN + 1)	// x:�Ǽ�-y:����
#define CJ_GROW_PLATE			(HXLC_BEGIN + 2)	// x:�ɳ���-y:����
#define CJ_WALK_PLATE			(HXLC_BEGIN + 3)	// x:����-y:����
#define CJ_RISK_PLATE			(HXLC_BEGIN + 4)	// x:����-y:����

#define CJ_STOCK_DIARY			(HXLC_BEGIN + 10)	// �����ռǵ���ʾ

#define CJ_PRICE_MEMO			(HXLC_BEGIN + 86)	// 1196 �۸����䱸ע
#define CJ_PRICE_LOW			(HXLC_BEGIN + 87)	// 1197	�۸�����ͼ۸�
#define CJ_PRICE_UP				(HXLC_BEGIN + 88)	// 1198 �۸�����߼۸�
#define HXLC_END				(HXLC_BEGIN + 89)	// 1199

//��ͳ�Ƶ�������Ŀ
#define	CJ_TJ_ZJLR				1333				//�ʽ�����
#define	CJ_TJ_ZJLC				1334				//�ʽ�����

#define CJ_REAL_BEGIN1			1335				//��ʵʱ�仯�Ĳ������ݿ�ʼ1
#define CJ_DD_Z_BUY				1340				//�����������
#define CJ_DD_Z_BUY_COUNT		1341				//�����������
#define CJ_DD_Z_SELL			1342				//������������
#define CJ_DD_Z_SELL_COUNT		1343				//������������

#define CJ_DD_B_BUY				1344				//�����������
#define CJ_DD_B_BUY_COUNT		1345				//�����������
#define CJ_DD_B_SELL			1346				//������������
#define CJ_DD_B_SELL_COUNT		1347				//������������

#define CJ_REAL_END1			1349				//��ʵʱ�仯�Ĳ������ݽ���1

#define CJ_REAL_BEGIN2			1380				//��ʵʱ�仯�Ĳ������ݿ�ʼ2
#define CJ_DD_Z_BUY_AMT			1380				//����������
#define CJ_DD_Z_SELL_AMT		1381				//�����������
#define CJ_DD_B_BUY_AMT			1382				//����������
#define CJ_DD_B_SELL_AMT		1383				//�����������

#define CJ_REAL_END2			1400				//��ʵʱ�仯�Ĳ������ݽ���2

//ʮһ��������Ŀ

#define	JJXM_BEGIN				SM_FD_BEGIN + 1100	// 1401

#define	JJXM_END				SM_FD_BEGIN + 1300	// 1601

// ���ӵĹɱ��ṹ
#define GBJG2_BEGIN				SM_FD_BEGIN + 1369	// 1670
#define CJ_AG					GBJG2_BEGIN + 4		// 1674 ��ͨA��
#define GBJG2_END				SM_FD_BEGIN + 1374	// 1675

// ʮ��ɶ�
#define SDGD_BEGIN				SM_FD_BEGIN + 1375	// 1676
#define SDGD_END				SM_FD_END	+ 1394	// 1695

// �������2
#define LRFP2_BEGIN				SM_FD_BEGIN + 1429	// 1730
#define LRFP2_END				SM_FD_END	+ 1441	// 1742

// �ֽ�����
#define	XJLL2_BEGIN				SM_FD_BEGIN + 1444	// 1745
#define XJLL2_END				SM_FD_END	+ 1455	// 1756

// �ʲ���ծ
#define ZCFZ2_BEGIN				SM_FD_BEGIN + 1456	// 1757
#define ZCFZ2_END				SM_FD_END	+ 1522	// 1823

// �������3
#define LRFP3_BEGIN				SM_FD_BEGIN + 1524	// 1825
#define LRFP3_END				SM_FD_BEGIN + 1614	// 1915

// ����ע
#define CWFZ_BEGIN				SM_FD_BEGIN + 1615	// 1916
#define CWFZ_END				SM_FD_END	+ 1642	// 1943

// ��ծ����
#define GZZL_BEGIN				SM_FD_BEGIN	+ 1649	// 1950
#define GZZL_END				SM_FD_END	+ 1662	// 1963

#define	SM_FD_END				SM_FD_BEGIN + 1800	//2101 �ƾ����ݿ��������ֵ�Ľ���

///////////////////////////////////////////////////////////////////////////////////////////
//ί��������(Ԥ��100�������ԴӸ�λ��չ��
#define SM_WT_BEGIN			SM_FD_END + 1			//2102 ί�����ݶ��忪ʼ
#define SM_WT_END			SM_WT_BEGIN + 100		//2202 ί�����ݶ������

/////////////////////////////////////////////////////////////////////////////////////////
//�ڲ��������޹�ʽ��
#define SM_FUNC_BEGIN		SM_WT_END + 1			//�������忪ʼ =2203
//
//���ú���											//2204
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
#define SM_FUNC_SUM			(SM_FUNC_BEGIN + 16)	//���
#define SM_FUNC_SUMBARS		(SM_FUNC_BEGIN + 17)	//
#define SM_FUNC_WMA			(SM_FUNC_BEGIN + 18)	//��Ȩ�ƶ�ƽ��
#define SM_FUNC_REFX		(SM_FUNC_BEGIN + 19)	//�������
//�߼�����											//2224
#define SM_FUNC_IF			(SM_FUNC_BEGIN + 21)	//
#define SM_FUNC_ISDOWN		(SM_FUNC_BEGIN + 22)	//
#define SM_FUNC_ISEQUAL		(SM_FUNC_BEGIN + 23)	//
#define SM_FUNC_ISUP		(SM_FUNC_BEGIN + 24)	//
//��������											//2234
#define SM_FUNC_ABS			(SM_FUNC_BEGIN + 31)	//����ֵ
#define SM_FUNC_BETWEEN		(SM_FUNC_BEGIN + 32)	//
#define SM_FUNC_CROSS		(SM_FUNC_BEGIN + 33)	//
#define SM_FUNC_LONGCROSS	(SM_FUNC_BEGIN + 34)	//
#define SM_FUNC_MAX			(SM_FUNC_BEGIN + 35)	//���ֵ
#define SM_FUNC_MIN			(SM_FUNC_BEGIN + 36)	//��Сֵ
#define SM_FUNC_MOD			(SM_FUNC_BEGIN + 37)	//
#define SM_FUNC_NOT			(SM_FUNC_BEGIN + 38)	//
#define SM_FUNC_RANGE		(SM_FUNC_BEGIN + 39)	//
#define SM_FUNC_REVERSE		(SM_FUNC_BEGIN + 40)	//
#define SM_FUNC_SGN			(SM_FUNC_BEGIN + 41)	//
#define SM_FUNC_SUBSAMEDAY	(SM_FUNC_BEGIN + 42)	//ͬһ���
//��ѧ����											
#define SM_FUNC_DIV			(SM_FUNC_BEGIN + 49)	//
#define SM_FUNC_RAND		(SM_FUNC_BEGIN + 50)	//
#define SM_FUNC_ACOS		(SM_FUNC_BEGIN + 51)	////2254
#define SM_FUNC_ASIN		(SM_FUNC_BEGIN + 52)	//
#define SM_FUNC_ATAN		(SM_FUNC_BEGIN + 53)	//
#define SM_FUNC_CEILING		(SM_FUNC_BEGIN + 54)	//
#define SM_FUNC_COS			(SM_FUNC_BEGIN + 55)	//����
#define SM_FUNC_EXP			(SM_FUNC_BEGIN + 56)	//
#define SM_FUNC_FLOOR		(SM_FUNC_BEGIN + 57)	//
#define SM_FUNC_INTPART		(SM_FUNC_BEGIN + 58)	//
#define SM_FUNC_LN			(SM_FUNC_BEGIN + 59)	//
#define SM_FUNC_LOG			(SM_FUNC_BEGIN + 60)	//
#define SM_FUNC_POW			(SM_FUNC_BEGIN + 61)	//
#define SM_FUNC_SIN			(SM_FUNC_BEGIN + 62)	//����
#define SM_FUNC_SQRT		(SM_FUNC_BEGIN + 63)	//
#define SM_FUNC_TAN			(SM_FUNC_BEGIN + 64)	//
#define SM_FUNC_GZSY		(SM_FUNC_BEGIN + 65)	//������Ϣ���ڵĹ�ծ�����ʹ�ʽ
#define SM_FUNC_SYFX		(SM_FUNC_BEGIN + 66)	//��ʣ���ծ��Ϣ����
#define SM_FUNC_XCFX		(SM_FUNC_BEGIN + 67)	//���ծ�´θ�Ϣ����

//ͳ�ƺ���											//
#define SM_FUNC_SKEW		(SM_FUNC_BEGIN + 69)	//�ֲ���ƫб��
#define SM_FUNC_KURT		(SM_FUNC_BEGIN + 70)	//���ݼ��ķ�ֵ
#define SM_FUNC_AVEDEV		(SM_FUNC_BEGIN + 71)	//
#define SM_FUNC_DEVSQ		(SM_FUNC_BEGIN + 72)	//
#define SM_FUNC_FORCAST		(SM_FUNC_BEGIN + 73)	//
#define SM_FUNC_SLOPE		(SM_FUNC_BEGIN + 74)	//
#define SM_FUNC_STD			(SM_FUNC_BEGIN + 75)	//
#define SM_FUNC_STDP		(SM_FUNC_BEGIN + 76)	//
#define SM_FUNC_VAR			(SM_FUNC_BEGIN + 77)	//
#define SM_FUNC_VARP		(SM_FUNC_BEGIN + 78)	//
#define SM_FUNC_RELATE		(SM_FUNC_BEGIN + 79)	//���ϵ��
#define SM_FUNC_COVAR		(SM_FUNC_BEGIN + 80)	//Э����
//ָ�꺯��											//2284
#define SM_FUNC_COST		(SM_FUNC_BEGIN + 81)	//
#define SM_FUNC_PEAK		(SM_FUNC_BEGIN + 82)	//
#define SM_FUNC_PEAKBARS	(SM_FUNC_BEGIN + 83)	//
#define SM_FUNC_SAR			(SM_FUNC_BEGIN + 84)	//
#define SM_FUNC_SARTURN		(SM_FUNC_BEGIN + 85)	//
#define SM_FUNC_TROUGH		(SM_FUNC_BEGIN + 86)	//
#define SM_FUNC_TROUGHBARS	(SM_FUNC_BEGIN + 87)	//
#define SM_FUNC_WINNER		(SM_FUNC_BEGIN + 88)	//
#define SM_FUNC_ZIG			(SM_FUNC_BEGIN + 89)	//
#define SM_FUNC_PWINNER		(SM_FUNC_BEGIN + 90)	//Զ�ڻ�������
#define SM_FUNC_FLATZIG		(SM_FUNC_BEGIN + 92)	//
//													//2294
#define SM_FUNC_ISNULL		(SM_FUNC_BEGIN + 91)	//
//����
#define SM_FUNC_LASTREP		(SM_FUNC_BEGIN + 94)	//ȡ�������
#define SM_FUNC_REPDATE		(SM_FUNC_BEGIN + 95)	//ȡ��������
#define SM_FUNC_GETREPTYPE	(SM_FUNC_BEGIN + 96)	//ȡ��������
#define SM_FUNC_REP			(SM_FUNC_BEGIN + 97)	//ȡͬ�ڱ���
#define SM_FUNC_YEARREP		(SM_FUNC_BEGIN + 98)	//ȡ�걨
#define SM_FUNC_MIDREP		(SM_FUNC_BEGIN + 99)	//ȡ�б�
#define SM_FUNC_QUARTERREP	(SM_FUNC_BEGIN + 100)	//ȡ����
//ʱ�亯��											//2304
#define SM_FUNC_FORMATTIME		(SM_FUNC_BEGIN + 101)	//
#define SM_FUNC_VALIDBEGINTIME	(SM_FUNC_BEGIN + 102)	//��ʼʱ��
#define SM_FUNC_VALIDENDTIME	(SM_FUNC_BEGIN + 103)	//��ֹʱ��
#define SM_FUNC_BARPOS			(SM_FUNC_BEGIN + 104)	//K��λ��
#define SM_FUNC_FROMNIGHT		(SM_FUNC_BEGIN + 106)	//
#define SM_FUNC_FROMOPEN		(SM_FUNC_BEGIN + 107)	//
#define SM_FUNC_TRADETIME		(SM_FUNC_BEGIN + 108)	//�ܿ���ʱ��
#define SM_FUNC_COUNTTIME		(SM_FUNC_BEGIN + 109)	//
//��Ȩ													//2313
#define SM_FUNC_FUQUAN			(SM_FUNC_BEGIN + 110)	//��Ȩ
#define SM_FUNC_FUQUAN_ADVANCE	(SM_FUNC_BEGIN + 110)	//�߼���Ȩ
#define SM_FUNC_FUQUAN_BACK		(SM_FUNC_BEGIN + 111)	//���Ȩ
#define SM_FUNC_FUQUAN_FOREWARD	(SM_FUNC_BEGIN + 112)	//��ǰ��Ȩ
#define IS_FUNC_FUQUAN(x)		((x)>=SM_FUNC_FUQUAN && (x)<=SM_FUNC_FUQUAN_FOREWARD)
//
#define SM_FUNC_CM				(SM_FUNC_BEGIN + 113)	//�ɱ��ֲ�
#define SM_FUNC_PERPRICE		(SM_FUNC_BEGIN + 114)	//�ּ�
//
#define SM_FUNC_GROUPDATA		(SM_FUNC_BEGIN + 116)	//ȡ��ش���������ͳ��ֵ
#define SM_FUNC_PLACEOFSORT		(SM_FUNC_BEGIN + 117)	//ȡ����������λ��
#define SM_FUNC_INDEXDATA		(SM_FUNC_BEGIN + 118)	//ȡ����������
//���ָ��														//2323
#define SM_FUNC_BLOCKINDEX		(SM_FUNC_BEGIN + 120)	//���ָ������
#define SM_FUNC_BLOCKSUM		(SM_FUNC_BEGIN + 121)	//������
#define SM_FUNC_BLOCKMAX		(SM_FUNC_BEGIN + 122)	//������ֵ
#define SM_FUNC_BLOCKMIN		(SM_FUNC_BEGIN + 123)	//�����Сֵ
#define SM_FUNC_BLOCKAVG		(SM_FUNC_BEGIN + 124)	//���ƽ��
#define SM_FUNC_BLOCKSTD		(SM_FUNC_BEGIN + 125)	//����׼��
#define SM_FUNC_BLOCKCOUNT		(SM_FUNC_BEGIN + 126)	//ȡ����Ʊ��
#define SM_FUNC_BLOCKLEAD		(SM_FUNC_BEGIN + 129)	//ȡ������ȹ�Ʊ������
#define SM_FUNC_BLOCKDATA		(SM_FUNC_BEGIN + 130)	//���ͳ��
//
#define SM_FUNC_PERIODNAME		(SM_FUNC_BEGIN + 140)	//ȡ��ǰ��������
#define SM_FUNC_INBLOCK			(SM_FUNC_BEGIN + 141)	//�жϵ�ǰ�����Ƿ�����ĳ���
#define SM_FUNC_BROKERINFO		(SM_FUNC_BEGIN + 142)	//ȡ�۹�ȯ�̱����Ϣ
//���ݷ����Һ���
#define SM_FUNC_RGB				(SM_FUNC_BEGIN + 148)	//RGB��ɫ
#define SM_FUNC_STRIP			(SM_FUNC_BEGIN + 149)	//����ɫ
#define SM_FUNC_DYNAINFO		(SM_FUNC_BEGIN + 150)	//ȡʵʱ����
#define SM_FUNC_FINANCE			(SM_FUNC_BEGIN + 151)	//ȡ��������
#define SM_FUNC_DRAWICON		(SM_FUNC_BEGIN + 152)	//��ͼ��
#define SM_FUNC_DRAWLINE		(SM_FUNC_BEGIN + 153)	//��ֱ��
#define SM_FUNC_DRAWTEXT		(SM_FUNC_BEGIN + 154)	//������
#define SM_FUNC_POLYLINE		(SM_FUNC_BEGIN + 155)	//������
#define SM_FUNC_STICKLINE		(SM_FUNC_BEGIN + 156)	//������
#define SM_FUNC_DRAWBMP			(SM_FUNC_BEGIN + 157)	//��λͼ
#define SM_FUNC_DRAWGBK			(SM_FUNC_BEGIN + 158)	//������䱳��
#define SM_FUNC_DRAWGBKLAST		(SM_FUNC_BEGIN + 159)	//���������䱳��
#define SM_FUNC_FILLRGN			(SM_FUNC_BEGIN + 160)	//�����������
#define SM_FUNC_PARTLINE		(SM_FUNC_BEGIN + 161)	//��������
#define SM_FUNC_TIPTEXT			(SM_FUNC_BEGIN + 162)	//��ʾ����
#define SM_FUNC_VERTLINE		(SM_FUNC_BEGIN + 163)	//����ֱ��
#define SM_FUNC_ZIGLINE			(SM_FUNC_BEGIN + 164)	//�������
#define SM_FUNC_HORLINE			(SM_FUNC_BEGIN + 165)	//��ˮƽ��
#define SM_FUNC_DWAWOWNER		(SM_FUNC_BEGIN + 166)	//�Զ���ͼ��ʽ
#define SM_FUNC_ANGLELINE		(SM_FUNC_BEGIN + 167)	//�Ƕ���
#define SM_FUNC_DRAWWATERMARK	(SM_FUNC_BEGIN + 168)	//���������䱳��
//
#define SM_FUNC_INDEXO			(SM_FUNC_BEGIN + 170)	//���̿��̼�
#define SM_FUNC_INDEXC			(SM_FUNC_BEGIN + 171)	//�������̼�
#define SM_FUNC_INDEXH			(SM_FUNC_BEGIN + 172)	//������߼�
#define SM_FUNC_INDEXL			(SM_FUNC_BEGIN + 173)	//������ͼ�
#define SM_FUNC_INDEXV			(SM_FUNC_BEGIN + 174)	//���̳ɽ���
#define SM_FUNC_INDEXM			(SM_FUNC_BEGIN + 175)	//���̳ɽ���
//�ַ�������
#define SM_FUNC_STRFIND			(SM_FUNC_BEGIN + 180)	//�ַ�������
#define SM_FUNC_STRLEFT			(SM_FUNC_BEGIN + 181)	//�ַ�����
#define SM_FUNC_STRMID			(SM_FUNC_BEGIN + 182)	//�ַ����в�
#define SM_FUNC_STRRIGHT		(SM_FUNC_BEGIN + 183)	//�ַ����Ҳ�
#define SM_FUNC_TOSTRING		(SM_FUNC_BEGIN + 184)	//ת�����ַ���
#define SM_FUNC_STKNAME			(SM_FUNC_BEGIN + 185)	//��Ʊ����
//"���������"������ɫ�Ĳ���֮��
#define SM_FUNC_QL_SQZD			(SM_FUNC_BEGIN + 200)	//�����ǵ�����
//ũ��ת��
#define SM_FUNC_SOLARTERM		(SM_FUNC_BEGIN + 201)	//����
#define SM_FUNC_LUNARDATE		(SM_FUNC_BEGIN + 202)	//ũ��
//���ں���
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
#define SM_FUNC_STAT_BUYVOL			(SM_FUNC_BEGIN + 212)	//����󵥳ɽ��� 
#define SM_FUNC_STAT_BUYCOUNT		(SM_FUNC_BEGIN + 213)	//����󵥸��� 
#define SM_FUNC_STAT_SELLVOL		(SM_FUNC_BEGIN + 214)	//�����󵥳ɽ��� 
#define SM_FUNC_STAT_SELLCOUNT		(SM_FUNC_BEGIN + 215)	//�����󵥸��� 
//
#define SM_FUNC_UPPERPRICE		(SM_FUNC_BEGIN + 216)	//��ͣ�۸�
#define SM_FUNC_LOWERPRICE		(SM_FUNC_BEGIN + 217)	//��ͣ�۸�
#define SM_FUNC_BONDYIELD		(SM_FUNC_BEGIN + 219)	//������

#define SM_FUNC_ISLASTBAR		(SM_FUNC_BEGIN + 220)	//�Ƿ������һ������
//�޸ľֲ�����
#define SM_FUNC_SETVALUE		(SM_FUNC_BEGIN + 221)	//������ʷ��δ����ĳ��ֵ

#define SM_FUNC_BONDMACDISCRETE	(SM_FUNC_BEGIN + 222)	//��ʽ����K��
#define SM_FUNC_BONDPRICE		(SM_FUNC_BEGIN + 223)	//ȫ��
#define SM_FUNC_REMAINPERIOD	(SM_FUNC_BEGIN + 224)	//ʣ������225-227��iFinDԤ��
#define SM_FUNC_BONDVALUE		(SM_FUNC_BEGIN + 228)	//��ծ��ֵ 
//gykͨ���ź�������
//���ú���
#define SM_FUNC_TMA		        (SM_FUNC_BEGIN + 230)	//TMA�ƶ�ƽ��
#define SM_FUNC_TR		        (SM_FUNC_BEGIN + 231)	//��ʵ����
#define SM_FUNC_DRAWNULL	    (SM_FUNC_BEGIN + 232)	//��Ч��
#define SM_FUNC_CURRBARSCOUNT	(SM_FUNC_BEGIN + 105)	//��������յ����������Ϳͻ��˱���һ��
#define SM_FUNC_TOTALBARSCOUNT	(SM_FUNC_BEGIN + 234)	//�ܵ�������
#define SM_FUNC_BARSNSINCE		(SM_FUNC_BEGIN + 235)	//N�������׸���������λ��
#define SM_FUNC_BARSLASTCOUNT	(SM_FUNC_BEGIN + 236)	//����������������
#define SM_FUNC_HOD		        (SM_FUNC_BEGIN + 237)	//��ֵ����
#define SM_FUNC_LOD		        (SM_FUNC_BEGIN + 238)	//��ֵ����
#define SM_FUNC_REFV		    (SM_FUNC_BEGIN + 239)	//������������ǰ������(δ��ƽ������),��REFʵ��
#define SM_FUNC_REFXV		    (SM_FUNC_BEGIN + 240)	//�����������ں������(ƽ������)
#define SM_FUNC_REFDATE		    (SM_FUNC_BEGIN + 241)	//ָ������
#define SM_FUNC_FILTERX		    (SM_FUNC_BEGIN + 242)	//�������
#define SM_FUNC_TFILTER		    (SM_FUNC_BEGIN + 243)	//�����źŹ��ˣ������������ֵĽ����ź�???
#define SM_FUNC_TTFILTER		(SM_FUNC_BEGIN + 244)	//���˶�ս����ź�???
#define SM_FUNC_MEMA		    (SM_FUNC_BEGIN + 245)	//ƽ���ƶ�ƽ��
#define SM_FUNC_EXPMA		    (SM_FUNC_BEGIN + 246)	//ָ���ƶ�ƽ��
#define SM_FUNC_EXPMEMA		    (SM_FUNC_BEGIN + 247)	//ָ��ƽ���ƶ�ƽ��,����ʵ�֣���EMA
#define SM_FUNC_XMA		        (SM_FUNC_BEGIN + 248)	//ƫ���ƶ�ƽ��
#define SM_FUNC_CONST		    (SM_FUNC_BEGIN + 249)	//ȡֵ��Ϊ����
#define SM_FUNC_TOPRANGE		(SM_FUNC_BEGIN + 250)	//��ǰֵ�ǽ����������ڵ����ֵ
#define SM_FUNC_LOWRANGE		(SM_FUNC_BEGIN + 251)	//��ǰֵ�ǽ����������ڵ���Сֵ
#define SM_FUNC_FINDHIGH		(SM_FUNC_BEGIN + 252)	//Ѱ��ָ�������ڵ��ض����ֵ
#define SM_FUNC_FINDHIGHBARS	(SM_FUNC_BEGIN + 253)	//Ѱ��ָ�������ڵ��ض����ֵ���������ڵ�������
#define SM_FUNC_FINDLOW		    (SM_FUNC_BEGIN + 254)	//Ѱ��ָ�������ڵ��ض���Сֵ
#define SM_FUNC_FINDLOWBARS		(SM_FUNC_BEGIN + 255)	//Ѱ��ָ�������ڵ��ض���Сֵ���������ڵ�������

//�߼�����
#define SM_FUNC_UPNDAY          (SM_FUNC_BEGIN + 260)   //����N��
#define SM_FUNC_DOWNNDAY        (SM_FUNC_BEGIN + 261)   //����N��
#define SM_FUNC_NDAY            (SM_FUNC_BEGIN + 262)   //����N�����X>Y
#define SM_FUNC_EXIST           (SM_FUNC_BEGIN + 263)   //N���ڴ�����������
#define SM_FUNC_EVERY           (SM_FUNC_BEGIN + 264)   //N����һֱ������������
#define SM_FUNC_LAST            (SM_FUNC_BEGIN + 265)   //��������
#define SM_FUNC_TESTSKIP        (SM_FUNC_BEGIN + 266)   //�Ƿ�ʹ˷���
//��������
#define SM_FUNC_IFN             (SM_FUNC_BEGIN + 267)   //�߼��ж�
//��ѧ����
#define SM_FUNC_FRACPART        (SM_FUNC_BEGIN + 268)   //ȥ����С������
#define SM_FUNC_ROUND           (SM_FUNC_BEGIN + 269)   //������������ֵ
#define SM_FUNC_SIGN            (SM_FUNC_BEGIN + 270)   //���ط���
//ʱ�亯��
#define SM_FUNC_TFILT           (SM_FUNC_BEGIN + 271)   //��ָ��ʱ������ݽ��й���
#define SM_FUNC_DATETODAY       (SM_FUNC_BEGIN + 272)   //ָ����1990.12.19������
#define SM_FUNC_DAYTODATE       (SM_FUNC_BEGIN + 273)   //��1990.12.19��������������
#define SM_FUNC_TIMETOSEC       (SM_FUNC_BEGIN + 274)   //��ָ��ʱ�̾���0ʱ�ж೤
#define SM_FUNC_SECTOTIME       (SM_FUNC_BEGIN + 275)   //��0ʱ����������ʲôʱ��
//��������
#define SM_FUNC_TOTALCAPITAL    (SM_FUNC_BEGIN + 276)   //��ǰ�ܹɱ�
#define SM_FUNC_CAPITAL		    (SM_FUNC_BEGIN + 277)	//��ͨ�ɱ�(��)
//���麯��
#define SM_FUNC_ISBUYORDER		    (SM_FUNC_BEGIN + 280)	//��������
#define SM_FUNC_ISSELLORDER		    (SM_FUNC_BEGIN + 281)	//����������
#define SM_FUNC_DCLOSE		    (SM_FUNC_BEGIN + 282)	//��һ�����̼�֮��ת������̼�
#define SM_FUNC_DOPEN		    (SM_FUNC_BEGIN + 283)	//����һ�����̼۵�֮��ת���ĵ�һ�����̼�
#define SM_FUNC_DHIGH		    (SM_FUNC_BEGIN + 284)	//����һ�����̼۵�֮��ת������߼�
#define SM_FUNC_DLOW		    (SM_FUNC_BEGIN + 285)	//����һ�����̼۵�֮��ת������ͼ�
#define SM_FUNC_DVOL		    (SM_FUNC_BEGIN + 286)	//����һ�����̼۵�֮��ת�����ۻ���*100
#define SM_FUNC_NAMELIKE		    (SM_FUNC_BEGIN + 287)	//ģ����Ʊ����
#define SM_FUNC_CODELIKE		    (SM_FUNC_BEGIN + 288)	//ģ����Ʊ����

#define SM_FUNC_END			(SM_FUNC_BEGIN + 300)		//�����������

// �ڲ�������չ
#define SM_EXT_FUNC_BEGIN             0x00010000 + SM_FUNC_BEGIN

#define SM_EXT_FUNC_DRAWTEXTABS       (SM_EXT_FUNC_BEGIN + 1)	            //����λ����ʾ����
#define SM_EXT_FUNC_DRAWTEXTREL       (SM_EXT_FUNC_BEGIN + 2)	            //���λ����ʾ����
#define SM_EXT_FUNC_DRAWRECTABS       (SM_EXT_FUNC_BEGIN + 3)	            //����λ�û�����
#define SM_EXT_FUNC_DRAWRECTREL       (SM_EXT_FUNC_BEGIN + 4)	            //���λ�û�����
#define SM_EXT_FUNC_DRAWFLAGTEXT      (SM_EXT_FUNC_BEGIN + 5)	            //��������
#define SM_EXT_FUNC_FLOATRGN          (SM_EXT_FUNC_BEGIN + 6)	            //�����������
#define SM_EXT_FUNC_FLOATSTICK        (SM_EXT_FUNC_BEGIN + 7)	            //������״��
#define SM_EXT_FUNC_PERCENTBAR        (SM_EXT_FUNC_BEGIN + 8)	            //��������ٷֱ���
#define SM_EXT_FUNC_HORPERCNETBAR     (SM_EXT_FUNC_BEGIN + 9)	            //���ƺ���ٷֱ���
#define SM_EXT_FUNC_DYNAMICICON       (SM_EXT_FUNC_BEGIN + 10)	            //���ƶ�̬ͼ��
#define SM_EXT_FUNC_DRAWCIRCLE        (SM_EXT_FUNC_BEGIN + 11)	            //����Բ

#define SM_EXT_FUNC_FILLRECT          (SM_EXT_FUNC_BEGIN + 12)	            //����
#define SM_EXT_FUNC_RADIALLINE        (SM_EXT_FUNC_BEGIN + 13)	            //����
#define SM_EXT_FUNC_REGRESSION        (SM_EXT_FUNC_BEGIN + 14)	            //�ع���
#define SM_EXT_FUNC_REGRESSIONCHNL    (SM_EXT_FUNC_BEGIN + 15)	            //�ع�ͨ����
#define SM_EXT_FUNC_EQLPERIOD         (SM_EXT_FUNC_BEGIN + 16)	            //��������
#define SM_EXT_FUNC_FIBONACCICYCLE    (SM_EXT_FUNC_BEGIN + 17)	            //쳲�����������
#define SM_EXT_FUNC_LUCASCYCLE        (SM_EXT_FUNC_BEGIN + 18)	            //¬��˹������
#define SM_EXT_FUNC_VERGOLDEN         (SM_EXT_FUNC_BEGIN + 19)	            //��ֱ�ƽ�ָ���
#define SM_EXT_FUNC_PERCENTAGE        (SM_EXT_FUNC_BEGIN + 20)	            //�����ٷֱ���
#define SM_EXT_FUNC_HORGOLDLINE       (SM_EXT_FUNC_BEGIN + 21)	            //ˮƽ�ƽ�ָ���
#define SM_EXT_FUNC_HORPARALLE        (SM_EXT_FUNC_BEGIN + 22)	            //ˮƽƽ����
#define SM_EXT_FUNC_GOLDCIRCLES       (SM_EXT_FUNC_BEGIN + 23)	            //�ƽ�ָ�ͬ��Բ
#define SM_EXT_FUNC_HELIX             (SM_EXT_FUNC_BEGIN + 24)	            //������
#define SM_EXT_FUNC_GANNBOX           (SM_EXT_FUNC_BEGIN + 25)	            //������
#define SM_EXT_FUNC_ELLIPSE           (SM_EXT_FUNC_BEGIN + 26)	            //��Բ
#define SM_EXT_FUNC_GANNLINE          (SM_EXT_FUNC_BEGIN + 27)	            //���¸�����

#define SM_EXT_FUNC_END               SM_EXT_FUNC_BEGIN + 300

//
//�û��Զ���
#define SM_USERS_BEGIN		(SM_FUNC_END + 1)			//�û��Զ��忪ʼ

#define SM_USERS_EXTERN		(SM_USERS_BEGIN + 1)		//�Զ��庯��

#define SM_USERS_END		(SM_USERS_BEGIN + 1000)		//�û��Զ������

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�ı���ϢID����
#define SM_TEXT_BEGIN				(SM_USERS_END + 1)		//�ı���ϢID���忪ʼ(3505)

#define SM_TEXT_STARTUP				(SM_TEXT_BEGIN + 0)		//��ʼҳ��

#define	SM_TEXT_EXCHANGENEWS		(SM_TEXT_BEGIN + 1)		//����������
#define	SM_TEXT_EXCHANGEBULLETIN	(SM_TEXT_BEGIN + 2)		//����������
#define	SM_TEXT_JOBBERINFO			(SM_TEXT_BEGIN + 3)		//ȯ����Ϣ
#define	SM_TEXT_JOBBERBULLETIN		(SM_TEXT_BEGIN + 4)		//ȯ�̹���
#define	SM_TEXT_JOBBERWEB			(SM_TEXT_BEGIN + 5)		//ȯ����վ
#define SM_TEXT_POPMSG				(SM_TEXT_BEGIN + 6)		//��������
#define SM_TEXT_ROLLMSG				(SM_TEXT_BEGIN + 7)		//��������

#define	SM_TEXT_STOCKINFO			(SM_TEXT_BEGIN + 11)	//��������
#define	SM_TEXT_STOCKREVIEW			(SM_TEXT_BEGIN + 12)	//����ÿ������
#define	SM_TEXT_CORPNEWS			(SM_TEXT_BEGIN + 13)	//��˾����
#define	SM_TEXT_CORPBULLETIN		(SM_TEXT_BEGIN + 14)	//��˾����
#define	SM_TEXT_STOCKREAL			(SM_TEXT_BEGIN + 15)	//����ʵʱ����
#define	SM_TEXT_STOCKHQ				(SM_TEXT_BEGIN + 16)	//��������
#define SM_TEXT_COMPANYWEB			(SM_TEXT_BEGIN + 17)	//��˾��վ
#define SM_TEXT_DEFAULTLSZX			(SM_TEXT_BEGIN + 18)	//Ĭ�ϸ�����ʷ��Ѷ
#define SM_TEXT_DEFAULTFSZX			(SM_TEXT_BEGIN + 19)	//Ĭ�ϸ��ɷ�ʱ��Ѷ

#define	SM_TEXT_NEWSCENTER			(SM_TEXT_BEGIN + 21)	//��������
#define	SM_TEXT_TODAYNEWS			(SM_TEXT_BEGIN + 22)	//���յ���
#define	SM_TEXT_ONLINEASK			(SM_TEXT_BEGIN + 23)	//������ѯ
#define	SM_TEXT_STATFORM			(SM_TEXT_BEGIN + 24)	//ͳ�Ʊ���
#define	SM_TEXT_RESEARCHREPORT		(SM_TEXT_BEGIN + 25)	//�о�����
#define	SM_TEXT_TRADEANALYSIS		(SM_TEXT_BEGIN + 26)	//��ҵ����
#define	SM_TEXT_TRADEBULLETIN		(SM_TEXT_BEGIN + 27)	//��ҵ����
#define	SM_TEXT_POLICY				(SM_TEXT_BEGIN + 28)	//���߷���
#define	SM_TEXT_KNOWLEDGE			(SM_TEXT_BEGIN + 29)	//֤ȯ֪ʶ

#define SM_TEXT_RUBBISH				(SM_TEXT_BEGIN + 44)	//������� 3549
#define SM_TEXT_COMMMINE			(SM_TEXT_BEGIN + 45)	//ͨ����ʷ��Ϣ����
#define SM_TEXT_MINMINE				(SM_TEXT_BEGIN + 46)	//ͨ�÷�ʱ��Ϣ����
#define SM_TEXT_POPIE				(SM_TEXT_BEGIN + 47)	//������� 3552
#define SM_TEXT_RUBBISH2			(SM_TEXT_BEGIN + 48)	//������� 3553	--�ϰ汾����ʹ��
#define SM_TEXT_STOCKBLOCK			(SM_TEXT_BEGIN + 49)	//������� 3554
#define SM_TEXT_MINECOUNT			(SM_TEXT_BEGIN + 50)	//��Ϣ������Ŀ

#define SM_TEXT_END					(SM_TEXT_BEGIN + 100)	//�ı���ϢID�������

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

/*�Ѻ�ĳ� inline ����������ٶ�*/
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
//�����ݵĶ���
#define BIG_BUY			0x00001000	//����
#define BIG_SELL		0x00002000	//����
#define BIG_ACTIVE		0x00000100	//����
#define BIG_PASSIVE		0x00000200	//����
#define BIG_LEVEL1		0x00000010	//�ش�
#define BIG_LEVEL12		0x00000011	//�ش�2��
#define BIG_LEVEL2		0x00000020	//��
#define BIG_LEVEL22		0x00000021	//��2��
#define BIG_LEVEL3		0x00000030	//��
#define BIG_LEVEL32		0x00000031	//�У�2��
#define BIG_LEVEL33		0x00000032	//�У�3��
#define BIG_LEVEL4		0x00000040	//С

//���ݴ����ͣ�ȡ�󵥵�������ĿID
int32 GetBigTradeID(int32 lBigType, DWORD& dwCount, DWORD& dwMoney, DWORD& dwTick);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma pack()
#endif //_INC_TYPEDEF_H

