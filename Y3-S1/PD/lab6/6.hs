ioMain = do
    maxDepth <- readLn :: IO Integer
    print (maxDepth >>= ioPeople)

ioNum = do
    num <- readLn :: IO Integer
    return num

ioStr = do
    str <- getLine
    return str

ioPeople :: Integer -> IO ([String], Integer)
ioPeople depth
    | depth == 0 = ([], 0)
    | otherwise = 
        if varsta > maxAge then
            ([nume], varsta)
        else if varsta == maxAge then
            (nume : nameList, varsta)
        else
            (nameList, maxAge)
     where
        varsta = ioNum
        nume = ioStr
        l = ioPeople (depth - 1)
        nameList = fst l
        maxAge = snd l

