--************************�㽭ͬ��˳������Ϣ�ɷ����޹�˾****************************
--				                �ʹ�ϵͳ V2.0.0
-- �ʹ�ҵ��ģ������ļ����ṩ������ҵ���������������������ṩͳһ���
--
-- ����ʱ��: 2013/6/8
-- ����:     ���� wangjian@myhexin.com
--
--
module('app.asm', package.seeall);
require('hexin.func');
require('hexin.log');
require('hexin.setting');

local hexin = hexin;	--����ϵͳ����
local setting = hexin.setting;

local asm_setting_name = '___asset_manager__';

local inited = (setting.get_singleval(asm_setting_name) == '1');
setting.set_singleval(asm_setting_name, '1');

local mlist = {};		--���ؼ��ص�ҵ����ģ���б�
local cmdmap= {};		--��������ӳ��
local cmdm  = {};		--����ģ���Ӧ��ϵ

--��ȡ���õĹ���ģ���б�
local function LoadModuleList()
	local txt = hexin.func.read_file('asmplugin');
	if txt == nil then 
		hexin.log.write('��asmplugin�ļ�ʧ�ܣ����ܼ���ҵ����ģ�飬����');
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
		hexin.log.write('asmplugin�����ļ��У�û��������Ӧ��ҵ����ģ�飬����');
		return nil;
	end
	return t;
end

--����ģ�飬��������
local function LoadModule()
	local t = LoadModuleList();
	if t == nil then return end;

	--����ģ��
	local m = {};
	for k, v in ipairs(t) do
		local r, d = pcall(require, v);
		if r then
			table.insert(m, {
				name = v;
				m    = d;
			});
		else
			hexin.log.write(string.format('����%sģ��ʧ�ܣ�%s', v, d));
		end
	end
	
	--��ȡ��ʼ����Ϣ
	for k, v in ipairs(m) do
		local f = v.m.GetHandleReqList;
		if f then
			v.req = f();
		end
	end

	--���ó�ʼ������
	if not inited then
		for k, v in ipairs(m) do
			local f = v.m.Init;
			if f then
				pcall(f);
			end
		end
	end
	
	local cmd = {};
	--������������
	for k, v in ipairs(m) do
		local req = v.req;
		if type(req) ~= 'table' then
			hexin.log.write(string.format('ģ��[%s]���ص���������������Ҫһ�������б�', v.name));
		else
			for k, v2 in ipairs(req) do
				cmd[v2] = cmd[v2] or v.m.HandleRequest;
				cmdm[v2] = cmdm[v2] or v.name;
			end
		end
	end
	cmdmap = cmd;
end

--����ҵ������
function HandleRequest(cmd, req, reply)
	local f = cmdmap[cmd];
	if f == nil then
		return false, string.format('����[%s]û�ж�Ӧ��������ģ��', cmd or '');
	end

	local pr, r, msg = pcall(f, cmd, req, reply);
	if not pr then
		hexin.log.write('�ű�ִ�д���:' .. tostring(r));
		return false, string.format('����[%s] ģ��[%s] ��̨�ű�ִ�д���', cmd or '', cmdm[cmd] or '');
	end

	return r, msg;
end

--��ʼ������
LoadModule();

