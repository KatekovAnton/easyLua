function Class(name, parent)
local smt, gmt = setmetatable, getmetatable
local parent = parent
local mt, cl = {}, {}
mt.__index = type(parent) == 'table' and parent or parent and error('Class inheritance error: table expected got '..type(parent), 2) or nil
mt.__call = function(self, ...) return self.init and self.init(self, ...) or {} end  -- average call method
cl.__name = name or ('class id: %8d'):format(math.random(99999999))                  -- name of class for getting
cl.__index = cl
cl.Inst = function(t)  return smt(t, cl) end
cl.Super = mt.__index
cl.Type = function(self, obj) return type(obj) == 'table' and gmt(obj) == gmt(self) or self.__name end
cl.IsObjectOf = function(self, class) return rawequal(class, gmt(self)) end
return smt(cl, mt)
end
