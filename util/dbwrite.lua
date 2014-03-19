---------------------------------
--! @file util/dbwrite.lua
--! @brief 数据定入模块
--!
--! @author lontoken@gmail.com 
--! @data 2014-03-19
---------------------------------
module('util.dbwrite', package.seeall);

local sqlite = require("lsqlite3");

local DB;

function InitDataBase()
    local DB = sqlite.open("db\\market.db")

    DB:exec[[
        CREATE TABLE IF NOT EXISTS market 
            (id, name, parent);
        CREATE TABLE IF NOT EXISTS stock 
            (code, market, name, jianpin);
        CREATE TABLE IF NOT EXISTS daytrend 
            (code, market, time, open_price, close_price, high_price, low_price, volnum);

        CREATE UNIQUE INDEX IF NOT EXISTS idx_mr_pk ON market(id);
        CREATE UNIQUE INDEX IF NOT EXISTS idx_st_pk ON stock(code, market);
        CREATE UNIQUE INDEX IF NOT EXISTS idx_dt_pk ON offhbque(code, market, time);
    ]]
end

function UnintiDataBase()
    if DB then
        DB:close();
    end
end


function InsertMarket(dataList)
    local sql;
    local sqlList = {};
    local item;
    for idx = 1, #dataList do
        item = dataList[idx];
        local valus = {
            item.id,
            "'" .. item.name .. "'",
            item.parent,
        };

        sqlList[#sqlList + 1] = [[INSERT INTO market(id, name, parent) 
            VALUES (]] .. table.concat(valus, ", ") .. ");";
    end
    sql = table.concat(sqlList, "");
end


function InsertStock(dataList)
    local sql;
    local sqlList = {};
    local item;
    for idx = 1, #dataList do
        item = dataList[idx];
        local valus = {
            "'" .. item.code .. "'",
            item.market,
            "'" .. item.name .. "'",
            "'" .. item.jianpin .. "'",
        };

        sqlList[#sqlList + 1] = [[INSERT INTO stock(code, market, name, jianpin) 
            VALUES (]] .. table.concat(valus, ", ") .. ");";
    end
    sql = table.concat(sqlList, "");
end


function InsertDayTrend(dataList)
    local sql;
    local sqlList = {};
    local item;
    for idx = 1, #dataList do
        item = dataList[idx];
        local valus = {
            "'" .. item.code .. "'",
            item.market,
            item.time,
            item.open_price,
            item.close_price,
            item.high_price,
            item.low_price,
            item.volnum,
        };

        sqlList[#sqlList + 1] = [[INSERT INTO daytrend(code, market, time, open_price, close_price, high_price, low_price, volnum) 
            VALUES (]] .. table.concat(valus, ", ") .. ");";
    end
    sql = table.concat(sqlList, "");
end
