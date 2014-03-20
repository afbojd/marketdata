-------------------------------------------------------------------------------
-- 行情获取模块
-- 
-- @author lontoken@gmail.com
--
-- @creation time 2014-03-17
-------------------------------------------------------------------------------
module('util.loger', package.seeall);

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
    --print(...);
end

function Info(...)
    print(...);
end

function Warn(...)
    print(...);
end

function Error(...)
    print(...);
end