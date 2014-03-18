-------------------------------------------------------------------------------
-- 数据库心跳保持者
-- 
-- @author ganlong ganlong@myhexin.com
--
-- @creation time 2013.10.23
-------------------------------------------------------------------------------

module('app.dbheartbeat', package.seeall);

require('hx');
require('hexin.threadex');
require('hexin.setting');
local db = require("app.db");

local thread = hexin.thread;
local setting = hexin.setting;

local loger = require('hexin.log');
local DateStr = os.date("%Y%m%d", os.time());
local FileName_Default = "log/".. DateStr;
local FileName_Debug = FileName_Default .. "_d.log";
local FileName_Info = FileName_Default .. "_i.log";
local FileName_Warn = FileName_Default .. "_w.log";
local FileName_Error = FileName_Default .. "_e.log";

local setting_name_thread_run = "dbheartbeat_thread_run";

function DoDbHeartbeat()
    local pRes, fRes, fMsg = pcall(function()
        local sql = "select 1 from dual";
        local d, msg = db.ExecSql(sql);
        
        if not d then
            return false, "exec sql error.";
        end
        
        print("DoDbHeartbeat");
        loger.write("[app.dbheartbeat.DoDbHeartbeat]DoDbHeartbeat.", FileName_Debug);
        
        return true;
    end);
    
    if not pRes then
        loger.write("[app.dbheartbeat.DoDbHeartbeat]faild.", FileName_Error);
        print("[Error][app.dbheartbeat.DoDbHeartbeat]faild.");
    end
end


--线程入口
hexin.thread.run_main_func(function()
    loger.write("[app.dbheartbeat.run_main_func]call start", FileName_Info);
    
    local runCounter = 0;
    
    local inited = (setting.get_singleval(setting_name_thread_run) == '1');
    
    loger.write("[app.dbheartbeat.run_main_func]inited= " .. tostring(inited), FileName_Info);
    
    if inited then
        return;
    end
    
    setting.set_singleval(setting_name_thread_run, '1');
    
    loger.write("[app.dbheartbeat.run_main_func]loop start.", FileName_Info);
    print("[app.dbheartbeat.run_main_func]loop start.");
    
    while true do
        DoDbHeartbeat();
        
        thread.sleep(60000);
    end

    loger.write("[app.dbheartbeat.run_main_func]call end", FileName_Info);
end);