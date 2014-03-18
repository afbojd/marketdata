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

QuoteKey_Time = 1;
QuoteKey_Code = 5;

QuoteKey_LatestePrice = 10;
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
    [QuoteKey_LatestePrice] = "lateste_price",
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
--! @param codeList 市场列表，如"16", "16,30"
--! @return 返回获取的所有子市场信息
--! @retval nil 失败
--! @retval table {{ market, name, items = {{id, name} ... } ... }
function GetMarketInfo(codeList)
    local req = "Method=Market&CodeList=" .. codeList;
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

    local marketList = {};

    for market in root:foreach_child() do
        local record = market:get_child("Record");
        local items = {};
        marketList[#marketList + 1] = {
            ["market"] = tonumber(record:get_attr("Market"));
            ["name"] = record:get_attr("Name");
            ["items"] = items;
        };

        for item in record:foreach_child() do
            items[#items + 1] = {
                id = tonumber(item:get_attr("Id")),
                name = item:get_child("Value"):get_text(),
            };
        end
    end

    loger.Debug("[util.quoteget.GetMarketInfo]marketList=" .. loger.GenTableStr(marketList));
    return marketList;
end


--! @brief 获取指定市场的证券信息，包括证券代码、证券名称、拼音简码
--! @param codeList 市场列表，如"16", "16,30"
--! @return 返回获取的所有证券信息
--! @retval nil 失败
--! @retval table {{ market, name, stocks = {{code, name, jianpin} ... } ... }
function GetStockByMarket(marketList)
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

    --print(root:output());

    local stockList = {};

    for pyjcResult in root:foreach_child() do
        local record = pyjcResult:get_child("Record");
        local stocks = {};
        stockList[#stockList + 1] = {
            ["market"] = tonumber(record:get_attr("Market"));
            ["name"] = record:get_attr("Name");
            ["stocks"] = stocks;
        };

        local curTxt, idx;
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
            };

        end
    end

    loger.Debug("[util.quoteget.GetStockByMarket]stockList=" .. loger.GenTableStr(stockList));
    return stockList;
end


--! @brief 获取指定证券的实时行情，包括最新价、3档的买卖价格和数量
--! @param codeList 证券列表，{{code, market}, ... }
--! @return 返回获取的所有证券行情信息
--! @retval nil 失败
--! @retval table {{code, market, lateste_price, buy_price1, buy_count1, ... , sale_price3, sale_count3}, ... }
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
    local id, value, marketId, quote;
    for dataResult in root:foreach_child() do
        for record in dataResult:foreach_child() do
            quote = {};
            for item in record:foreach_child() do
                id = tonumber(item:get_attr("Id"));
                value  = item:get_child("Value"):get_text();

                quote.market = tonumber(item:get_attr("Market"));
                if id == QuoteKey_Code then
                    quote.code = value;
                else
                    quote[QuoteKeyRealTimeMap[id]] = value;
                end
            end
            quoteList[#quoteList + 1] = quote;
        end
    end

    loger.Debug("[util.quoteget.GetRealTimeQuote]quoteList=" .. loger.GenTableStr(quoteList));
    return quoteList;
end


--! @brief 获取指定证券的成交明细
--! @param codeList 证券列表，{{code, market}, ... }
--! @return 返回获取的当天所有成交明细
--! @retval nil 失败
--! @retval table {{code, market, deal_detail = {{time, lateste_price, volnum}, ...}}, ... }，其中时间time格式为HHMMSS的5/6位整数
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
    local id, value, marketId, quote, timeTab, dealDetail, dealItem;
    for dataResult in root:foreach_child() do
        codeIndex = dataResult:get_child("CodeIndex");
        dealDetail = {};
        quote = {
            code = codeIndex:get_attr("Code"),
            market = tonumber(codeIndex:get_attr("Market")),
            deal_detail = dealDetail,
        };
        quoteList[#quoteList + 1] = quote;

        for record in codeIndex:foreach_child() do
            dealItem = {};
            for item in record:foreach_child() do
                id = tonumber(item:get_attr("Id"));
                value = item:get_child("Value"):get_text();

                if id == QuoteKey_Time then
                    timeTab = os.date("*t", tonumber(value));
                    dealItem.time = timeTab.hour * 10000 + timeTab.min * 100 + timeTab.sec;
                else
                    dealItem[QuoteKeyRealTimeMap[id]] = value;
                end
                
            end
            dealDetail[#dealDetail + 1] = dealItem;
        end
    end

    loger.Debug("[util.quoteget.GetDealDetail]quoteList=" .. loger.GenTableStr(quoteList));
    return quoteList;
end


-- GetDealDetail({
--     {
--         code = "600000",
--         market = 17,
--     },

--     });

-- local root = hexin.xml.parse_string(ret);
-- print("root:", root:output());
-- print("MarketResult:", root:get_child("MarketResult"));

-- print("MarketResult\\Record:", root:find_path("MarketResult\\Record"));

-- -- local itemList = root:find_path("MarketResult\\Record\\Item");
-- -- print("itemList=", itemList:output());




local reqHq = "method=quote&datetime=4096(0-0)&datatype=10,24,25,26,27,28,29,30,31,32,33,34,35&codelist=17(600000);17(600500)";
local reqHq = "method=quote&datetime=16384(0-0)&datatype=7,8,11,10,13&codelist=17(600000);17(600500)";
local ret, msg = hexin.util.httpRequest(HQURL, reqHq);
if type(ret) ~= 'string' then
    print("[quote]" .. tostring(msg));
end
local root = hexin.xml.parse_string(ret);
print("reqHqroot:", root:output());

-- temp = os.date("*t", 1395105243)
-- print(loger.GenTableStr(temp))

-- local reqHq = "method=quote&datetime=16384(-100-0)&datatype=OPEN,CLOSE&codelist=17(600000)";
-- local ret, msg = hexin.util.httpRequest(HQURL, reqHq);
-- if type(ret) ~= 'string' then
--     print("[quote]" .. tostring(msg));
-- else
--     print(ret);
-- end
-- local root = hexin.xml.parse_string(ret);
-- print("root1:", root:output());