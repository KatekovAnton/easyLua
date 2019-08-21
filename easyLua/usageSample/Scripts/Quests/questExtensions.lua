--[[
questExtensions.lua
--]]

require('Utils/base')
require('Utils/class')
require('Quests/questLogic')



function Quest:waitForThirdRoomer(house)
    return self:interrupt(function (house)
        local roomersCount = house:getRoomersCount()
        print('Quest:waitForThirdRoomer Current roomers count ' .. tostring(roomersCount))
        if roomersCount < 3 then
            return nil
        end
        return 'ok'
    end, house)
end


function Quest:waitForFourthRoomer(house)
    return self:interrupt(function (house)
        local roomersCount = house:getRoomersCount()
        print('Quest:waitForFourthRoomer Current roomers count ' .. tostring(roomersCount))
        if roomersCount < 4 then
            return nil
        end
        return 'ok'
    end, house)
end
