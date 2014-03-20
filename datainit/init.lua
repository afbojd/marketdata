---------------------------------
--! @file util/dbwrite.lua
--! @brief 数据初始化
--!
--! @author lontoken@gmail.com 
--! @data 2014-03-19
---------------------------------
module('datainit.init', package.seeall);

local mkinit = require("datainit.marketinit");
local stinit = require("datainit.stockinit");
local trinit = require("datainit.trendinit");
local loger = require("util.loger");
local quoteget = require("util.quoteget");

function Init()
     local marketList = mkinit.MarketInit();

    local skListSH = stinit.StockInit(quoteget.Market_SH);
    local skListSZ = stinit.StockInit(quoteget.Market_SZ);

    trinit.DayTrendInit(skListSH);
    trinit.DayTrendInit(skListSZ);
end