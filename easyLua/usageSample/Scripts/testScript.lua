
require('Utils/base')
require('Utils/class')
require('Utils/eventDispatcher')
require('Quests/questLogic')
require('Quests/questExtensions')



perms = {}
globalData = {}

function prepareSaveGlobalData()
    print('prepareSaveGlobalData')
    perms[_ENV] = '_ENV'
end

function prepareLoadGlobalData()
    print('prepareLoadGlobalData')
    perms['_ENV'] = _ENV
end



function saveGlobalData()
    globalData['value1'] = 'text1'
    globalData['value2'] = 'text2'
    globalData['value3'] = 'Well, lets test saving a string variable.'
    
    gloabalQuestManager:saveQuests(globalData)

    print("saved data:", dump(globalData))
end



function loadGlobalData(permsE)
    print("loaded data:", dump(permsE))

    globalData['value1'] = permsE['value1']
    globalData['value2'] = permsE['value2']
    globalData['value3'] = permsE['value3']
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
    gloabalQuestManager:setHouse(house)

    -- Quest1 body
    function quest1Body(quest, questManager)
        -- Check house
        -- local house = questManager.house
        -- local roomersCount = house:getRoomersCount()
        -- print('AAAAAA = ' .. tostring(roomersCount))

        print('Fredd and Sarah are waiting for 3rd roomer!')
        local result = quest:waitForThirdRoomer(questManager)
        print('Ok third person is here! lets party!')
        quest:finish(QUEST_STATE_SUCCESS)
    end

    -- Quest1 dispatching
    local quest1 = Quest(quest1Body)
    gloabalQuestManager:addQuest(quest1)

    print('Initialization done')
end
