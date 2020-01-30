data Piece = One   -- primul jucător
            | Two   -- al doilea jucător
            | Empty -- căsuță liberă pe tablă
   deriving (Show, Eq)

data Table = Table [Piece] [Piece] [Piece]
   deriving (Show,Eq)

table1 :: Table
table1 = Table [Empty, One, Two, One, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Two, One, Empty, Empty, One, Two, One]

table2 :: Table
table2 = Table [Two, One, Two, One, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Two, One, Empty, Empty, One, Two, One]

table3 :: Table
table3 = Table [Empty, One, Empty, Empty, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Empty, One, Empty, Empty, One, Two, One]

table4 :: Table
table4 = Table [Empty,Empty,Two,One,Empty,Empty,Two,One]
               [Two,One,One,Two,One,Two,One,Two]
               [Two,Two,One,Empty,Empty,One,Two,One]


countPiece :: Piece -> [Piece] -> Int
countPiece cntP l
    | null l = 0
    | otherwise = do
        if cntP == h then
            tailCnt + 1
        else
            tailCnt
    where
        h = head l
        t = tail l
        tailCnt = countPiece cntP t

validBoard :: Table -> Bool
validBoard (Table l1 l2 l3) = length l1 == 8 && length l2 == 8 && length l3 == 8

validPlacement :: Table -> Bool
validPlacement (Table l1 l2 l3) = 
    (countPiece One l1 + countPiece One l2 + countPiece One l3) <= 9 &&
    (countPiece Two l1 + countPiece Two l2 + countPiece Two l3) <= 9

validTable :: Table -> Bool
validTable tab = validBoard tab && validPlacement tab


test11 = validTable table1 == True
test12 = validTable table2 == False
test13 = validTable table3 == True


data Position = P (Int,Int)

instance Show Position where
  show (P (i,j)) = "careul " ++ show i ++ " pozitia " ++ show j

-- Avem nevoie de == pentru a face Eq
instance Eq Position where
  (P (l1, o1)) == (P (l2, o2)) = l1 == l2 && o1 == o2

-- Ne da pozitia anterioara pe acelasi careu
prevPos :: Position -> Position
prevPos (P (lin, offset))
    | offset == 0 = P (lin, 7)
    | otherwise = P (lin, offset - 1)

-- pozitia urmatoare pe acelasi care
nextPos :: Position -> Position
nextPos (P (lin, offset))
    | offset == 7 = P (lin, 0)
    | otherwise = P (lin, offset + 1)

-- Pozitiile de pe alte careuri la care avem acces
transferPos :: Position -> [Position]
transferPos (P (lin, offset))
    | elem offset corners = do []
    | lin == 1 = do [P (2, offset)]
    | lin == 2 = do [P (1, offset), P (3, offset)]
    | lin == 3 = do [P (2, offset)]
    where
        corners = [0, 2, 4, 6]

-- toate pozitiile vecine
ngbPos :: Position -> [Position]
ngbPos p = [prevPos p] ++ [nextPos p] ++ transferPos p

-- Verifica daca 2 pozitii sunt vecine
connectedPos :: Position -> Position -> Bool
connectedPos p1 p2 = elem p2 (ngbPos p1)

-- Valoarea elementului pe pozitia pos
tabValue :: Table -> Position -> Piece
tabValue (Table l1 l2 l3) (P (lin, offset))
    | lin == 1 = l1 !! offset
    | lin == 2 = l2 !! offset
    | lin == 3 = l3 !! offset

getSquare :: Table -> Int -> [Piece]
getSquare (Table l1 l2 l3) idx
    | idx == 1 = l1
    | idx == 2 = l2
    | idx == 3 = l3

-- Inlocuieste un element dintr-o lista
replace :: [Piece] -> Int -> Piece -> [Piece]
replace src idx piece = (take idx src) ++ [piece] ++
    (reverse (take ((length src) - idx - 1) (reverse src)))

move :: Table -> Position -> Position -> Maybe Table
move (Table l1 l2 l3) (P (lin1, off1)) (P (lin2, off2))
    | connectedPos p1 p2 == False = Nothing
    | tabValue tab p1 == Empty = Nothing
    | not (tabValue tab p2 == Empty) = Nothing
    | lin1 == 1 && lin2 == 1 = Just (Table doubleNewSrc l2 l3)
    | lin1 == 1 && lin2 == 2 = Just (Table newSrc newDst l3)
    | lin1 == 1 && lin2 == 3 = Just (Table newSrc l2 newDst)
    | lin1 == 2 && lin2 == 1 = Just (Table newDst newSrc l3)
    | lin1 == 2 && lin2 == 2 = Just (Table l1 doubleNewSrc l3)
    | lin1 == 2 && lin2 == 3 = Just (Table l1 newSrc newDst)
    | lin1 == 3 && lin2 == 1 = Just (Table newDst l2 newSrc)
    | lin1 == 3 && lin2 == 2 = Just (Table l1 newDst newSrc)
    | lin1 == 3 && lin2 == 3 = Just (Table l1 l2 doubleNewSrc)
    where
        tab = Table l1 l2 l3
        p1 = P (lin1, off1)
        p2 = P (lin2, off2)
        srcSquare = getSquare tab lin1
        destSquare = getSquare tab lin2
        newSrc = replace srcSquare off1 Empty
        newDst = replace destSquare off2 (tabValue tab p1)
        -- folosit doar daca cele 2 poz sunt pe acelasi careu
        -- inlocuieste pozitia 2 din careul 1 deja prelucrat
        doubleNewSrc = replace newSrc off2 (tabValue tab p1)


test21 = move table2 (P (1,2)) (P(2,2)) == Nothing
test22 = move table1 (P (1,2)) (P(2,2)) == Nothing
test23 = move table1 (P (1,1)) (P(2,1))
       == Just (Table [Empty,Empty,Two,One,Empty,Empty,Two,One]
                      [Two,One,One,Two,One,Two,One,Two]
                      [Two,Two,One,Empty,Empty,One,Two,One])
                      -- table4
test24 = move table1 (P (3,1)) (P(2,1))
        == Just (Table [Empty,One,Two,One,Empty,Empty,Two,One]
                       [Two,Two,One,Two,One,Two,One,Two]
                       [Two,Empty,One,Empty,Empty,One,Two,One])



data EitherWriter a = EW {getvalue :: Either String (a, String)}

-- Schita exercitiul 3

--instance Monad EitherWriter where
--    a >>= a' = undefined
--    return = Right


playGame :: Table -> [(Position, Position)] -> [(Position, Position)] -> EitherWriter Table
playGame = undefined

printGame :: EitherWriter Table -> IO ()
printGame ewt = do
    let t = getvalue ewt
    case t of
      Left v -> putStrLn v
      Right (t,v) -> putStrLn v

list1, list2 :: [(Position,Position)]
list1 = [(P(1,1),P(1,0)), (P(2,2),P(2,1)), (P(1,3),P(2,3)) ]
list2 = [(P(1,6),P(1,5)), (P(2,3),P(3,3)), (P(1,2),P(1,3)) ]

test41 = printGame $ playGame table1 list1 list2


{-
> test41
Jucatorul One a mutat din careul 1 pozitia 1 in  careul 1 pozitia 0
Jucatorul Two a mutat din careul 1 pozitia 6 in  careul 1 pozitia 5
Jucatorul One a mutat din careul 2 pozitia 2 in  careul 2 pozitia 1
Jucatorul Two a mutat din careul 2 pozitia 3 in  careul 3 pozitia 3
Jucatorul One a mutat din careul 1 pozitia 3 in  careul 2 pozitia 3
Jucatorul Two a mutat din careul 1 pozitia 2 in  careul 1 pozitia 3
Table finala este Table [One,Empty,Empty,Two,Empty,Two,Empty,One] [Two,One,Empty,One,One,Two,One,Two] [Two,Two,One,Two,Empty,One,Two,One]
-}
list3, list4 :: [(Position,Position)]
list3 = [(P(1,1),P(1,0)), (P(2,2),P(2,4)), (P(1,3),P(2,3)) ]
list4 = [(P(1,6),P(1,5)), (P(2,3),P(3,3)), (P(1,2),P(1,3)) ]

test42 = printGame $ playGame table1 list3 list4
-- test42
-- Jucatorul One nu poate muta din careul 2 pozitia 2 in  careul 2 pozitia 4
