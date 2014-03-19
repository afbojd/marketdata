---------------------------------
--! @file util/dbwrite.lua
--! @brief 数据定入模块
--!
--! @author lontoken@gmail.com 
--! @data 2014-03-19
---------------------------------
module('util.dbwrite', package.seeall);

local sqlite = require("lsqlite3");
local loger = require("util.loger");

local DB = _G["DB_Market"];

--mysql脚本
-- CREATE DATABASE IF NOT EXISTS `market`
--     CHARACTER SET 'utf8'       
--     COLLATE 'utf8_general_ci';

-- CREATE TABLE IF NOT EXISTS market (
--     id int,
--     name char(64),
--     parent int,

--     PRIMARY KEY (id)
-- );

-- CREATE TABLE IF NOT EXISTS stock (
--     code char(32),
--     market int,
--     name char(64),
--     jianpin char(64),

--     PRIMARY KEY (code, market)
-- );

-- CREATE TABLE IF NOT EXISTS daytrend (
--     code char(32),
--     market int,
--     time char(64),
--     open_price double,
--     close_price double,
--     high_price double,
--     low_price double,
--     volnum bigint,

--     PRIMARY KEY (code, market, time)
-- );

function InitDataBase()
    DB = sqlite.open("db\\market.db");
    _G["DB_Market"] = DB;

    DB:exec([[
        CREATE TABLE IF NOT EXISTS market 
            (id, name, parent);
        CREATE TABLE IF NOT EXISTS stock 
            (code, market, name, jianpin);
        CREATE TABLE IF NOT EXISTS daytrend 
            (code, market, time, open_price, close_price, high_price, low_price, volnum);

        CREATE UNIQUE INDEX IF NOT EXISTS idx_mr_pk ON market(id);
        CREATE UNIQUE INDEX IF NOT EXISTS idx_st_pk ON stock(code, market);
        CREATE UNIQUE INDEX IF NOT EXISTS idx_dt_pk ON daytrend(code, market, time);
    ]]);
end

function UnintiDataBase()
    if DB then
        DB:close();
    end
end


function InsertMarket(dataList)
    loger.Debug("[util.dbwrite.InsertMarket]#dataList=" .. #dataList);
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

    if #sqlList > 0 then
        sql = table.concat(sqlList, "");
        local ret = DB:exec(sql);
        loger.Debug("[util.dbwrite.InsertMarket]ret=" .. tostring(ret));
    end
    loger.Debug("[util.dbwrite.InsertMarket]end");
end


function InsertStock(dataList)
    loger.Info("[util.dbwrite.InsertStock]#dataList=" .. #dataList);
    local sql;
    local sqlList = {};
    local item;
    local inertCount = 0;
    for idx = 1, #dataList do
        item = dataList[idx];
        local valus = {
            "'" .. item.code .. "'",
            item.market,
            "'" .. item.name .. "'",
            "'" .. "item.jianpin" .. "'",
        };

        sqlList[#sqlList + 1] = [[INSERT INTO stock(code, market, name, jianpin) VALUES (]] .. table.concat(valus, ", ") .. ");";

        if #sqlList >= 10 then
            sql = table.concat(sqlList, "");
            loger.Debug("[util.dbwrite.InsertStock]sql.10=" .. sql);
            local ret = DB:exec(sql);
            loger.Debug("[util.dbwrite.InsertStock]ret=" .. tostring(ret));
            inertCount = inertCount + #sqlList;
            sqlList = {};
        end
    end
    
    if #sqlList > 0 then
        sql = table.concat(sqlList, "");
        loger.Debug("[util.dbwrite.InsertStock]sql=" .. sql);
        local ret = DB:exec(sql);
        loger.Debug("[util.dbwrite.InsertStock]ret=" .. tostring(ret));
        inertCount = inertCount + #sqlList;
    end
    loger.Info("[util.dbwrite.InsertStock]inertCount=" .. inertCount);
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
