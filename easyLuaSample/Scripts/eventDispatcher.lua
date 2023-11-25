
require('Utils/base')
require('Utils/class')



-------------------------------------------------------------------------------------------------
-- API constants
-------------------------------------------------------------------------------------------------

EVENT_TYPE_UNIT   = 1
EVENT_TYPE_GAME   = 2



EventListener = Class()
function EventListener:init()
    print('rrrrr')
    local o = {}
    return self.Inst(o)
end


function EventListener:onEvent()
    return nil
end


function EventListener:onAfterEvent(conditionResult)
    return nil
end



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


function EventDispatcher:onEvent()
    listenersNew = {}
    listenersToCall = {}

    -- iterate through listerens
    for listener, _ in pairs(self.listeners) do
        local conditionResult = listener:onEvent()
        if conditionResult == nil then
            listenersNew[listener] = true
        else
            listenersToCall[listener] = conditionResult
        end
    end
    self.listeners = listenersNew

    -- why we should iterate through another array?
    -- because recursion will cause re-fill of self.listeners
    for listener, parameter in pairs(listenersToCall) do
        local conditionResult = listener:onAfterEvent(parameter)
    end
end



gloabalDispatcher = EventDispatcher()



function onEvent()
    gloabalDispatcher:onEvent()
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





