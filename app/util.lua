--************************浙江同花顺网络信息股份有限公司****************************
--				                资管系统 V2.0.0
-- 应用程序需要的一些公关函数
--
-- 创建时间: 2013/6/26
-- 作者:     王建 wangjian@myhexin.com
--

--Param包装对象
local HexinObj = {
	__index=function(t, k)		
		local obj = rawget(t, 'obj');
		local mt  = getmetatable(obj);
		if mt and mt[k] then
			return function(self, ...)									
				local obj = self.obj;
				return obj[k](obj, ...);
			end
		else
			return obj:getdata(k);
		end

		return nil;
	end;
	__newindex = function(t, k, v)
		local obj = rawget(t, 'obj');
		obj:setdata(k, v);
	end;
};

function HexinObj:new (obj)
	local o = {};	
	o.obj = obj;	
	setmetatable(o, self)
	return o
end

function WrapperHexinPacket(p)
	return HexinObj:new(p);
end