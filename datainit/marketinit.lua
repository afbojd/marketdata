---------------------------------
--! @file util/dbwrite.lua
--! @brief 数据初始化
--!
--! @author lontoken@gmail.com 
--! @data 2014-03-19
---------------------------------
module('datainit.marketinit', package.seeall);

local quoteget = require("util.quoteget");
local dbwrite = require("util.dbwrite");
local loger = require("util.loger");

function InitMarket()
    local mkList = {
        quoteget.Market_SH,
        quoteget.Market_SZ,
        quoteget.Market_QH,
    };
    mkList = table.concat(mkList, ", ");

    local dataList = quoteget.GetMarketInfo(mkList);
    if dataList then
        
    else
        loger.Error("[datainit.marketinit.InitMarket]get market data faild.");
        return 0;
    end
end