--************************浙江同花顺网络信息股份有限公司****************************
--                                资管系统 V2.0.0
-- 应用程序主入口，提供启动相关配置
--
-- 创建时间: 2013/6/8
-- 作者:     王建 wangjian@myhexin.com
--
--

module('app.main', package.seeall);
require('hexin.base');
require('hexin.app');
require('hexin.func');
require('hexin.ini');
require('hexin.log');
require('hexin.threadex');

local opt = hexin.func.getopt(arg or {});

local ini = hexin.ini.set_def_ini(opt['p'] or 'config.ini');
local config = {
    local_listen_port = hexin.ini.read('publish', 'local_listen_port', '9990'),
    http_port = hexin.ini.read('publish', 'http_port', '9090'),
    sbhb_address = hexin.ini.read('publish', 'sbhb_address', '127.0.0.1:9901'),
    dp_address = hexin.ini.read('publish', 'dp_address', '127.0.0.1:8011'),
    log_address = hexin.ini.read('publish', 'log_address', '127.0.0.1:8001'),
    
    write_thread_log = hexin.ini.read('log', 'write_thread_log', 'true') == 'true' or false,
    show_thread_log = hexin.ini.read('log', 'show_thread_log', 'true') == 'true' or false,
    max_uptime = tonumber(hexin.ini.read('log', 'max_uptime', '5')),
    max_item = tonumber(hexin.ini.read('log', 'max_item', '300')),
};

--配置
local setting =
{
    --监听端口
    transmid =
    {
        isserver = true,    --监听服务模块标志，必须
        handle_module = 'mid.wt',    --数据处理模块
        listen_name =  'wtsvr';       --hexin.util.create_guid(),            --监听对象名
        queue_name  =   hexin.util.create_guid(),                --数据接收队列名
        port = config.local_listen_port,            --监听端口
        protocol  = 'hx',        --监听协议，现在支持， hx-核新包格式， http-http协议，step-step协议，空-流格式
        threadcnt = tonumber(hexin.ini.read('sys', 'thread_cnt', '3')),    --处理线程数量,只能是1，因为此线程中会负责用户的分发

        minrevdata = 4;
        linkverify = '1';
        

        write_log = config.write_thread_log;        --记录线程日志
        show_log  = config.show_thread_log;        --显示线程日志
    },

    --启动log功能
    log = 
    {
        deflogfile = 'log/%Y%m%d.log';    --默认日志路径
        maxuptime  = config.max_uptime;         --日志最长缓存时间(秒)
        maxitem    = config.max_item;         --日志最长缓存记录条数 
        --以上两个条件任意一个达到都会触发写盘操作
    };

    --日志服务配置
--    logsvr = 
--    {
--        --这部分是固定配置
--        isserver = true,    --监听服务模块标志，必须
--        handle_module = 'app.apsvrman',    --数据处理模块        
--        queue_name  =   hexin.util.create_guid(),                --数据接收队列名        
--        protocol  = 'hx',        --监听协议，现在支持， hx-核新包格式， http-http协议，step-step协议，空-流格式        
--        minrevdata = 4;
--        linkverify = '1';
--        write_log = true;        --记录线程日志
--        show_log  = true;        --显示线程日志
--    
--        --个性配置
--        port = hexin.ini.read('sys', 'listen_port', '8001'),            --监听端口
--        threadcnt = tonumber(hexin.ini.read('sys', 'thread_cnt', '5')),    --处理线程数量
--        listen_name =   'log_server',            --监听对象名,可以根据名称获得连接对象，方便广播数据
--        handle_script = 'tradelog.server';            --数据处理模块
--    };
    
    httpsvr = 
    {
        isserver = true;
        handle_module = 'mgrs.manager';
        queue_name = hexin.util.create_guid();
        protocol = 'http';
        port = config.http_port;
        threadcnt = 5;    
        listen_name = 'apmanager';
    };

    --服务器连接对象管理器
    severlinkman = 
    {
        isthread  = true;        --线程池启动标志，必须
        script    = 'app.svrlinkman',    --线程脚本
        threadcnt = 1;            --处理线程数
        write_log = true;        --记录线程日志
        show_log  = true;        --显示线程日志

        --连接设置
        linkset = 
        {
            --需要连接不同的服务器的时候，
            --建立多个类似的配置即可
            logserver =        --服务器名称,可以在任意线程中沟通过app.link.GetLink(id)获得此配置的连接对象，id参数即为此名称
            {
                addr    = config.log_address;    --服务器地址
                handle    = 'asm.cliscript.handlelog';    --异步数据处理模块
            },
            sbhbserver = 
            {
                addr = config.sbhb_address;     --127.0.0.1 --192.168.27.97
                handle = 'asm.cliscript.handlesb';
            },
            
            dpserver = 
            {
                addr = config.dp_address;
                handle = 'asm.cliscript.handledp';
            },
        };
    };
};

--启动业务模块
require('app.asm');

--启动数据库心跳线程
hexin.thread.start_threads('app.dbheartbeat', 1, {});

hexin.app.run(setting);
