

print = function(...)
    printResult = ""
    for _,v in ipairs({...}) do
        printResult = printResult .. tostring(v) .. "\t" -- doesn't work with v = nil - returns empty string
    end
    context:logtext(printResult);
end
