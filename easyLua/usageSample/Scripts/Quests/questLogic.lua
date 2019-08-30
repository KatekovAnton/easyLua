--[[
 questLogic.lua
 --]]

require('Utils/base')
require('Utils/class')
require('Utils/eventDispatcher')



-------------------------------------------------------------------------------------------------
-- Quest
-------------------------------------------------------------------------------------------------

QUEST_STATE_AWAIT     = 0
QUEST_STATE_CURRENT   = 1
QUEST_STATE_SUCCESS   = 2
QUEST_STATE_FAILED    = 3



Quest = Class()
function Quest:init(body)
    local o = {}
    o.condition = nil
    o.state = QUEST_STATE_AWAIT
    o.co = coroutine.create(body)
    return self.Inst(o)
end



function Quest:run(questManager)
    self.state = QUEST_STATE_CURRENT
    coroutine.resume(self.co, self, questManager)
end



function Quest:continue(interruptionResult)
    self.condition = nil
    coroutine.resume(self.co, interruptionResult)
end



function Quest:finish(state)
    print('Quest:finish')
    self.state = state
    --self.co = nil
    self.condition = nil
end



function Quest:onEvent(questManager)
    return self.condition(questManager)
end



-- condition should be a function that
-- returns nil if condition failed and quest state does't change
-- returns not nil if quest agenda has been done
-- this object will be passed back to quest function
function Quest:interrupt(condition, questManager)
    local currentConditionResult = condition(questManager)
    if currentConditionResult ~= nil then
        return currentConditionResult
    end
    self.condition = condition
    local conditionResult = coroutine.yield()
    self.condition = nil
    return conditionResult
end



-------------------------------------------------------------------------------------------------
-- Quest manager
-------------------------------------------------------------------------------------------------

QuestManager = Class('QuestManager', EventListener)
function QuestManager:init()
    local o = self.Super()
    o.runningQuests = {}
    o.finishedQuests = {}
    return self.Inst(o)
end



function QuestManager:getQuestsCount()
    table.getn(self.runningQuests)
end



function QuestManager:setHouse(house)
    self.house = house
end



function QuestManager:getFinishedQuestsCount()
    table.getn(self.finishedQuests)
end



function QuestManager:addQuest(quest)
    self.runningQuests[quest] = true
    quest:run(self)
end



function QuestManager:onEvent(house)

    local runningQuestsNewToCall = {}

    -- iterate through quests
    for quest, _ in pairs(self.runningQuests) do
        local conditionResult = quest:onEvent(self)
        if conditionResult ~= nil then
            runningQuestsNewToCall[quest] = conditionResult
        end
    end

    -- why we should iterate through another array?
    -- because recursion will cause re-fill of self.listeners
    for quest, conditionResult in pairs(runningQuestsNewToCall) do
        quest:continue(self, conditionResult)
        if quest.state ~= QUEST_STATE_CURRENT then
            print('QuestManager: found finished quest = ' .. tostring(quest))
            self.runningQuests[quest] = nil
            self.finishedQuests[quest] = true
        end
    end
    print('QuestManager: count of quests running ' .. tostring(tableLength(self.runningQuests)) .. '; finished ' .. tostring(tableLength(self.finishedQuests)))
end



function QuestManager:saveQuests(perms)
    --perms['runningQuests'] = self.runningQuests
    --perms['finishedQuests'] = self.finishedQuests
    local fqd = {}
    for quest, _ in pairs(self.finishedQuests) do
        local q = {}
        print(tostring(quest.co))
        q["q"] = quest.co
        fqd[q] = true
    end
    perms['finishedQuests'] = fqd
end

function QuestManager:loadQuests(perms)

end



gloabalQuestManager = QuestManager()
gloabalDispatcher:addListener(gloabalQuestManager)
