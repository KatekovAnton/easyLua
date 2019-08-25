--[[
questExtensions.lua
--]]

require('Utils/base')
require('Utils/class')
require('Quests/questLogic')



function Quest:waitForThirdRoomer(questManager)
    return self:interrupt(function (questManager)
        local house = questManager.house
        local roomersCount = house:getRoomersCount()
        if roomersCount < 3 then
            return nil
        end
        return 'ok'
    end, questManager)
end


function Quest:waitForFourthRoomer(questManager)
    return self:interrupt(function (questManager)
        local house = questManager.house
        local roomersCount = house:getRoomersCount()
        if roomersCount < 4 then
            return nil
        end
        return 'ok'
    end, questManager)
end
