
require('Utils/base')
require('Utils/class')

function dump(o)
if type(o) == 'table' then
local s = '{ '
for k,v in pairs(o) do
if type(k) ~= 'number' then k = '"'..k..'"' end
s = s .. '['..k..'] = ' .. dump(v) .. ','
end
return s .. '} '
else
return tostring(o)
end
end

perms =
{

}

globalData =
{

}

function saveGlobalData()

    globalData['value1'] = 'text1'
    globalData['value2'] = 'text2'
    globalData['value3'] = 'Well, that was pretty rough but I figured it out finally. Turns out that when you call "require" LUA accesses the global "package.loaders" table, which contains a list of functions which searches for and loads your particular lua file.'
    print("globalData:", dump(globalData))

end

function loadGlobalData(perms)

    table.insert(globalData, perms['value1'])
    table.insert(globalData, perms['value2'])
    table.insert(globalData, perms['value3'])
    print("globalData:", dump(globalData))

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

function showData()
    print("data:", dump(data))
end
