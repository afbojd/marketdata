---------------------------------
--! @file util/dbwrite.lua
--! @brief 证券信息初始化
--!
--! @author lontoken@gmail.com 
--! @data 2014-03-19
---------------------------------
module('datainit.stockinit', package.seeall);

local quoteget = require("util.quoteget");
local dbwrite = require("util.dbwrite");
local loger = require("util.loger");

function StockInit(market)
    loger.Info("[datainit.stockinit.StockInit]market=" .. market);

    local stockCount = 0;
    local dataList = quoteget.GetStockByMarket(market);
    local stockList = {};

    if dataList then
        for mk, mv in pairs(dataList) do
            if type(mv) == "table" then
                local marketId = mk;
                local item;
                for idx = 1, #(mv.stocks) do
                    item = (mv.stocks)[idx];
                    stockList[#stockList + 1] = {
                        ["code"] = item.code,
                        ["name"] = item.name,
                        ["jianpin"] = item.jianpin,
                        ["market"] = marketId,
                    };
                end
            end
        end
    else
        loger.Error("[datainit.stockinit.StockInit]get stock data faild.");
        return nil;
    end

    loger.Debug("[datainit.stockinit.StockInit]stockList=" .. loger.GenTableStr(stockList));
    dbwrite.InsertStock(stockList);
    stockCount = stockCount + #stockList;

    return stockCount;
end