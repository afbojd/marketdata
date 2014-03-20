---------------------------------
--! @file util/dbread.lua
--! @brief 数据定入模块
--!
--! @author lontoken@gmail.com 
--! @data 2014-03-20
---------------------------------
module('util.dbread', package.seeall);

local sqlite3 = require("lsqlite3");
local loger = require("util.loger");

local DB = _G["DB_Market"];