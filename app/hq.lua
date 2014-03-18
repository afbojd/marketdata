--************************浙江同花顺网络信息股份有限公司****************************
--				                资管系统 V2.0.0
-- 资管行情接收程序
--
-- 创建时间: 2013/7/8
-- 作者:     王建 wangjian@myhexin.com
-- 任意引用模块使用 app.hq.GetHQ(code)即可获取行情信息

module('app.hq', package.seeall);
require('hx');
require('hexin.base');

--连接的行情发送地址，地址和端口是和委托主站从行情发送取数据的接口相同
--的,地址格式是ip:port
local send_addr = '10.0.2.180:8610';


--------------------以下是公共处理部分，正常情况下勿修改-----------------------
local hq, bexsist = hexin.hx.receiver.create('zghq');
--新生成的对象才做连接操作
if not bexsist then
	hq:init_send_addr(send_addr);
end


--------------------------导出函数---------------------------------------------

--取指定代码的行情信息
--code 行情代码
--return 如果代码存在，返回相关信息table,否则返回nil
--数据的值域是 zqmc-证券名称 zqdm-带分类的证券代码 time-行情时间 zrsp-昨收
--jrkp-今日开盘 zxj-最新价 mrsl1-mrsl5 买入数量1-5 mrjw1-mrjw5 买入价位1-5
--mcsl1-5 卖出数量1-5 mcjw1-5 卖出价位1-5 ztjg-涨停价格 dtjg-跌停价格
function GetHQ(code)
	return hq:get_hqdata(code);
end

function GetAllCode()
    local list = hq:get_all_code();
    return list;
end
