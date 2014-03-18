--************************�㽭ͬ��˳������Ϣ�ɷ����޹�˾****************************
--				                �ʹ�ϵͳ V2.0.0
-- cache����ģ�飬�ṩ�����������ڴ�
--
-- ����ʱ��: 2013/6/8
-- ����:     ���� wangjian@myhexin.com
--
-- ������Ҫ�������࣬������Զ�һЩ�������ڲ�����ʱ�򣬾Ϳ��Ծ������ٶ�ȫ�ֶ���ļ���
-- �ӿ��ȡ�ٶ�

-- ģ���ṩ��ȡ���ݺ���SetData��GetData

-- 1.2013/6/8 ����ֻ����ʱ�汾���ṩ�洢���ܣ�����֤�ٶȣ�ֻ��֤���ݵ���ȷ��
module('app.cache', package.seeall)

require('hexin.json')
local json = json;

-------------�ڲ����ݺ��ڲ�����
local  _data_map = {};	--�������ݶ�Ӧ��ϵ(�����棬�ӿ��ȡ����)

--�������������ñ������ݵĶ���--
local function GetDataByCategory(category)
	local d = _data_map[category];
	if d then
		return d;
	end

	d = hexin.hpmap.create('[app_cache]' .. category);
	_data_map[category] = d;
	return d;
end


local function PacketData(data)
	local d = json.encode(
	{
		d = data;		
	});	
	return d;
end

local function UnPacketData(data)
	if data == nil then return nil; end

	local d = json.decode(data);
	if d then return d.d; end
	return nil;
end

--��÷���洢����
function GetCategorySet(category)
	local d = GetDataByCategory(category);
	return function(name, data)
		return d:setdata(name, PacketData(data));
	end
end

--��÷���ȡ����
function GetCategoryGet(category)
	local d = GetDataByCategory(category);
	return function(name)
		return UnPacketData(d:getdata(name));
	end
end
--��������
--category  ���ݷ���
--name      ��������
--data      ����
--�ɹ�����true��ʧ�ܷ���false
function SetData(category, name, data)
	local d = GetDataByCategory(category);
	if d == nil then return false;end

	d:setdata(name, PacketData(data));
	return true;
end

function SetDataOri(category, name, data)
	local d = GetDataByCategory(category);
	if d == nil then return false;end

	d:setdata(name, data);
	return true;
end


local IDXBG = '$\001\002';
local IDXLEN = #IDXBG;
--�ж��Ƿ�������ֵ
local function JudgeIndex(d)
	if d == nil  then return nil end;

	if #d < IDXLEN then return d end;
	if string.sub(d, 1, IDXLEN) ~= IDXBG then
		return d;
	end
	return nil, string.sub(d, IDXLEN+1);
end

--ȡ����
--category  ���ݷ���
--name      ��������
--����ֵ   �ɹ�������ص����ݣ�ʧ�ܷ���nil,�ɹ�ͬʱ����ԭʼ��keyֵ(ʹ������keyʱ����Ҫ������������)
function GetData(category, name)
	local d = GetDataByCategory(category);
	if d == nil then return nil end

	local txt = nil;
	local src = nil;
	while(true) do
		txt, src = JudgeIndex(d:getdata(name));
		if txt == nil and src == nil then
			return nil;
		elseif txt == nil then
			name = src;
		else
			break;
		end
	end

	return UnPacketData(txt), src or name;
end


function GetDataOri(category, name)
	local d = GetDataByCategory(category);
	if d == nil then return nil end

	local txt = nil;
	local src = nil;
	while(true) do
		txt, src = JudgeIndex(d:getdata(name));
		if txt == nil and src == nil then
            return nil;
		elseif txt == nil then
			name = src;
		else
			break;
		end
	end

	return txt, src or name;
end

--���ĳ�����������е�����
function EmptyCategory(category)
	local d = GetDataByCategory(category);
	if d then
		d:Empty();
	end
end

--�ڷ����¼�������
--idxname �������� 
--srcname ԭʼ��������
function CreateIndex(category, idxname, srcname)
	local d = GetDataByCategory(category);
	if d == nil then return nil end;

	d:setdata(idxname, string.format('%s%s', IDXBG,srcname));
end

--ɾ��ָ����cache����
--category ����
--name     ����
function DeleteData(category, name)
	local d = GetDataByCategory(category);
	if d  == nil then return false; end

	d:setdata(name, '');
	return true;
end

--��������
--category ����
--name     ����
--f  ������������true���£����򲻴���
--������ݲ����ڻ�Ĭ������һ��table�Թ����ݴ���
function UpdateData(category, name, f)
	local d, oriname = GetData(category, name);
	d = d or {};
	oriname = oriname or name;

	if f(d) then
		SetData(category, oriname, d);
		return true;
	end
	return false;
end

--��������
function HandleData(category, name, f)
	local d, oriname = GetData(category, name);
	if d == nil then return nil; end

	f(d);
end