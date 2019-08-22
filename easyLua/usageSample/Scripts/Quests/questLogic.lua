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
    o.body = body
    o.state = QUEST_STATE_AWAIT
    o.co = coroutine.create(o.body)
    return self.Inst(o)
end



function Quest:run(questManager)
    self.state = QUEST_STATE_CURRENT
    coroutine.resume(self.co, self, questManager)
end



function Quest:continue(questManager, interruptionResult)
    coroutine.resume(self.co, self, questManager, interruptionResult)
end



function Quest:finish()
    self.state = QUEST_STATE_SUCCESS
end



function Quest:fail()
    self.state = QUEST_STATE_FAILED
end



function Quest:onEvent(house)
    return self.condition(house)
end



-- condition should be a function that
-- returns nil if condition failed and quest state does't change
-- returns not nil if quest agenda has been done
-- this object will be passed back to quest function
function Quest:interrupt(condition)
    local currentConditionResult = condition(house)
    if currentConditionResult ~= nil then
        return currentConditionResult
    end
    self.condition = condition
    gloabalDispatcher:addListener(self)
    local conditionResult = coroutine.yield()
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



function QuestManager:getFinishedQuestsCount()
    table.getn(self.finishedQuests)
end



function QuestManager:addQuest(quest)
    self.runningQuests[quest] = true
end



function QuestManager:finishQuest(quest)
    self.runningQuests[quest] = nil
    self.finishedQuests[quest] = true
end



function QuestManager:onEvent(house)
    local runningQuestsNew = {}
    local runningQuestsNewToCall = {}

    -- iterate through listerens
    for quest, _ in pairs(self.runningQuests) do
        local conditionResult = quest:onEvent(house)
        if conditionResult == nil then
            runningQuestsNew[listener] = true
        else
            runningQuestsNewToCall[listener] = conditionResult
        end
    end
    self.runningQuests = runningQuestsNew

    -- why we should iterate through another array?
    -- because recursion will cause re-fill of self.listeners
    for quest, conditionResult in pairs(runningQuestsNewToCall) do
        quest:continue(self, conditionResult)
    end
end



function QuestManager:saveQuests(perms)
    perms['runningQuests'] = self.runningQuests
    perms['finishedQuests'] = self.finishedQuests
end

function QuestManager:loadQuests(perms)

end



gloabalQuestManager = QuestManager()
gloabalDispatcher:addListener(gloabalQuestManager)
