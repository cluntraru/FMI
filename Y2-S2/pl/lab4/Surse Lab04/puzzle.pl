right_of(X, Y) :- X =:= Y + 1.
left_of(X, Y) :- Y =:= X + 1.
consec(X, Y) :- right_of(X, Y); left_of(X, Y).

solutie(Strada,PosesorZebra) :-
    Strada = [
        casa(1,_,_,_,_,_),
        casa(2,_,_,_,_,_),
        casa(3,_,_,_,_,_),
        casa(4,_,_,_,_,_),
        casa(5,_,_,_,_,_)
    ],

    % casa(Numar,Nationalitate,Culoare,AnimalCompanie,Bautura,Tigari)
    member(casa(_, englez,    rosie,  _,     _,     _), Strada),
    member(casa(_, spaniol,   _,      caine, _,     _), Strada),
    member(casa(_, _,         verde,  _,     cafea, _), Strada),
    member(casa(_, ucrainean, _,      _,     ceai,  _), Strada),

    member(casa(NumCasaVerde, _, verde, _, _, _), Strada),
    member(casa(NumCasaBej,   _, bej,   _, _, _), Strada),
    right_of(NumCasaVerde, NumCasaBej),

    member(casa(_, _,         _,      melci, _,     olgGold), Strada),
    member(casa(_, _,         galben, _,     _,     kools), Strada),
    member(casa(3, _,         _,      _,     lapte, _), Strada),

    member(casa(NumCasaChesterfield, _, _, _, _, chesterfield), Strada),
    member(casa(NumCasaVulpe, _, _, vulpe, _, _), Strada),
    consec(NumCasaChesterfield, NumCasaVulpe),

    member(casa(NumCasaKools, _, _, _, _, kools), Strada),
    member(casa(NumCasaCal, _, _, cal, _, _), Strada),
    consec(NumCasaKools, NumCasaCal),

    member(casa(_, _, _, _, sucPortocale, luckyStrike), Strada),
    member(casa(_, japonez, _, _, _, parliament), Strada),

    member(casa(NumCasaAlbastru, _, albastru, _, _, _), Strada),
    member(casa(NumCasaNorvegian, norvegian, _, _, _, _), Strada),
    consec(NumCasaAlbastru, NumCasaNorvegian),

    member(casa(_, PosesorZebra, _, zebra, _, _), Strada).
