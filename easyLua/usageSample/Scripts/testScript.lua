
require('Utils/base')
require('Utils/class')



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
