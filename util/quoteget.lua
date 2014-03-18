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


function GetRealTimeQuote(codeList)
    local codestr = "";

    local item;
    if #codeList >= 1 then
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


                if id == 10 then
                    quote.code = value;
                else
                end
            end
        end
    end
end

-- local root = hexin.xml.parse_string(ret);
-- print("root:", root:output());
-- print("MarketResult:", root:get_child("MarketResult"));

-- print("MarketResult\\Record:", root:find_path("MarketResult\\Record"));

-- -- local itemList = root:find_path("MarketResult\\Record\\Item");
-- -- print("itemList=", itemList:output());




local reqHq = "method=quote&datetime=0(0-0)&datatype=10,24,25,26,27,28,29,30,31,32,33,34,35&codelist=17(600000);17(600500)";
local ret, msg = hexin.util.httpRequest(HQURL, reqHq);
if type(ret) ~= 'string' then
    print("[quote]" .. tostring(msg));
end
local root = hexin.xml.parse_string(ret);
print("reqHqroot:", root:output());



-- local reqHq = "method=quote&datetime=16384(-100-0)&datatype=OPEN,CLOSE&codelist=17(600000)";
-- local ret, msg = hexin.util.httpRequest(HQURL, reqHq);
-- if type(ret) ~= 'string' then
--     print("[quote]" .. tostring(msg));
-- else
--     print(ret);
-- end
-- local root = hexin.xml.parse_string(ret);
-- print("root1:", root:output());