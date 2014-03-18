--************************浙江同花顺网络信息股份有限公司****************************
--				                资管系统 V2.0.0
-- 应用服务器模板

require('hexin.func');
require('hexin.log');
require('app.util');
require('hexin.threadex');

local hexin = hexin;
local arg   = hexin.thread.get_thread_arg();

local handle = require(arg.handle_script) or {};

--处理连接的函数
local HandleLink = handle.HandleLink;

--处理数据的函数
local HandleData = handle.HandleData;

--处理断线消息的函数
local HandleDisConnect = handle.HandleDisConnect;


--处理数据函数
--tcp是监听对象
--d 是接收到的数据以及其他相关信息的打包，HexinPacket包格式
local function HandleRequest(tcp, d)
	local sessionid = d:getdata(':sid:');

	if d:getdata(':pid:') == '1' then	--处理握手包
		if not string.find(d:getdata(':data:'), 'youareadog') then
			tcp:disconnect(d:getdata(':sid:'));
			return;
		end
		local sid = tcp:get_session_info(d:getdata(':sid:'));
		local info = '客户连接成功,来源:'  .. ( sid['ip'] or '');
		print(info);
		hexin.log.write(info);

		--通知连接成功
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

--**返回给调用模块的处理函数，必须的**
return {
	HandleServerData = HandleRequest;
};

