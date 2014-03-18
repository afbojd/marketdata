#ifndef _PERIODDEF_H
#define _PERIODDEF_H

/////////////////////////////////////////////////////////////////////
//ʱ��ĸ�ʽ
#define UT_TIME_SECOND			0			//��ȷ����
#define UT_TIME_MINUTE			1			//��ȷ������
#define UT_TIME_DAY				2			//��ȷ����

//��������
#define PD_BASE(x)		(x & 0xFF00)		//ȡ��������
#define PD_TIMES(x)		(x & 0x00FF)		//ȡ������

#define MIN_5					5			//5����K��

#define SEC_5					5			//5��K��

#define PD_REAL_NUM				3
#define PD_BASE_OFFSET			12

#define UT_NOW					0x0000		//ʵʱ���ݣ���������ʷ
#define UT_HISNOW				0x0001		//��ʷʵʱ����
#define UT_TRACE				0x1000		//�ɽ���ϸ
#define UT_LEVEL2				0x1C00		//��¼��ʳɽ��������̡����������ݣ����������ݳ�
#define UT_MINUTE				0x2000		//��������
											//�Ͱ�λ��ʾ����
											//0 ��ʾһ����
#define UT_HISMINUTE			0x2001		//��ʷ��������

#define UT_KLINE_BEG			0x3000		//K�����ڵĿ�ʼ
#define UT_MIN					0x3000		//1 5 15 30 60 120����K��
											//�Ͱ�λ��ʾ����
											//0 ��ʾһ����

#define UT_SECOND				0x3100		//��K��
#define UT_DAY					0x4000		//����
											//�Ͱ�λ��ʾ��
											//0 ��ʾһ��
#define UT_WEEK					0x5000		//����
#define UT_MONTH				0x6000		//����
#define UT_YEAR					0x7000		//����
#define UT_KLINE_END			0x7FFF		//K�����ڵĽ���

#define UT_FINANCECALC			0x9000		//�������

#define UT_CACHEPERIOD			0xA000		//��������
#define UT_OTHERPERIOD			0xB000		//����������������
#define UT_FINPERIOD			0xC000		//�ƾ�������������

#define UT_TEXTPERIOD			0xD000		//�ı�����
#define UT_SERVERPUSH			0xDC00		//��վ�������͵����ݣ����������ݳ�

#define UT_EXTRA_PERIOD			0xE000		//�������ڣ����������ɽ���ϸ�ͷ��������õ���ǰ����

#define UT_MARKET_PERIOD		0xF100		//ȡ�г���Ϣ�ļ�����ʵ�������ڡ�
#define UT_STAT_PERIOD			0xF200		//ͳ�Ƽ���

#define UT_NONE_PERIOD			0xFFFF		//������
#define UT_ALL_PERIOD			0xFFFE		//ȫ�����ڣ����ڱ�ʾ�������ڵĳ���

///////////////////////////////////////////////////////////////////////////////////////
#define PD_DAYUNIT(x)			(x < UT_KLINE_BEG  && x >= UT_TRACE)		//�ж��Ƿ�����Ϊ��λ
#define PD_KLINE(x)				(x >= UT_KLINE_BEG && x <= UT_KLINE_END)	//�ж��Ƿ���K������

///////////////////////////////////////////////////////////////////////////////////////
//UT_SERVERPUSH �ĵ�λ��ʾ��������
#define PUSH_REALORDER			0x0001		//���͵Ķ��߾�������
#define PUSH_RO_REQUEST			0x0002		//��������͵Ķ��߾�������
#define PUSH_RO_STAT			0x0003		//����ͳ�ƵĶ��߾�������

///////////////////////////////////////////////////////////////////////////////////
//UT_LEVEL2 �ĵ�λ��ʾ�����ļ�������
#define LEV2_TICK				0x0001		//��ʳɽ���ϸ
#define LEV2_BUYWAWAL			0x0002		//���ɽ��롮ί�򳷵��������ĳ�����Ϣ
#define LEV2_SELLWAWAL			0x0003		//���ɽ��롮ί�������������ĳ�����Ϣ
#define LEV2_BUYORDER			0x0005		//������������λ
#define LEV2_SELLORDER			0x0006		//�������������λ
#define LEV2_ORDER				0x0007		//���ί��
#define	LEV2_TRACE				0x0008		//�ɽ���ϸ
#define	LEV2_LEVELS				0x0009		//N������

#define LEV2_STAT_VOL			0x0010		//�ɽ�����λͳ�ƣ��ּ۱�
#define LEV2_STAT_CLASS			0x0011		//�ɽ���ͳ��
#define LEV2_SERIES				0x0012		//��������
#define LEV2_STAT_CLOUD			0x0013		//�ɽ���ͳ�ƣ��ɽ���
#define LEV2_STAT_SERIES		0x0014		//ͳ����������
#define LEV2_STAT_MONEY			0x0015		//�ɽ���λͳ��

#define LEV2_BIGTRADE			0x0020		//����ϸ

#define LEV2_MSG				0x0080		//һЩ��������Ϣ�ļ�������Ҫ����ת�봦��

#define LEV2_BUYRWARANK			0x0082		//���ɼ�ʱί�򳷵�����
#define LEV2_SELLRWARANK		0x0083		//���ɼ�ʱί����������

#define LEV2_BUYTWARANK			0x0084 		//�����ۼ�ί�򳷵�����
#define LEV2_SELLTWARANK		0x0089 		//�����ۼ�ί����������

#define LEV2_INDUSTRYRANK		0x0087		//��ҵ����
#define LEV2_SECURITYRANK		0x0088		//��ҵ�ڸ�������

#define LEV2_IND_CHG_RANK		0x008A		//��ҵ��������
#define LEV2_SEC_CHG_RANK		0x008B		//��ҵ�ڸ��ɻ�������

#define LEV2_IND_RISE_RANK		0x008C		//��ҵ��������
#define LEV2_SEC_RISE_RANK		0x008D		//��ҵ�ڸ�����������

#define LEV2_ALLSERIES			0x0092		//���д������������

///////////////////////////////////////////////////////////////////////////////////
//���������ж�
#define	STD_SELL		0x4		//���̳ɽ�������������
#define	STD_BUY			0x0		//���̳ɽ���������������

#define	STD_TICK		0x80	//������ʳɽ��ж�

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

#define STD_NOVOL		0xF							//û�гɽ�

#define IS_NORMALVOL(x)   (x >= 0 && x != (int32)STD_NOVOL)			//�����ĳɽ�������

/////////////////////////////////////////////////////////////////////////////////////
//����ת���ķ���ֵ
#define MT_CPT_ERROR				-1				//���󣬲���ת������
#define MT_CPT_UPDATETIME			1				//��Ҫ�ϲ���ʱ��

//ʱ��ת������ֵ
#define		MT_CAT_UPDATE			0			//����
#define		MT_CAT_ADD				1			//����
#define		MT_CAT_OVERLAY			2			//����

#define		MT_CAT_ERROR			-1			//����

#endif //_PERIODDEF_H



