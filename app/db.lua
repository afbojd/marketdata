--************************浙江同花顺网络信息股份有限公司****************************
--				                资管系统 V2.0.0
-- 数据库连接管理
--
-- 创建时间: 2013/6/8
-- 作者:     王建 wangjian@myhexin.com
--
-- ExecSql执行sql语句

module('app.db', package.seeall)

require('hexin.db');

--------------------------------内部函数---------------------------------------
--数据库连接设置
local dbset = 
{
	dbtype = 'oracle',				--数据库类型，mssql-SQL Server， mysql-MYSQL oracle-ORACLE
	db_addr= '172.20.0.244',		--数据库地址
	db_dbname = 'myoracle',	--数据库名
	db_username= 'hxasset',				--用户名
	db_pwd = 'hxasset'				--密码
};

local db = nil;
local function GetDB()
	if db then 
		return db;
	end
	db, msg = hexin.db.ConnectDB(dbset);
	if db == nil then
		print('连接数据库失败:', msg);
		return  db, msg;
	end
	return db;
end
-------------------------------------------------------------------------------


--执行SQL语句
--sql 需要执行的sql语句
--返回值，
--成功的情况下，如果有表返回，那么返回表数据，多个表返回多个数据
--没有表返回，那么返回true/nil， 如果是nil，那么第二个返回值返回错误信息
function ExecSql(sql)
	local db, msg = GetDB();
	if db == nil then return nil, msg end;

	local tlist = {};
	local t = nil;
	local last = '';
	local r, msg, rows = db:ExecSql_CB_BY_ROW(sql, nil, function(tabname, idx, row)
		if last ~= tabname then
			last = tabname;
			t = {};
			table.insert(tlist, t);
		end
		table.insert(t, row);
	end);
	if not r then
		return nil, msg;		
	end
	
	if #tlist == 0 then
		return true, rows;
	end

	--返回多个表
	return unpack(tlist);
end
