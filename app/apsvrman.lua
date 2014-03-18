--************************�㽭ͬ��˳������Ϣ�ɷ����޹�˾****************************
--				                �ʹ�ϵͳ V2.0.0
-- Ӧ�÷�����ģ��

require('hexin.func');
require('hexin.log');
require('app.util');
require('hexin.threadex');

local hexin = hexin;
local arg   = hexin.thread.get_thread_arg();

local handle = require(arg.handle_script) or {};

--�������ӵĺ���
local HandleLink = handle.HandleLink;

--�������ݵĺ���
local HandleData = handle.HandleData;

--���������Ϣ�ĺ���
local HandleDisConnect = handle.HandleDisConnect;


--�������ݺ���
--tcp�Ǽ�������
--d �ǽ��յ��������Լ����������Ϣ�Ĵ����HexinPacket����ʽ
local function HandleRequest(tcp, d)
	local sessionid = d:getdata(':sid:');

	if d:getdata(':pid:') == '1' then	--�������ְ�
		if not string.find(d:getdata(':data:'), 'youareadog') then
			tcp:disconnect(d:getdata(':sid:'));
			return;
		end
		local sid = tcp:get_session_info(d:getdata(':sid:'));
		local info = '�ͻ����ӳɹ�,��Դ:'  .. ( sid['ip'] or '');
		print(info);
		hexin.log.write(info);

		--֪ͨ���ӳɹ�
		tcp:send(d:getdata(':sid:'), '\0\0\0');

		if HandleLink then
			HandleLink(tcp, sessionid, sid['ip']);
		end
		return;	
	end

	if HandleDisConnect and d:getdata(':linkstatus:') == '0'then
		HandleDisConnect(tcp, sessionid);
		return;
	end
	
	local req = HexinPacket();
	if not req:unpacket(d:getdata(':data:')) then
		return;
	end

	req = WrapperHexinPacket(req);

	if HandleData then
		HandleData(tcp, sessionid, req);
	end
end

--**���ظ�����ģ��Ĵ������������**
return {
	HandleServerData = HandleRequest;
};

