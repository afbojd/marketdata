---------------------------------
--! @file util/dbwrite.lua
--! @brief 数据定入模块
--!
--! @author lontoken@gmail.com 
--! @data 2014-03-19
---------------------------------
module('util.dbwrite', package.seeall);

local sqlite3 = require("lsqlite3");
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
    local code, msg;
    local fileName = "db\\market.sqlite";
    DB, code, msg = sqlite3.open(fileName);

    if not DB then
        loger.Error("[util.dbwrite.InitDataBase]create database faild.fileName=" .. fileName 
            .. ",code=" .. tostring(code) .. ",msg=" .. tostring(msg));
        return false;
    end

    _G["DB_Market"] = DB;

    local ret = DB:exec([[
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

    if ret ~= sqlite3.OK then
        loger.Error("[util.dbwrite.InitDataBase]exec sql faild.ret=" .. tostring(ret));
        return false;
    end

    loger.Info("[util.dbwrite.InitDataBase]init database success.");
    return true;
end

function UnintiDataBase()
    if DB then
        local ret = DB:close();
        if ret == sqlite3.OK then
            loger.Info("[util.dbwrite.UnintiDataBase]close database faild.ret=" .. tostring(ret));
        else
            loger.Info("[util.dbwrite.UnintiDataBase]close database success.");
        end
    end
end


function InsertMarket(dataList)
    loger.Debug("[util.dbwrite.InsertMarket]#dataList=" .. #dataList);

    local item, ret;
    local insertCount = 0;

    local insert_stmt, msg = DB:prepare("INSERT INTO market(id, name, parent) VALUES (?, ?, ?)");

    if type(insert_stmt) ~= "userdata" then
        loger.Error("[util.dbwrite.InsertMarket]prepare sql faild.msg=" .. tostring(msg));
        return;
    end

    DB:exec('begin');
    for idx = 1, #dataList do
        item = dataList[idx];

        ret = insert_stmt:bind_values(item.id, item.name, item.parent);
        if ret ~= sqlite3.OK then
            local valus = {
                item.id,
                "'" .. item.name .. "'",
                item.parent,
            };
            loger.Error("[util.dbwrite.InsertMarket]do insert failse.ret=" .. tostring(ret)
                .. ",INSERT INTO market(id, name, parent) VALUES (" .. table.concat(valus, ", ") .. ");" );
        else
            insertCount = insertCount + 1;
        end

        insert_stmt:step()
        insert_stmt:reset()
    end
    DB:exec('commit');
    insert_stmt:finalize();

    loger.Info("[util.dbwrite.InsertMarket]end.insertCount=" .. insertCount);
    return insertCount;
end


function InsertStock(dataList)
    loger.Info("[util.dbwrite.InsertStock]#dataList=" .. #dataList);

    local item, ret;
    local insertCount = 0;

    local insert_stmt, msg = DB:prepare("INSERT INTO stock(code, market, name, jianpin) VALUES (?, ?, ?, ?)");

    if type(insert_stmt) ~= "userdata" then
        loger.Error("[util.dbwrite.InsertStock]prepare sql faild.msg=" .. tostring(msg));
        return;
    end

    DB:exec('begin');
    for idx = 1, #dataList do
        item = dataList[idx];

        ret = insert_stmt:bind_values(item.code, item.market, item.name, item.jianpin);
        if ret ~= sqlite3.OK then
            local valus = {
                "'" .. item.code .. "'",
                item.market,
                "'" .. item.name .. "'",
                "'" .. item.jianpin .. "'",
            };
            loger.Error("[util.dbwrite.InsertStock]do insert failse.ret=" .. tostring(ret)
                .. ",INSERT INTO market(id, name, parent) VALUES (" .. table.concat(valus, ", ") .. ");" );
        else
            insertCount = insertCount + 1;
        end

        insert_stmt:step()
        insert_stmt:reset()
    end
    DB:exec('commit');
    insert_stmt:finalize();

    loger.Info("[util.dbwrite.InsertStock]insertCount=" .. insertCount);
    return insertCount;
end


function InsertDayTrend(dataList)
    loger.Info("[util.dbwrite.InsertDayTrend]#dataList=" .. #dataList);

    local item, ret;
    local insertCount = 0;
    local insert_stmt, msg = DB:prepare([[INSERT INTO daytrend(code, market, time, open_price, close_price, 
 high_price, low_price, volnum) VALUES (?, ?, ?, ?, ?, ?, ?, ?)]]);

    if type(insert_stmt) ~= "userdata" then
        loger.Error("[util.dbwrite.InsertDayTrend]prepare sql faild.msg=" .. tostring(msg));
        return;
    end

    DB:exec('begin');
    for idx = 1, #dataList do
        item = dataList[idx];
        ret = insert_stmt:bind_values(item.code, item.market, item.time, item.open_price, item.close_price, item.high_price,
                item.low_price, item.volnum);
        
        if ret ~= sqlite3.OK then
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
            loger.Error("[util.dbwrite.InsertDayTrend]do insert failse.ret=" .. tostring(ret)
                .. [[,INSERT INTO daytrend(code, market, time, open_price, close_price, 
 high_price, low_price, volnum) VALUES (]] .. table.concat(valus, ", ") .. ");" );
        else
            insertCount = insertCount + 1;
        end

        insert_stmt:step()
        insert_stmt:reset()
    end
    DB:exec('commit');
    insert_stmt:finalize();

    loger.Info("[util.dbwrite.InsertDayTrend]insertCount=" .. insertCount);
    return insertCount;
end
