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
if not DB then
    local fileName = "db\\market.sqlite";
    DB, code, msg = sqlite3.open(fileName);

    if not DB then
        loger.Error("[util.dbread]create database faild.fileName=" .. fileName 
            .. ",code=" .. tostring(code) .. ",msg=" .. tostring(msg));
        return false;
    end
end

function GetDayTrendCodeFromDB()
    local select_stmt = assert(DB:prepare("select code, count(code) count from daytrend group by code"));

    local codeList = {};
    local codeCount = 0;
    for row in select_stmt:nrows() do
        codeList[row.code] = row.count;
        codeCount = codeCount + 1;
    end

    loger.Info("[util.dbread.GetDayTrendCodeFromDB]codeCount=" .. codeCount);
    return codeList;
end