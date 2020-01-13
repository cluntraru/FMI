data Point = P Integer Integer deriving Show

data Geom = Geom [Point] deriving Show

pointA :: Point -> Integer
pointA (P a _) = a

pointB :: Point -> Integer
pointB (P _ b) = b

geomList :: Geom -> [Point]
geomList (Geom l) = l

vPozitive :: Geom -> Geom
vPozitive geom 
    | null (geomList geom) = Geom []
    | (pointA h > 0 && pointB h > 0) = Geom (h : geomList geomTail)
    | otherwise = geomTail
    where
        h = head (geomList geom)
        t = tail (geomList geom)
        geomTail = vPozitive (Geom t)

pointEq :: Point -> Point -> Bool
pointEq pnt pnt2 = pointA pnt == pointA pnt2 && pointB pnt == pointB pnt2

pointListEq :: [Point] -> [Point] -> Bool
pointListEq pntL pntL2
    | null pntL && null pntL2 = True
    | null pntL && not (null pntL2) = False
    | not (null pntL2) && null pntL = False
    | otherwise = pointEq h1 h2 && pointListEq t1 t2
    where
        h1 = head pntL
        h2 = head pntL2
        t1 = tail pntL
        t2 = tail pntL2

geomEq :: Geom -> Geom -> Bool
geomEq geom geom2 = pointListEq (geomList geom) (geomList geom2)

distPoint :: Point -> Point -> Float
distPoint pnt1 pnt2 = sqrt (fromIntegral ((pointA pnt1 - pointA pnt2) ^ 2 + (pointB pnt1 - pointB pnt2) ^ 2))

distList :: Geom -> Geom -> [Float]
distList geom geom'
    | null l || null l' = []
    | otherwise = (distPoint h h') : distList geomTail geomTail'
    where
        l = geomList geom
        l' = geomList geom'
        h = head l
        h' = head l'
        geomTail = Geom (tail l)
        geomTail' = Geom (tail l')

sumaDist :: Geom -> Geom -> Float
sumaDist geom geom' = do
    if length (geomList geom) /= length (geomList geom') then
        error "numar de varfuri diferit!"
    else
        foldr (+) 0 (distList geom geom')


class GeomList a where
    toListG :: a -> [(Integer, Integer)]
    fromListG :: [(Integer, Integer)] -> a

instance GeomList Geom where
    toListG geom
        | null l = []
        | otherwise = (pointA h, pointB h) : lTail
        where
            l = geomList geom
            h = head l
            lTail = toListG (Geom (tail l))

    fromListG l
        | null l = Geom []
        | otherwise = Geom ((P (fst h) (snd h)) : geomList (fromListG t))
        where
            h = head l
            t = tail l
