

print = function(...)
    printResult = ""
    for _,v in ipairs({...}) do
        printResult = printResult .. tostring(v) .. "\t" -- doesn't work with v = nil - returns empty string
    end
    context:logtext(printResult);
end

function dump(o)
    if type(o) == 'table' then
        local s = '{ '
        for k,v in pairs(o) do
            if type(k) ~= 'number' then k = '"'.. tostring(k) ..'"' end
            s = s .. '['..k..'] = ' .. dump(v) .. ','
        end
        return s .. '} '
    else
        return tostring(o)
    end
end

function tableLength(T)
    local count = 0
    for _ in pairs(T) do count = count + 1 end
    return count
end
