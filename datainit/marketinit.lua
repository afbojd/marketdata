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

function MarketInit()
    local marketStr = {
        quoteget.Market_SH,
        quoteget.Market_SZ,
        quoteget.Market_QH,
    };
    marketStr = table.concat(marketStr, ";");

    local dataList = quoteget.GetMarketInfo(marketStr);
    local marketList = {};
    if dataList then
        for mk, mv in pairs(dataList) do
            if type(mv) == "table" then
                local parentId = mk;
                local parentName = mv.name;
                local item;
                for idx = 1, #(mv.items) do
                    item = (mv.items)[idx];
                    marketList[#marketList + 1] = {
                        ["id"] = item.id,
                        ["name"] = item.name,
                        ["parent"] = parentId,
                    };
                end
            end
        end
    else
        loger.Error("[datainit.marketinit.MarketInit]get market data faild.");
        return nil;
    end

    loger.Debug("[datainit.marketinit.MarketInit]marketList=" .. loger.GenTableStr(marketList));
    dbwrite.InsertMarket(marketList);

    return marketList;
end