--************************�㽭ͬ��˳������Ϣ�ɷ����޹�˾****************************
--				                �ʹ�ϵͳ V2.0.0
-- ���������ӹ�����

module('app.svrlikman', package.seeall);

require('app.link');
require('app.util');
require('hexin.threadex');

local hexin = hexin;
local app   = app;
local arg = hexin.thread.get_thread_arg();

local linkset = arg.linkset;
if linkset == nil then
	hexin.thread.write_log(hexin.thread.RUN_LOG, 'û�����ñ�Ҫ�ķ���������');
	return;
end

-------------------------------------------------------------------------------
local data_q = hexin.queue.create('_asset_server_cross_link_');

local linkinfo = {};
--��������������
for k, v in pairs(linkset) do
	local asynhandle = nil;
	if v.handle then
		asynhandle = require(v.handle);
	end

	linkinfo[k] = {
			obj		= app.link.CreateLink(k, v.addr, data_q);
			handle  = asynhandle or {};
	};
	print(string.format('����������: %s  %s', k, tostring(linkinfo[k].obj)));
end

--����������Ϣ
--obj ���Ӷ��� 
--isconnected  true/false�Ƿ����ӳɹ���֪ͨ
--ipinfo  ��ǰ���ӵĵ�ַ��Ϣip:port��ʽ
local function HandleStatus(info, obj, isconnected, ipinfo)
	local chg = false;
	if isconnected and obj:getprop('iscon') ~= '1' then
		obj:setprop('iscon', '1');
		chg = true;
	elseif (not isconnected) and obj:getprop('iscon') == '1' then
		obj:setprop('iscon', '0');
		chg = true;
	end
	if chg then
		print('����״̬:', ipinfo, isconnected);
	end

	if chg and info.handle.HandleStatus then			
		info.handle.HandleStatus(obj, isconnected, ipinfo);
	end
end


--���ݴ�����
--obj  ���Ӷ���
--data �յ���ԭʼ����
local function HandleData(info, obj, data)
--	print('data xxxx-->', obj, data);	
	local reply = data_q:create_data();
	if not reply:unpacket(data) then
		print('��Ӧ�����ݰ�ʧ��');
		return;
	end

	local reqid = reply:getdata('__req_id__');
	if reqid then	--ͬ��������
		obj:SetReplyData(reqid, reply);

	elseif info.handle.HandleData then	--�첽�������
		info.handle.HandleData(obj, WrapperHexinPacket(reply));
	end
end


hexin.thread.run_queue_handle(data_q, function(d)
	local name = d:getdata(':objname:');
	local info  = linkinfo[name];
	if info then
		local obj   = info.obj;
		local ctype = d:getdata(':ctype:');		

		if ctype == '0' then
			HandleData(info, obj, d:getdata(':data:'));
		else
			HandleStatus(info, obj, ctype == '1', d:getdata(':data:'));
		end
	end
end);