-------------------------------------------------------------------------------
-- 行情获取模块
-- 
-- @author lontoken@gmail.com
--
-- @creation time 2014-03-17
-------------------------------------------------------------------------------
module('util.loger', package.seeall);


local LogerFile = assert(io.open("log.log", "a"));



function GenTableStr (tbl)
    local msgstr;
    for k, v in pairs(tbl) do
        if type(v) ~= 'table' then
            if msgstr then
                msgstr = msgstr .. "," .. k .. '=' .. tostring(v) .. " " .. type(v);
            else
                msgstr =  k .. '=' .. tostring(v) .. " " .. type(v);
            end
        else
            if msgstr then
                msgstr = msgstr .. ' ' .. k .. '={';
            else
                msgstr = k .. '={';
            end
            msgstr = string.format("%s%s", msgstr, GenTableStr(v) .. '}');
        end
    end
    return msgstr or "";
end

function Debug(...)
    --LogerFile:write(..., "\n");
end

function Info(...)
    LogerFile:write(..., "\n");
end

function Warn(...)
    LogerFile:write(..., "\n");
    print(...);
end

function Error(...)
    LogerFile:write(..., "\n");
    print(...);
end