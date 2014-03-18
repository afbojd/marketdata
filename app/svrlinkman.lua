--************************浙江同花顺网络信息股份有限公司****************************
--				                资管系统 V2.0.0
-- 服务器连接管理器

module('app.svrlikman', package.seeall);

require('app.link');
require('app.util');
require('hexin.threadex');

local hexin = hexin;
local app   = app;
local arg = hexin.thread.get_thread_arg();

local linkset = arg.linkset;
if linkset == nil then
	hexin.thread.write_log(hexin.thread.RUN_LOG, '没有配置必要的服务器连接');
	return;
end

-------------------------------------------------------------------------------
local data_q = hexin.queue.create('_asset_server_cross_link_');

local linkinfo = {};
--创建服务器连接
for k, v in pairs(linkset) do
	local asynhandle = nil;
	if v.handle then
		asynhandle = require(v.handle);
	end

	linkinfo[k] = {
			obj		= app.link.CreateLink(k, v.addr, data_q);
			handle  = asynhandle or {};
	};
	print(string.format('服务器连接: %s  %s', k, tostring(linkinfo[k].obj)));
end

--处理连接消息
--obj 连接对象 
--isconnected  true/false是否连接成功的通知
--ipinfo  当前连接的地址信息ip:port格式
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
		print('连接状态:', ipinfo, isconnected);
	end

	if chg and info.handle.HandleStatus then			
		info.handle.HandleStatus(obj, isconnected, ipinfo);
	end
end


--数据处理函数
--obj  连接对象
--data 收到的原始数据
local function HandleData(info, obj, data)
--	print('data xxxx-->', obj, data);	
	local reply = data_q:create_data();
	if not reply:unpacket(data) then
		print('解应答数据包失败');
		return;
	end

	local reqid = reply:getdata('__req_id__');
	if reqid then	--同步请求处理
		obj:SetReplyData(reqid, reply);

	elseif info.handle.HandleData then	--异步处理过程
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