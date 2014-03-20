---------------------------------
--! @file util/qoteget.lua
--! @brief 行情获取模块
--!
--! 相关C文件:cifox\marketdef\perioddef.h
--!           cifox\marketdef\typedef.h
--!           cifox\marketdef\marketdef.h
--! 相关文档：
--!           cifox\doc\同花顺HTTP行情接口规范.doc
--!
--! @author lontoken@gmail.com 
--! @data 2014-03-18
---------------------------------

module('util.quoteget', package.seeall);

require('hx');
require('hexin.util');
require('hexin.xml');
local loger = require("util.loger");


local reqbody = "Method=Market&CodeList=16;32&Append=P";
local HQURL = "http://122.224.215.36/hexin";

Market_SH = 16;
Market_SZ = 32;
Market_QH = 64;

QuoteKey_Time = 1;
QuoteKey_Code = 5;
QuoteKey_OpenPrice = 7;
QuoteKey_HighPrice = 8;
QuoteKey_LowPrice = 9;
QuoteKey_LatestePrice = 10;
QuoteKey_ClosePrice = 11;
QuoteKey_Volnum = 13;
QuoteKey_BuyPrice1 = 24;
QuoteKey_BuyCount1 = 25;
QuoteKey_BuyPrice2 = 26;
QuoteKey_BuyCount2 = 27;
QuoteKey_BuyPrice3 = 28;
QuoteKey_BuyCount3 = 29;
QuoteKey_SalePrice1 = 30;
QuoteKey_SaleCount1 = 31;
QuoteKey_SalePrice2 = 32;
QuoteKey_SaleCount2 = 33;
QuoteKey_SalePrice3 = 34;
QuoteKey_SaleCount3 = 35;

QuoteKeyRealTimeMap = {
    [QuoteKey_OpenPrice] = "open_price",
    [QuoteKey_HighPrice] = "high_price",
    [QuoteKey_LowPrice] = "low_price",
    [QuoteKey_LatestePrice] = "lateste_price",
    [QuoteKey_ClosePrice] = "close_price",
    [QuoteKey_Volnum] = "volnum",
    [QuoteKey_BuyPrice1] = "buy_price1",
    [QuoteKey_BuyCount1] = "buy_count1",
    [QuoteKey_BuyPrice2] = "buy_price2",
    [QuoteKey_BuyCount2] = "buy_count2",
    [QuoteKey_BuyPrice3] = "buy_price3",
    [QuoteKey_BuyCount3] = "buy_count3",
    [QuoteKey_SalePrice1] = "sale_price1",
    [QuoteKey_SaleCount1] = "sale_count1",
    [QuoteKey_SalePrice2] = "sale_price2",
    [QuoteKey_SaleCount2] = "sale_count2",
    [QuoteKey_SalePrice3] = "sale_price3",
    [QuoteKey_SaleCount3] = "sale_count3",
};

--! @brief 获取指定市场的子市场信息
--! @param codeList 市场列表，如"16", "16;30"
--! @return 返回获取的所有子市场信息
--! @retval nil 失败
--! @retval table { market = {name, items = {{id, name}, ... } ... }
function GetMarketInfo(codeList)
    loger.Debug("[util.quoteget.GetMarketInfo]#codeList=" .. #codeList);

    local req = "Method=Market&CodeList=" .. codeList;

    loger.Debug("[util.quoteget.GetMarketInfo]req=" .. req);
    local response, msg = hexin.util.httpRequest(HQURL, req);

    if type(response) ~= 'string' then
        loger.Error("[util.quoteget.GetMarketInfo]http faild,msg=" .. tostring(msg));
        return nil;
    end

    local root = hexin.xml.parse_string(response);
    if type(root) ~= "table" then
        loger.Error("[util.quoteget.GetMarketInfo]response error,response=" .. tostring(response));
        return nil;
    end

    loger.Debug("[util.quoteget.GetMarketInfo]root=" .. root:output());

    local marketList = {};

    local marketId;
    for market in root:foreach_child() do
        local record = market:get_child("Record");
        local items = {};

        marketId = tonumber(record:get_attr("Market"));
        marketList[marketId] = {
            ["name"] = record:get_attr("Name"),
            ["items"] = items,
        };

        for item in record:foreach_child() do
            items[#items + 1] = {
                id = tonumber(item:get_attr("Id")),
                name = item:get_child("Value"):get_text(),
            };
        end
    end

    loger.Debug("[util.quoteget.GetMarketInfo]#marketList=" .. #marketList);
    return marketList;
end


--! @brief 获取指定市场的证券信息，包括证券代码、证券名称、拼音简码
--! @param codeList 市场列表，如"16", "16;30"
--! @return 返回获取的所有证券信息
--! @retval nil 失败
--! @retval table {market ={name, stocks = {{code, name, jianpin} ... } ... }
function GetStockByMarket(marketList)
    loger.Info("[util.quoteget.GetStockByMarket]marketList=" .. marketList);

    local req = "Method=Market&CodeList=" .. marketList .. "&Append=P";
    local response, msg = hexin.util.httpRequest(HQURL, req);

    if type(response) ~= 'string' then
        loger.Error("[util.quoteget.GetStockByMarket]http faild,msg=" .. tostring(msg));
        return nil;
    end

    local root = hexin.xml.parse_string(response);
    if type(root) ~= "table" then
        loger.Error("[util.quoteget.GetStockByMarket]response error,response=" .. tostring(response));
        return nil;
    end

    local stockList = {};

    local marketId;
    local stockCount = 0;
    for pyjcResult in root:foreach_child() do
        local record = pyjcResult:get_child("Record");
        local stocks = {};
        marketId = tonumber(record:get_attr("Market"));

        stockList[marketId] = {
            ["name"] = record:get_attr("Name");
            ["stocks"] = stocks;
        };

        local curTxt, idx, code, name, jianpin;
        for py in record:foreach_child() do
            local txt = py:get_text();

            curTxt = txt;
            idx = string.find(curTxt, "|");
            code = string.sub(curTxt, 1, idx-1);
            curTxt = string.sub(curTxt, idx + 1);

            idx = string.find(curTxt, "|");
            name = string.sub(curTxt, 1, idx-1);
            curTxt = string.sub(curTxt, idx + 1);

            idx = string.find(curTxt, "|");
            jianpin = string.sub(curTxt, 1, idx-1);
            curTxt = string.sub(curTxt, idx + 1);

            stocks[#stocks + 1] = {
                ["code"] = code,
                ["name"] = name,
                ["jianpin"] = jianpin,
                ["market"] = tonumber(curTxt),
            };
            stockCount = stockCount + 1;
        end
    end

    loger.Debug("[util.quoteget.GetStockByMarket]#stockList=" .. #stockList .. ",stockCount=" .. stockCount);
    return stockList;
end


--! @brief 获取指定证券的实时行情，包括最新价、3档的买卖价格和数量
--! @param codeList 证券列表，{{code, market}, ... }
--! @return 返回获取的所有证券行情信息
--! @retval nil 失败
--! @retval table {code = {market, lateste_price, buy_price1, buy_count1, ... , sale_price3, sale_count3}, ... }
function GetRealTimeQuote(codeList)
    local codestr = "";

    local item;
    if #codeList >= 1 then
        item = codeList[1];
        codestr = codestr .. item.market .. "(" .. item.code .. ")";
    end

    for idx = 2, #codeList do
        item = codeList[idx];
        codestr = ";" .. codestr .. item.market .. "(" .. item.code .. ")";
    end

    local req = "Method=Quote&datetime=0(0-0)&datatype=10,24,25,26,27,28,29,30,31,32,33,34,35&codelist=" .. codestr;
    local response, msg = hexin.util.httpRequest(HQURL, req);

    if type(response) ~= 'string' then
        loger.Error("[util.quoteget.GetRealTimeQuote]http faild,msg=" .. tostring(msg));
        return nil;
    end

    local root = hexin.xml.parse_string(response);
    if type(root) ~= "table" then
        loger.Error("[util.quoteget.GetRealTimeQuote]response error,response=" .. tostring(response));
        return nil;
    end

    local quoteList = {};
    local id, value, marketId, quote, code;
    for dataResult in root:foreach_child() do
        for record in dataResult:foreach_child() do
            quote = {};
            for item in record:foreach_child() do
                id = tonumber(item:get_attr("Id"));
                value  = item:get_child("Value"):get_text();

                quote.market = tonumber(item:get_attr("Market"));
                if id == QuoteKey_Code then
                    code = value;
                else
                    quote[QuoteKeyRealTimeMap[id]] = tonumber(value);
                end
            end
            quoteList[code] = quote;
        end
    end

    loger.Debug("[util.quoteget.GetRealTimeQuote]quoteList=" .. loger.GenTableStr(quoteList));
    return quoteList;
end


--! @brief 获取指定证券的成交明细
--! @param codeList 证券列表，{{code, market}, ... }
--! @return 返回获取的当天所有成交明细
--! @retval nil 失败
--! @retval table {code = {market, deal_detail = {{time, lateste_price, volnum}, ...}}, ... }，其中时间time格式为HHMMSS的5/6位整数
function GetDealDetail(codeList)
    local codestr = "";

    local item;
    if #codeList >= 1 then
        item = codeList[1];
        codestr = codestr .. item.market .. "(" .. item.code .. ")";
    end

    for idx = 2, #codeList do
        item = codeList[idx];
        codestr = ";" .. codestr .. item.market .. "(" .. item.code .. ")";
    end

    local req = "Method=Quote&datetime=4096(0-0)&datatype=10,13&codelist=" .. codestr;
    local response, msg = hexin.util.httpRequest(HQURL, req);

    if type(response) ~= 'string' then
        loger.Error("[util.quoteget.GetDealDetail]http faild,msg=" .. tostring(msg));
        return nil;
    end

    local root = hexin.xml.parse_string(response);
    if type(root) ~= "table" then
        loger.Error("[util.quoteget.GetDealDetail]response error,response=" .. tostring(response));
        return nil;
    end

    local quoteList = {};
    local id, value, marketId, quote, timeTab, dealDetail, dealItem, code, codeIndex;
    for dataResult in root:foreach_child() do
        codeIndex = dataResult:get_child("CodeIndex");
        dealDetail = {};
        code = codeIndex:get_attr("Code");

        quote = {
            market = tonumber(codeIndex:get_attr("Market")),
            deal_detail = dealDetail,
        };
        quoteList[code] = quote;

        for record in codeIndex:foreach_child() do
            dealItem = {};
            for item in record:foreach_child() do
                id = tonumber(item:get_attr("Id"));
                value = item:get_child("Value"):get_text();

                if id == QuoteKey_Time then
                    timeTab = os.date("*t", tonumber(value));
                    dealItem.time = timeTab.hour * 10000 + timeTab.min * 100 + timeTab.sec;
                else
                    dealItem[QuoteKeyRealTimeMap[id]] = tonumber(value);
                end
                
            end
            dealDetail[#dealDetail + 1] = dealItem;
        end
    end

    loger.Debug("[util.quoteget.GetDealDetail]quoteList=" .. loger.GenTableStr(quoteList));
    return quoteList;
end


--! @brief 获取指定证券的分时行情，包括最新价和成交量
--! @param codeList 证券列表，{{code, market}, ... }
--! @return 返回获取的当天所有分时行情
--! @retval nil 失败
--! @retval table {code = {market, trends = {{time, lateste_price, volnum}, ...}}, ... }，其中时间time格式为HHMMSS的5/6位整数
function GetMinuteTrend(codeList)
    local codestr = "";

    local item;
    if #codeList >= 1 then
        item = codeList[1];
        codestr = codestr .. item.market .. "(" .. item.code .. ")";
    end

    for idx = 2, #codeList do
        item = codeList[idx];
        codestr = ";" .. codestr .. item.market .. "(" .. item.code .. ")";
    end

    local req = "Method=Quote&datetime=8192(0-0)&datatype=10,13&codelist=" .. codestr;
    local response, msg = hexin.util.httpRequest(HQURL, req);

    if type(response) ~= 'string' then
        loger.Error("[util.quoteget.GetMinuteTrend]http faild,msg=" .. tostring(msg));
        return nil;
    end

    local root = hexin.xml.parse_string(response);
    if type(root) ~= "table" then
        loger.Error("[util.quoteget.GetMinuteTrend]response error,response=" .. tostring(response));
        return nil;
    end

    local trendList = {};
    local id, value, marketId, quote, timeTab, trends, dealItem, code, codeIndex;
    for dataResult in root:foreach_child() do
        codeIndex = dataResult:get_child("CodeIndex");
        trends = {};

        code = codeIndex:get_attr("Code");

        quote = {
            ["market"] = tonumber(codeIndex:get_attr("Market")),
            ["trends"] = trends,
        };
        trendList[code] = quote;

        for record in codeIndex:foreach_child() do
            dealItem = {};
            for item in record:foreach_child() do
                id = tonumber(item:get_attr("Id"));
                value = item:get_child("Value"):get_text();

                if id == QuoteKey_Time then
                    dealItem.time = value % 1000000;
                else
                    dealItem[QuoteKeyRealTimeMap[id]] = tonumber(value);
                end
                
            end
            trends[#trends + 1] = dealItem;
        end
    end

    loger.Debug("[util.quoteget.GetMinuteTrend]trendList=" .. loger.GenTableStr(trendList));
    return trendList;
end


--! @brief 获取指定证券的日行情信息，包括开盘价、收盘价、最高价、最低价、成交量
--! @param codeList 证券列表，{{code, market}, ... }
--! @param begTime 开始时间
--! @param endTime 结束时间
--! @return 返回获取的当天所有分时行情
--! @retval nil 失败
--! @retval table {code = {market, trends = {{time, open_price, close_price, high_price, low_price, volnum}, ...}}, ... }，
--      其中时间time格式为HHMMSS的5/6位整数
function GetDayTrend(codeList, begTime, endTime)
    loger.Info("[util.quoteget.GetDayTrend]#codeList=" .. #codeList);

    local codestr = "";
    begTime = begTime or 0;
    endTime = endTime or 0;

    local item;
    if #codeList >= 1 then
        item = codeList[1];
        codestr = codestr .. item.market .. "(" .. item.code .. ")";
    end

    for idx = 2, #codeList do
        item = codeList[idx];
        codestr = codestr .. ";" .. item.market .. "(" .. item.code .. ")";
    end

    local req = "Method=Quote&datetime=16384(" .. begTime .. "-" .. endTime .. ")&datatype=7,8,9,11,13&codelist=" .. codestr;

    loger.Info("[util.quoteget.GetDayTrend]req=" .. req);
    local response, msg = hexin.util.httpRequest(HQURL, req);

    if type(response) ~= 'string' then
        loger.Error("[util.quoteget.GetDayTrend]http faild,msg=" .. tostring(msg));
        return nil;
    end

    local root = hexin.xml.parse_string(response);
    if type(root) ~= "table" then
        loger.Error("[util.quoteget.GetDayTrend]response error,response=" .. tostring(response));
        return nil;
    end

    --print("root:", root:output());

    local trendList = {};
    local id, value, marketId, quote, timeTab, trends, dealItem, code, codeIndex;
    local trendCount = 0;
    for dataResult in root:foreach_child() do
        codeIndex = dataResult:get_child("CodeIndex");

        if codeIndex then
            for codeIndex in dataResult:foreach_child() do
                code = codeIndex:get_attr("Code");
                marketId = tonumber(codeIndex:get_attr("Market"));

                for record in codeIndex:foreach_child() do
                    trendItem = {};
                    for item in record:foreach_child() do
                        id = tonumber(item:get_attr("Id"));

                        value = item:get_child("Value"):get_text();

                        --print(id, value);

                        if id == QuoteKey_Time then
                            trendItem["time"] = tonumber(value);
                        elseif id == QuoteKey_Code then
                            code = value;
                            marketId = tonumber(item:get_attr("Market"));
                        else
                            trendItem[QuoteKeyRealTimeMap[id]] = tonumber(value);
                        end
                        
                    end

                    if code then
                        if not trendList[code] then
                            trendList[code] = {
                                market = marketId,
                                trends = {},
                            };
                        end
                        trends = trendList[code].trends;
                        trends[#trends + 1] = trendItem;
                        trendCount = trendCount + 1;
                    end
                end
            end
        else
            for record in dataResult:foreach_child() do
                trendItem = {};
                for item in record:foreach_child() do
                    id = tonumber(item:get_attr("Id"));

                    value = item:get_child("Value"):get_text();

                    --print(id, value);

                    if id == QuoteKey_Time then
                        trendItem["time"] = tonumber(value);
                    elseif id == QuoteKey_Code then
                        code = value;
                        marketId = tonumber(item:get_attr("Market"));
                    else
                        trendItem[QuoteKeyRealTimeMap[id]] = tonumber(value);
                    end
                    
                end

                --print(loger.GenTableStr(trendItem));

                if code then
                    if not trendList[code] then
                        trendList[code] = {
                            market = marketId,
                            trends = {},
                        };
                    end
                    trends = trendList[code].trends;
                    trends[#trends + 1] = trendItem;
                    trendCount = trendCount + 1;
                end
            end
        end
    end

    loger.Info("[util.quoteget.GetDayTrend]trendCount=" .. trendCount);
    return trendList;
end

-- GetDayTrend({
--     {
--         code = "600000",
--         market = 17,
--     },
--     {
--         code = "600500",
--         market = 17,
--     },
--     });

-- local root = hexin.xml.parse_string(ret);
-- print("root:", root:output());
-- print("MarketResult:", root:get_child("MarketResult"));

-- print("MarketResult\\Record:", root:find_path("MarketResult\\Record"));

-- -- local itemList = root:find_path("MarketResult\\Record\\Item");
-- -- print("itemList=", itemList:output());




-- local reqHq = "method=quote&datetime=16384(-2-1)&datatype=7,8,13&codelist=17(600000)";
-- local ret, msg = hexin.util.httpRequest(HQURL, reqHq);
-- if type(ret) ~= 'string' then
--     print("[quote]" .. tostring(msg));
-- end
-- local root = hexin.xml.parse_string(ret);
-- print("reqHqroot:", root:output());


-- local reqHq = "method=quote&datetime=16384(-100-0)&datatype=OPEN,CLOSE&codelist=17(600000)";
-- local ret, msg = hexin.util.httpRequest(HQURL, reqHq);
-- if type(ret) ~= 'string' then
--     print("[quote]" .. tostring(msg));
-- else
--     print(ret);
-- end
-- local root = hexin.xml.parse_string(ret);
-- print("root1:", root:output());