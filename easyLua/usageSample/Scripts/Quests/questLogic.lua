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



Quest = Class('Quest', EventListener)
function Quest:init(body)
    local o = {}
    o.tasks = {}
    o.condition = nil
    o.body = body
    o.state = QUEST_STATE_AWAIT
    o.co = coroutine.create(o.body)
    return self.Inst(o)
end



function Quest:addTask(task)
    self.tasks[task] = true
end



function Quest:run(house)
    self.state = QUEST_STATE_CURRENT
    coroutine.resume(self.co, self, house)
end



function Quest:finish()
    self.state = QUEST_STATE_SUCCESS
end



function Quest:fail()
    self.state = QUEST_STATE_FAILED
end



-- condition should be a function that 
-- returns nil if condition failed and quest state does't change
-- returns not nil if quest agenda has been done
-- this object will be passed back to quest function
function Quest:interrupt(condition, house)
    local currentConditionResult = condition(house)
    if currentConditionResult ~= nil then
        return currentConditionResult
    end
    self.condition = condition
    gloabalDispatcher:addListener(self)
    local conditionResult = coroutine.yield()
    return conditionResult
end



function Quest:onEvent(house)
    conditionResult = self.condition(house)
    return conditionResult
end



function Quest:onAfterEvent(conditionResult)
    if conditionResult ~= nil then 
         coroutine.resume(self.co, conditionResult)
    end
end



-------------------------------------------------------------------------------------------------
-- Quest manager
-------------------------------------------------------------------------------------------------

QuestManager = Class()
function QuestManager:init()
    local o = {}
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



gloabalQuestManager = QuestManager()



function saveQuests(perms)
    perms['runningQuests'] = gloabalQuestManager.runningQuests
    perms['finishedQuests'] = gloabalQuestManager.finishedQuests
end

function restoreQuests(perms)

end
