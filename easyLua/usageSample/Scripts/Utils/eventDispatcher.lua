
require('Utils/base')
require('Utils/class')



-------------------------------------------------------------------------------------------------
-- API constants
-------------------------------------------------------------------------------------------------

EVENT_TYPE_UNIT   = 1
EVENT_TYPE_GAME   = 2



-------------------------------------------------------------------------------------------------
-- EventListener is base class for listening events
-- Override EventListener:onEvent()
-- house is some external data context
-------------------------------------------------------------------------------------------------
EventListener = Class()
function EventListener:init()
    local o = {}
    return self.Inst(o)
end



function EventListener:onEvent()

end



-------------------------------------------------------------------------------------------------
-- EventDispatcher is container of listeners
-- every listener should confirm to EventListener class
-------------------------------------------------------------------------------------------------
EventDispatcher = Class()
function EventDispatcher:init()
    local o = {}
    o.listeners = {}
    return self.Inst(o)
end



function EventDispatcher:addListener(listener)
    self.listeners[listener] = true
end



function EventDispatcher:removeListener(listener)
    self.listeners[listener] = nil
end



function EventDispatcher:onEvent(house)
    for listener, _ in pairs(self.listeners) do
        listener:onEvent(house)
    end
end



-------------------------------------------------------------------------------------------------
-- Global EventDispatcher
-------------------------------------------------------------------------------------------------
gloabalDispatcher = EventDispatcher()



function onEvent(house)
    gloabalDispatcher:onEvent(house)
end



--[[Применение типа:
foo = Class()
function foo:init(x, y)
  local o = {}
  o.x, o.y = x, y
  return self.Inst(o)
end

function foo:foobar(z)
  self.x, self.y = self.x + z, self.y - z
end

bar = Class('bar', foo) -- наследование

function bar:init(x, y, w, h)
  local o = self.Super(x, y)
   -- доступ к батьке батьки - self.Super.Super
  o.w, o.h = w, h
  return self.Inst(o)
end

function bar:bar(z)
  self.x = self.x + self.h - z
end


obj = foo(10, 20)
obj:foobar(2)

obj2 = bar(10, 20, 30, 40)
obj2:bar(12)
obj2:foobar(4) -- наследованный метод

А родительские методы вот так: 
self.Super.method(self, ...), иначе двоеточием в функцию перешлётся Super что не есть хорошо.]]--





