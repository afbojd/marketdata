--************************�㽭ͬ��˳������Ϣ�ɷ����޹�˾****************************
--				                �ʹ�ϵͳ V2.0.0
-- ���ݿ����ӹ���
--
-- ����ʱ��: 2013/6/8
-- ����:     ���� wangjian@myhexin.com
--
-- ExecSqlִ��sql���

module('app.db', package.seeall)

require('hexin.db');

--------------------------------�ڲ�����---------------------------------------
--���ݿ���������
local dbset = 
{
	dbtype = 'oracle',				--���ݿ����ͣ�mssql-SQL Server�� mysql-MYSQL oracle-ORACLE
	db_addr= '172.20.0.244',		--���ݿ��ַ
	db_dbname = 'myoracle',	--���ݿ���
	db_username= 'hxasset',				--�û���
	db_pwd = 'hxasset'				--����
};

local db = nil;
local function GetDB()
	if db then 
		return db;
	end
	db, msg = hexin.db.ConnectDB(dbset);
	if db == nil then
		print('�������ݿ�ʧ��:', msg);
		return  db, msg;
	end
	return db;
end
-------------------------------------------------------------------------------


--ִ��SQL���
--sql ��Ҫִ�е�sql���
--����ֵ��
--�ɹ�������£�����б��أ���ô���ر����ݣ�������ض������
--û�б��أ���ô����true/nil�� �����nil����ô�ڶ�������ֵ���ش�����Ϣ
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

	--���ض����
	return unpack(tlist);
end
