-------------------------------------------------------------------------------
-- 行情获取模块
-- 
-- @author lontoken@gmail.com
--
-- @creation time 2014-03-17
-------------------------------------------------------------------------------

package.cpath = ".\\?.dll"

local quoteget = require("util.quoteget");
local loger = require("util.loger");
local dbwrite = require("util.dbwrite");
local datainit = require("datainit.init");

dbwrite.InitDataBase();
datainit.Init();
dbwrite.UnintiDataBase();
