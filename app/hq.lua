--************************�㽭ͬ��˳������Ϣ�ɷ����޹�˾****************************
--				                �ʹ�ϵͳ V2.0.0
-- �ʹ�������ճ���
--
-- ����ʱ��: 2013/7/8
-- ����:     ���� wangjian@myhexin.com
-- ��������ģ��ʹ�� app.hq.GetHQ(code)���ɻ�ȡ������Ϣ

module('app.hq', package.seeall);
require('hx');
require('hexin.base');

--���ӵ����鷢�͵�ַ����ַ�Ͷ˿��Ǻ�ί����վ�����鷢��ȡ���ݵĽӿ���ͬ
--��,��ַ��ʽ��ip:port
local send_addr = '10.0.2.180:8610';


--------------------�����ǹ��������֣�������������޸�-----------------------
local hq, bexsist = hexin.hx.receiver.create('zghq');
--�����ɵĶ���������Ӳ���
if not bexsist then
	hq:init_send_addr(send_addr);
end


--------------------------��������---------------------------------------------

--ȡָ�������������Ϣ
--code �������
--return ���������ڣ����������Ϣtable,���򷵻�nil
--���ݵ�ֵ���� zqmc-֤ȯ���� zqdm-�������֤ȯ���� time-����ʱ�� zrsp-����
--jrkp-���տ��� zxj-���¼� mrsl1-mrsl5 ��������1-5 mrjw1-mrjw5 �����λ1-5
--mcsl1-5 ��������1-5 mcjw1-5 ������λ1-5 ztjg-��ͣ�۸� dtjg-��ͣ�۸�
function GetHQ(code)
	return hq:get_hqdata(code);
end

function GetAllCode()
    local list = hq:get_all_code();
    return list;
end
