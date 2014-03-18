--************************浙江同花顺网络信息股份有限公司****************************
--				                资管系统 V2.0.0
-- 服务器连接模块
module('app.link', package.seeall);

require('hexin.base');
require('hexin.translink');	--连接对象
require('app.util');
local cache = require('app.cache');
local hexin = hexin;
local reply_map = hexin.hpmap;

--连接对象
local LINK = CreateExtendClass();

--初始化
function LINK:Init()
	self.event = hexin.event.create(self.obj:getprop('event_name'));
end

--信号通知
function LINK:SetEvent()
	self.event:set_event();
end

--设置应答数据
function LINK:SetReplyData(id, data)
	reply_map.set(id, data);
	self:SetEvent();
end

--等待信号
--timeout 超时时间，单位毫秒
function LINK:Wait(timeout)
	local r = self.event:wait(timeout);
	self.event:reset_event();
	return r;
end

local p = HexinPacket();

--发送请求数据
--req请求格式是table数据
function LINK:Send(req)
	p:empty();
	p:set_table(req);
	return self.obj:send(p:packet());	
end

--发送请求并接收应答
--req 请求数据，table数据
--timeout 等待超时时间（单位毫秒)
--返回值，成功返回收到的数据，解包好的数据格式，直接用字段名就能取值
--失败，返回nil,错误代码，错误信息
function LINK:SendAndReceive(req, timeout)
	timeout = timeout or 3000;
	local reqid = hexin.util.create_guid();
	--print('reqid-->', reqid);
	req['__req_id__'] = reqid;
	if not self:Send(req) then
		return nil, -1, '连接未建立或已断开';
	end

	local reply = nil;
	while(true) do
		if self:Wait(timeout) then
			reply = reply_map.free(reqid);
			if reply then 				
				break; 
			end;
			print('收到数据->', reqid, hexin.thread.get_cur_threadid());
			self:SetEvent();
			hexin.util.sleep(500);
		else
			return nil, -2, '请求超时';
		end
	end
	return WrapperHexinPacket(reply);
end

--判断当前连接是否成功
function LINK:IsConnected()
	return self:getprop('iscon') == '1';
end

--创建连接对象
--id 连接ID，相同ID只会创建一个连接
--addr 服务器地址 ,格式  ip:port|ip2:port2...,支持自动重连等功能
--成功，返回连接对象，否则返回nil
local links = {};
function CreateLink(id, addr, q)
	if id == nil then return nil, 'ID不能为空'; end

	if links[id] then
		return links[id];
	end

	local obj , exsist = hexin.hx.wtlinker.create(id);

	if obj == nil then
		return nil, '生成连接对象失败';
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

--根据用户ID获得连接对象
function GetLink(id)
	if id == nil then return nil, 'ID不能为空' end
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
	return nil, tostring(id) .. '连接对象未初始化，请稍后重试';
end

