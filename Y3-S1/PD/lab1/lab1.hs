import Data.List

myInt = 5555555555555555555555555555555555555555555555555555555555555555555555555555555555555

double :: Integer -> Integer
double x = x+x

triple :: Integer -> Integer
triple x = x + x + x


--maxim :: Integer -> Integer -> Integer
maxim x y =
    if (x > y)
        then x
    else y

max3 x y z =
    let u = maxim x y
    in (maxim  u z)

maxim4 x y z w =
    if (x >= y && x >= z && x >= w)
        then x
    else if (y >= x && y >= z && y >= w)
        then y
    else if (z >= x && z >= y && z >= w)
        then z
    else w

data Alegere =
    Piatra | Foarfeca | Hartie
    deriving(Eq, Show)

data Rezultat =
    Victorie | Infrangere | Egalitate
    deriving (Eq, Show)

partida :: Alegere -> Alegere -> Rezultat
partida p1 p2 =
    if (p1 == Piatra) then
        if (p2 == Piatra)
            then Egalitate
        else if (p2 == Foarfeca)
            then Victorie
        else Infrangere
    else if (p1 == Foarfeca) then
        if (p2 == Piatra)
            then Infrangere
        else if (p2 == Foarfeca)
            then Egalitate
        else Victorie
    else
        if (p2 == Piatra)
            then Victorie
        else if (p2 == Foarfeca)
            then Infrangere
        else Egalitate

