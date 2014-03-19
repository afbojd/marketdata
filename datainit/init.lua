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
local loger = require("util.loger");
local quoteget = require("util.quoteget");

function Init()
    local marketList = mkinit.MarketInit();

    stinit.StockInit(quoteget.Market_SH);
    stinit.StockInit(quoteget.Market_SZ);
end