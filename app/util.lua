--************************�㽭ͬ��˳������Ϣ�ɷ����޹�˾****************************
--				                �ʹ�ϵͳ V2.0.0
-- Ӧ�ó�����Ҫ��һЩ���غ���
--
-- ����ʱ��: 2013/6/26
-- ����:     ���� wangjian@myhexin.com
--

--Param��װ����
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