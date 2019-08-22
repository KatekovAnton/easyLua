
require('Utils/base')
require('Utils/class')
require('Utils/eventDispatcher')
require('Quests/questLogic')
require('Quests/questExtensions')



perms =
{

}

globalData =
{

}



function saveGlobalData()
    globalData['value1'] = 'text1'
    globalData['value2'] = 'text2'
    globalData['value3'] = 'Well, lets test saving a string variable.'
    gloabalQuestManager:saveQuests(globalData)

    print("saved data:", dump(globalData))
end



function loadGlobalData(perms)
    print("loaded data:", dump(perms))

    globalData['value1'] = perms['value1']
    globalData['value2'] = perms['value2']
    globalData['value3'] = perms['value3']
end



function testSimpleFunction()
    print('lets see how our custom print works')
end



function testNativeObject(house)
    local size = house:getSize()
    print('data retrieved from c++ house:')
    print('size w = ' .. tostring(size.w) .. ', h = ' .. tostring(size.h))

    local roomersCount = house:getRoomersCount()
    print('roomers count = ' .. tostring(roomersCount))
    for i = 0, roomersCount - 1, 1 do
        local roomer = house:getRoomer(i)
        print('roomer ' .. tostring(i) .. ' name: ' .. roomer:getName())
    end
end



function initialiseQuest(house)
    print('Initialization started!')

    -- Quest1 body
    function quest1Body(quest, questManager)
        print('Fredd and Sarah are waiting for 3rd roomer!')
        local quest, questManager, result = quest:waitForThirdRoomer()
        print('Ok third person is here! lets party!')
    end

    -- Quest1 dispatching
    local quest1 = Quest(quest1Body)
    quest1:run(house)

    print('Initialization done')
end
