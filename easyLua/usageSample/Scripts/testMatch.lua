--[[
testMatch.lua
This is Test mission script
--]]

if RemoteDebugEnabled then
  require('RemoteDebug/mobdebug').start()
end

require('customMissionSettings')
require('customMissionLogic')



local testMatchSettings = CustomMatchSettings()
testMatchSettings.mapFileName = 'Desert_4.wrl'
testMatchSettings.mapName = 'Incandescent machines'
testMatchSettings:addPlayer(GameMatchPlayerInfo(1, 5, 'Player 1', Color(237, 237, 54, 255), false, '', 0))
testMatchSettings:addPlayer(GameMatchPlayerInfo(2, 1, 'Player 2', Color(25, 116, 210, 255), false, '', 1))
testMatchSettings:addPlayer(GameMatchPlayerInfo(3, 0, 'Player 3', Color(40, 255, 58, 255), false, '', 2))
local gameSettings =
{
    game_name = 'Test game3',
    uniset_name = "Original",
    start_gold = 301,
    ['amoun of material'] = {
        ['raw']  = 2,               -- values:0,1,2
        ['fuel'] = 1,               -- values:0,1,2
        ['gold'] = 1,               -- values:0,1,2
    },
    ['total count of resource placements'] = 280, -- ~500 is max
    ['laying ability'] = true,
    ['enable gasoline'] = true,
}
testMatchSettings:applySettings(gameSettings) 



-- Setup API to this instance
TheMatchSettings = testMatchSettings



local testMatchLogic = CustomMissionLogic()



local unitList1 = {
  {75, 30, "airtrans"},
  {84, 30, "surveyor"},
  {83, 27, "radar"},
  {83, 28, "matstore"},
  {81, 27, "powerpl"},
  {80, 33, "shipyard"},
  {80, 35, "dock"},
  {84, 29, "engineer", 3, 40},
  {81, 29, "engineer", 3, 40},
  {82, 29, "constructor", 3, 60},
  {85, 29, "constructor", 3, 60},
  { unitType = "radar",
    xy = {
      {86, 38},
      {74, 41},
      {67, 31}
    }
  },
  { unitType = "misturret", 
    xy = {
      {84, 39},
      {88, 39},
      {72, 42},
      {76, 42},
      {81, 26},
      {85, 26},
      {65, 30},
      {69, 30},
    }
  },
  { unitType = "zenit",
    xy = {
      {85, 39},
      {87, 39},
      {73, 42},
      {75, 42},
      {82, 26},
      {84, 26},
      {66, 30},
      {68, 30}
    }
  },
  { unitType = "arturret",
    xy = {
      {74, 42},
      {86, 39},
      {83, 26},
      {67, 30}
    }
  },
  {72, 33, "shipyard"},
  {72, 35, "dock"},
  { unitType = "mining",
    action = 2,
    xy = {
      {84, 27},
      {69, 34},
      {69, 36}
    }
  },
  
  {67, 33, "lightplant"},
  {67, 36, "hvplant"},
  {70, 38, "conn"},
  {70, 39, "research"},
  {72, 39, "gref"},
  {75, 39, "plat"},
  {75, 40, "plat"},
  {74, 39, "habitat"},
  {67, 38, "conn"},
  {67, 32, "conn"},
  {67, 39, "store"},
  {70, 29, "corvette"},
  {71, 29, "corvette"},
  {71, 30, "gunboat"},
  {76, 29, "corvette"},
  {77, 29, "corvette"},
  {76, 30, "gunboat"},
  {77, 44, "corvette"},
  {78, 44, "corvette"},
  {78, 42, "corvette"},
  {78, 43, "gunboat"},
  {83, 42, "corvette"},
  {84, 42, "corvette"},
  {83, 41, "gunboat"},
  {53, 33, "miner", 3, 20},
  {77, 35, "gunboat"},
  {78, 35, "gunboat"},
  {79, 35, "gunboat"},
  {77, 36, "gunboat"},
  {79, 36, "gunboat"},
  {77, 37, "gunboat"},
  {79, 37, "gunboat"}
}
do
  local i = #unitList1
  local y = 32
  for x = 70, 82 do
    i = i + 1
    unitList1[i] = {x, y, "bridge"}
  end
  local x = 82
  for y = 33, 37 do
    i = i + 1
    unitList1[i] = {x, y, "bridge"}
  end
  y = 38
  for x = 73, 83 do
    i = i + 1
    unitList1[i] = {x, y, "bridge"}
  end
  x = 80
  for y = 28, 32 do
    i = i + 1
    unitList1[i] = {x, y, "conn"}
  end
  y = 33
  for x = 69, 71 do
    i = i + 1
    unitList1[i] = {x, y, "conn"}
  end
  for x = 74, 79 do
    i = i + 1
    unitList1[i] = {x, y, "conn"}
  end
  y = 37
  for x = 71, 86 do
    i = i + 1
    unitList1[i] = {x, y, "conn"}
  end
end
do
end

local unitList2 = {
  {74, 56, "bomber"},
  {76, 56, "bomber"},
  {75, 54, "bomber"},
  {76, 54, "bomber"},
  {76, 70, "surveyor"},
  {77, 70, "surveyor"},
  
  {84 - 49, 27 + 64, "mining", 2},
  {37, 92, "surveyor"},
  {83 - 49, 28 + 64, "matstore"},
  {83 - 49, 27 + 64, "radar"},
  {81 - 49, 27 + 64, "powerpl"},
  
  {81 - 49, 27 + 63, "scout"},
  {81 - 48, 27 + 63, "scout"},
  {81 - 47, 27 + 63, "scout"},
  
  {35, 93, "conn"},
  {35, 94, "conn"},
  {35, 95, "lightplant"},
  {37, 95, "hvplant"},
  
  {37, 97, "engineer", 3, 40},
  {38, 97, "constructor", 3, 60},
  
  {78, 36, "sub"},
  {32, 88, "misturret"},
  {33, 88, "zenit"},
  {34, 88, "arturret"},
  {35, 88, "zenit"},
  {36, 88, "misturret"},
  
  {81 - 49, 27 + 62, "alnasgun"},
  {81 - 48, 27 + 62, "alnplane"},
  {81 - 47, 27 + 62, "alntank"},
  {49, 29, "engineer", 3, 40},
  {49, 30, "constructor", 3, 60},
  {49, 31, "scout"},
  {49, 32, "tank"},
  {53, 28, "conn"},
  {53, 34, "conn"}
}
do
  local i = #unitList2
  for x = 71, 74 do
    for y = 55, 57 do
      i = i + 1
      unitList2[i] = {x, y, "gunboat"}
    end
  end
end

local unitList3 = {
    {94, 96, "radar"},
    {90, 92, "lightplant"},
    {92, 92, "hvplant"},
    {94, 92, "powerpl"},
    {96, 92, "mining", 2},
    
    {91, 89, "alnasgun"},
    {92, 89, "alnasgun"},
    {93, 89, "alnasgun"},
    {94, 89, "alnasgun"},
    {91, 90, "alnplane"},
    {92, 90, "alnplane"},
    {93, 90, "alnplane"},
    {94, 90, "alnplane"},
    {91, 91, "alntank"},
    {92, 91, "alntank"},
    {93, 91, "alntank"},
    {94, 91, "alntank"},
        
    {92, 94, "engineer", 3, 40},
    {93, 94, "constructor", 3, 60},
}



testMatchLogic:addInitialUnitsForPlayer(unitList1, 1)
testMatchLogic:addInitialUnitsForPlayer(unitList2, 2)
testMatchLogic:addInitialUnitsForPlayer(unitList3, 3)



local data1 = {gold = 1000, cameraX = 83, cameraY = 30, cameraZoom = 1}
local data2 = {gold = 1000, cameraX = 84 - 49, cameraY = 27 + 64, cameraZoom = 1.5}
local data3 = {gold = 1000, cameraX = 94, cameraY = 92, cameraZoom = 1}



testMatchLogic:addInitialDataForPlayers(data1, 1)
testMatchLogic:addInitialDataForPlayers(data2, 2)
testMatchLogic:addInitialDataForPlayers(data3, 3)



function testMatchLogic:onMapLoaded(game, match)

    local map = match:getMap()
    map:placeInitialResources(86, 32)
    map:placeInitialResources(69, 34)
    map:placeInitialResources(69, 36)
    map:placeInitialResources(84, 27)
    map:placeInitialResources(35, 91)
    map:placeInitialResources(96, 92)
    map:placeInitialResources(84, 34)

end



function testMatchLogic:onMatchLoaded(game, match)

    local unit = match:playerAtIndex(1):createUnit(54, 34, 'tank')

    unit:placeUnitOnMap(false)
    unit:setDirection(6)

    match:playerAtIndex(1):createUnit(55, 33, 'infantry'):placeUnitOnMap(false)
    match:playerAtIndex(1):createUnit(56, 33, 'infantry'):placeUnitOnMap(false)
    match:playerAtIndex(1):createUnit(56, 32, 'pcan'):placeUnitOnMap(false)

    
    match:playerAtIndex(2):createUnit(53, 34, 'infil'):placeUnitOnMap(false)
    match:playerAtIndex(2):createUnit(52, 32, 'awac'):placeUnitOnMap(false)
    match:playerAtIndex(2):createUnit(76, 55, 'awac'):placeUnitOnMap(false)
    match:playerAtIndex(1):createUnit(54, 33, 'awac'):placeUnitOnMap(false)
    match:playerAtIndex(1):createUnit(84, 33, 'awac'):placeUnitOnMap(false)


    local map = match:getMap()
    local mapWidth = map:getWidth()
    local mapHeight = map:getHeight()
    print('test success. map w = ' .. tostring(mapWidth) .. ', map h = ' .. tostring(mapHeight))
    
end


-- Setup API to this instance
TheMatchLogic = testMatchLogic


-- Unit Tests
if not MAXTouch then
  print()
  print('------ Settings DEBUG ------')
  CustomMatchSettingsDEBUG()
  print('------ Logic DEBUG ------')
  CustomMatchLogicDEBUG()
end
