--************************�㽭ͬ��˳������Ϣ�ɷ����޹�˾****************************
--				                �ʹ�ϵͳ V2.0.0
-- ����������ģ��
module('app.link', package.seeall);

require('hexin.base');
require('hexin.translink');	--���Ӷ���
require('app.util');
local cache = require('app.cache');
local hexin = hexin;
local reply_map = hexin.hpmap;

--���Ӷ���
local LINK = CreateExtendClass();

--��ʼ��
function LINK:Init()
	self.event = hexin.event.create(self.obj:getprop('event_name'));
end

--�ź�֪ͨ
function LINK:SetEvent()
	self.event:set_event();
end

--����Ӧ������
function LINK:SetReplyData(id, data)
	reply_map.set(id, data);
	self:SetEvent();
end

--�ȴ��ź�
--timeout ��ʱʱ�䣬��λ����
function LINK:Wait(timeout)
	local r = self.event:wait(timeout);
	self.event:reset_event();
	return r;
end

local p = HexinPacket();

--������������
--req�����ʽ��table����
function LINK:Send(req)
	p:empty();
	p:set_table(req);
	return self.obj:send(p:packet());	
end

--�������󲢽���Ӧ��
--req �������ݣ�table����
--timeout �ȴ���ʱʱ�䣨��λ����)
--����ֵ���ɹ������յ������ݣ�����õ����ݸ�ʽ��ֱ�����ֶ�������ȡֵ
--ʧ�ܣ�����nil,������룬������Ϣ
function LINK:SendAndReceive(req, timeout)
	timeout = timeout or 3000;
	local reqid = hexin.util.create_guid();
	--print('reqid-->', reqid);
	req['__req_id__'] = reqid;
	if not self:Send(req) then
		return nil, -1, '����δ�������ѶϿ�';
	end

	local reply = nil;
	while(true) do
		if self:Wait(timeout) then
			reply = reply_map.free(reqid);
			if reply then 				
				break; 
			end;
			print('�յ�����->', reqid, hexin.thread.get_cur_threadid());
			self:SetEvent();
			hexin.util.sleep(500);
		else
			return nil, -2, '����ʱ';
		end
	end
	return WrapperHexinPacket(reply);
end

--�жϵ�ǰ�����Ƿ�ɹ�
function LINK:IsConnected()
	return self:getprop('iscon') == '1';
end

--�������Ӷ���
--id ����ID����ͬIDֻ�ᴴ��һ������
--addr ��������ַ ,��ʽ  ip:port|ip2:port2...,֧���Զ������ȹ���
--�ɹ����������Ӷ��󣬷��򷵻�nil
local links = {};
function CreateLink(id, addr, q)
	if id == nil then return nil, 'ID����Ϊ��'; end

	if links[id] then
		return links[id];
	end

	local obj , exsist = hexin.hx.wtlinker.create(id);

	if obj == nil then
		return nil, '�������Ӷ���ʧ��';
	end

	if not exsist then
		if q then
			obj:set_receive_queue(q);
		end

		obj:set_addrinfo(addr);
		obj:start_connect(1);

		obj:setprop('event_name', hexin.util.create_guid());
	end
	local r = LINK:new(obj);
	r:Init();
	links[id] = r;
	cache.SetData("_connect_cache", "_is_conn_" .. id, '1');
	return r, exsist;
end

--�����û�ID������Ӷ���
function GetLink(id)
	if id == nil then return nil, 'ID����Ϊ��' end
	if links[id] then return links[id] end;
	local res = cache.GetData("_connect_cache", "_is_conn_" .. id );
	if res == '1' then
		local obj = hexin.hx.wtlinker.create(id);
		if obj then
			local r = LINK:new(obj);
			r:Init();
			links[id] = r;
			return r;
		end
	end
	return nil, tostring(id) .. '���Ӷ���δ��ʼ�������Ժ�����';
end

