
require('Utils/base')
require('Utils/class')



function testSimpleFunction()

    print('lets see how our custom print works')

end

function testNativeObject(object)

    local size = object:getSize()
    print('data retrieved from c++ object: house size w = ' .. tostring(size.w) .. ', h = ' .. tostring(size.h))

end
