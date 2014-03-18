--************************�㽭ͬ��˳������Ϣ�ɷ����޹�˾****************************
--                                �ʹ�ϵͳ V2.0.0
-- Ӧ�ó�������ڣ��ṩ�����������
--
-- ����ʱ��: 2013/6/8
-- ����:     ���� wangjian@myhexin.com
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

--����
local setting =
{
    --�����˿�
    transmid =
    {
        isserver = true,    --��������ģ���־������
        handle_module = 'mid.wt',    --���ݴ���ģ��
        listen_name =  'wtsvr';       --hexin.util.create_guid(),            --����������
        queue_name  =   hexin.util.create_guid(),                --���ݽ��ն�����
        port = config.local_listen_port,            --�����˿�
        protocol  = 'hx',        --����Э�飬����֧�֣� hx-���°���ʽ�� http-httpЭ�飬step-stepЭ�飬��-����ʽ
        threadcnt = tonumber(hexin.ini.read('sys', 'thread_cnt', '3')),    --�����߳�����,ֻ����1����Ϊ���߳��лḺ���û��ķַ�

        minrevdata = 4;
        linkverify = '1';
        

        write_log = config.write_thread_log;        --��¼�߳���־
        show_log  = config.show_thread_log;        --��ʾ�߳���־
    },

    --����log����
    log = 
    {
        deflogfile = 'log/%Y%m%d.log';    --Ĭ����־·��
        maxuptime  = config.max_uptime;         --��־�����ʱ��(��)
        maxitem    = config.max_item;         --��־������¼���� 
        --����������������һ���ﵽ���ᴥ��д�̲���
    };

    --��־��������
--    logsvr = 
--    {
--        --�ⲿ���ǹ̶�����
--        isserver = true,    --��������ģ���־������
--        handle_module = 'app.apsvrman',    --���ݴ���ģ��        
--        queue_name  =   hexin.util.create_guid(),                --���ݽ��ն�����        
--        protocol  = 'hx',        --����Э�飬����֧�֣� hx-���°���ʽ�� http-httpЭ�飬step-stepЭ�飬��-����ʽ        
--        minrevdata = 4;
--        linkverify = '1';
--        write_log = true;        --��¼�߳���־
--        show_log  = true;        --��ʾ�߳���־
--    
--        --��������
--        port = hexin.ini.read('sys', 'listen_port', '8001'),            --�����˿�
--        threadcnt = tonumber(hexin.ini.read('sys', 'thread_cnt', '5')),    --�����߳�����
--        listen_name =   'log_server',            --����������,���Ը������ƻ�����Ӷ��󣬷���㲥����
--        handle_script = 'tradelog.server';            --���ݴ���ģ��
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

    --���������Ӷ��������
    severlinkman = 
    {
        isthread  = true;        --�̳߳�������־������
        script    = 'app.svrlinkman',    --�߳̽ű�
        threadcnt = 1;            --�����߳���
        write_log = true;        --��¼�߳���־
        show_log  = true;        --��ʾ�߳���־

        --��������
        linkset = 
        {
            --��Ҫ���Ӳ�ͬ�ķ�������ʱ��
            --����������Ƶ����ü���
            logserver =        --����������,�����������߳��й�ͨ��app.link.GetLink(id)��ô����õ����Ӷ���id������Ϊ������
            {
                addr    = config.log_address;    --��������ַ
                handle    = 'asm.cliscript.handlelog';    --�첽���ݴ���ģ��
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

--����ҵ��ģ��
require('app.asm');

--�������ݿ������߳�
hexin.thread.start_threads('app.dbheartbeat', 1, {});

hexin.app.run(setting);
