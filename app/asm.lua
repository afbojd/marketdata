--************************浙江同花顺网络信息股份有限公司****************************
--				                资管系统 V2.0.0
-- 资管业务模块管理文件，提供管理多个业务插件的能力，并对请求提供统一入口
--
-- 创建时间: 2013/6/8
-- 作者:     王建 wangjian@myhexin.com
--
--
module('app.asm', package.seeall);
require('hexin.func');
require('hexin.log');
require('hexin.setting');

local hexin = hexin;	--缓存系统功能
local setting = hexin.setting;

local asm_setting_name = '___asset_manager__';

local inited = (setting.get_singleval(asm_setting_name) == '1');
setting.set_singleval(asm_setting_name, '1');

local mlist = {};		--本地加载的业务功能模块列表
local cmdmap= {};		--请求类型映射
local cmdm  = {};		--请求模块对应关系

--读取配置的功能模块列表
local function LoadModuleList()
	local txt = hexin.func.read_file('asmplugin');
	if txt == nil then 
		hexin.log.write('打开asmplugin文件失败，不能加载业务处理模块，请检查');
		return 
	end;

	local t = {};
	for s in string.gmatch(txt, '([^\r\n]+)') do
		local flag, m = string.match(s, '([^=]+)%s*=%s*(.+)');
		if flag == 'plugin' then
			table.insert(t, m);
		end
	end

	if #t <= 0 then
		hexin.log.write('asmplugin配置文件中，没有配置响应的业务处理模块，请检查');
		return nil;
	end
	return t;
end

--加载模块，并做缓存
local function LoadModule()
	local t = LoadModuleList();
	if t == nil then return end;

	--加载模块
	local m = {};
	for k, v in ipairs(t) do
		local r, d = pcall(require, v);
		if r then
			table.insert(m, {
				name = v;
				m    = d;
			});
		else
			hexin.log.write(string.format('加载%s模块失败，%s', v, d));
		end
	end
	
	--读取初始化信息
	for k, v in ipairs(m) do
		local f = v.m.GetHandleReqList;
		if f then
			v.req = f();
		end
	end

	--调用初始化函数
	if not inited then
		for k, v in ipairs(m) do
			local f = v.m.Init;
			if f then
				pcall(f);
			end
		end
	end
	
	local cmd = {};
	--缓存请求类型
	for k, v in ipairs(m) do
		local req = v.req;
		if type(req) ~= 'table' then
			hexin.log.write(string.format('模块[%s]返回的请求类型有误，需要一个命令列表', v.name));
		else
			for k, v2 in ipairs(req) do
				cmd[v2] = cmd[v2] or v.m.HandleRequest;
				cmdm[v2] = cmdm[v2] or v.name;
			end
		end
	end
	cmdmap = cmd;
end

--处理业务请求
function HandleRequest(cmd, req, reply)
	local f = cmdmap[cmd];
	if f == nil then
		return false, string.format('请求[%s]没有对应的请求处理模块', cmd or '');
	end

	local pr, r, msg = pcall(f, cmd, req, reply);
	if not pr then
		hexin.log.write('脚本执行错误:' .. tostring(r));
		return false, string.format('请求[%s] 模块[%s] 后台脚本执行错误', cmd or '', cmdm[cmd] or '');
	end

	return r, msg;
end

--初始化数据
LoadModule();

