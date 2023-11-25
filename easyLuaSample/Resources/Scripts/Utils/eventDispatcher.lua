--[[
eventDispatcher.lua
--]]

require('Utils/base')
require('Utils/class')



-------------------------------------------------------------------------------------------------
-- Event listener
-------------------------------------------------------------------------------------------------

EventListener = Class()
function EventListener:init()
    local o = {}
    return self.Inst(o)
end



function EventListener:onEvent()
    return nil
end



function EventListener:onAfterEvent(conditionResult)
    return nil
end



-------------------------------------------------------------------------------------------------
-- Event dispatcher
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
    listenersNew = {}
    listenersToCall = {}

    -- iterate through listerens
    for listener, _ in pairs(self.listeners) do
        local conditionResult = listener:onEvent(house)
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



function onEvent(house)
    gloabalDispatcher:onEvent(house)
end
