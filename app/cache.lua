--************************浙江同花顺网络信息股份有限公司****************************
--				                资管系统 V2.0.0
-- cache管理模块，提供整个程序共享内存
--
-- 创建时间: 2013/6/8
-- 作者:     王建 wangjian@myhexin.com
--
-- 数据需要区分种类，种类可以多一些，这样在操作的时候，就可以尽量减少对全局对象的加锁
-- 加快存取速度

-- 模块提供存取数据函数SetData和GetData

-- 1.2013/6/8 现在只是临时版本，提供存储功能，不保证速度，只保证数据的正确性
module('app.cache', package.seeall)

require('hexin.json')
local json = json;

-------------内部数据和内部函数
local  _data_map = {};	--分类数据对应关系(做缓存，加快读取数据)

--根据数据种类获得保存数据的对象--
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

--获得分类存储数据
function GetCategorySet(category)
	local d = GetDataByCategory(category);
	return function(name, data)
		return d:setdata(name, PacketData(data));
	end
end

--获得分类取数据
function GetCategoryGet(category)
	local d = GetDataByCategory(category);
	return function(name)
		return UnPacketData(d:getdata(name));
	end
end
--保存数据
--category  数据分类
--name      数据名称
--data      数据
--成功返回true，失败返回false
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
--判断是否是索引值
local function JudgeIndex(d)
	if d == nil  then return nil end;

	if #d < IDXLEN then return d end;
	if string.sub(d, 1, IDXLEN) ~= IDXBG then
		return d;
	end
	return nil, string.sub(d, IDXLEN+1);
end

--取数据
--category  数据分类
--name      数据名称
--返回值   成功返回相关的数据，失败返回nil,成功同时返回原始的key值(使用索引key时，需要更新数据有用)
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

--清除某个分类下所有的数据
function EmptyCategory(category)
	local d = GetDataByCategory(category);
	if d then
		d:Empty();
	end
end

--在分类下简历索引
--idxname 索引名称 
--srcname 原始数据名称
function CreateIndex(category, idxname, srcname)
	local d = GetDataByCategory(category);
	if d == nil then return nil end;

	d:setdata(idxname, string.format('%s%s', IDXBG,srcname));
end

--删除指定的cache内容
--category 分类
--name     名称
function DeleteData(category, name)
	local d = GetDataByCategory(category);
	if d  == nil then return false; end

	d:setdata(name, '');
	return true;
end

--更新数据
--category 分类
--name     名称
--f  处理函数，返回true更新，否则不处理
--如果数据部存在会默认生成一个table以供数据处理
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

--处理数据
function HandleData(category, name, f)
	local d, oriname = GetData(category, name);
	if d == nil then return nil; end

	f(d);
end