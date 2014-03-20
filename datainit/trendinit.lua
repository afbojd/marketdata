---------------------------------
--! @file util/trendinit.lua
--! @brief 证券的相关趋势行情数据
--!
--! @author lontoken@gmail.com 
--! @data 2014-03-19
---------------------------------
module('datainit.trendinit', package.seeall);

local quoteget = require("util.quoteget");
local dbwrite = require("util.dbwrite");
local loger = require("util.loger");

local StockList = {
    {code ="600570", market = 17},
    {code ="600000", market = 17},
    {code ="600500", market = 17},
};

function DayTrendInit(stockList)
    loger.Info("[datainit.trendinit.DayTrendInit]#stockList=" .. #stockList);

    local item;
    local idx = 1;
    local skList = {};
    local initCount = 0;
    while idx <= #stockList do
        item = stockList[idx];

        skList[#skList + 1] = item;
        if #skList == 10 or idx == #stockList then
            local trendData = quoteget.GetDayTrend(skList);

            if trendData then
                local trendList = {};
                for mk, mv in pairs(trendData) do
                    if type(mv) == "table" then
                        local marketId = mv.market;
                        local code = mk;
                        for idxInner = 1, #(mv.trends) do
                            item = (mv.trends)[idxInner];
                            trendList[#trendList + 1] = {
                                ["code"] = code,
                                ["market"] = marketId,
                                ["time"] = item.time,
                                ["open_price"] = item.open_price,
                                ["close_price"] = item.close_price,
                                ["high_price"] = item.high_price,
                                ["low_price"] = item.low_price,
                                ["volnum"] = item.volnum,
                            };
                        end
                    end
                end

                dbwrite.InsertDayTrend(trendList);
                initCount = initCount + #trendList;
            else
                loger.Error("[datainit.trendinit.DayTrendInit]get trend data faild.");
            end

            skList = {};
        end

        idx = idx + 1;

        loger.Info("[datainit.trendinit.DayTrendInit]idx=" .. idx);

        -- if idx == 100 then
        --     break;
        -- end
    end

    loger.Info("[datainit.trendinit.DayTrendInit]initCount=" .. initCount);
    return initCount;
end