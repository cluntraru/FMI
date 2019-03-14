%---------------------------------
% Jon Snow and Daenerys Targaryen
%---------------------------------

male(rickardStark).
male(eddardStark).
male(brandonStark).
male(benjenStark).
male(robbStark).
male(aerysTargaryen).
male(rhaegarTargaryen).


%------------------------

female(lyarraStark).
female(catelynStark).
female(lyannaStark).
female(sansaStark).
female(aryaStark).
female(rhaellaTargaryen).
female(eliaTargaryen).

%------------------------

parent_of(rickardStark, lyarraStark).
parent_of(rickardStark, brandonStark).
parent_of(rickardStark, eddardStark).
parent_of(brandonStark, rhaellaTargaryen).
parent_of(rhaellaTargaryen, aryaStark).
parent_of(aryaStark, robbStark).
%% parent_of(brandonStark, aryaStark).


%------------------------

mother_of(X, Y) :- parent_of(X, Y), female(X).

father_of(X, Y) :- parent_of(X, Y), male(X).

grandfather_of(X, Y) :- father_of(X, Z), parent_of(Z, Y).

grandmother_of(X, Y) :- mother_of(X, Z), parent_of(Z, Y).

sister_of(X, Y) :- parent_of(Z, X), parent_of(Z, Y), female(X), \+ X == Y.

brother_of(X, Y) :- parent_of(Z, X), parent_of(Z, Y), male(X),  \+ X == Y.

aunt_of(X, Y) :- parent_of(Z, Y), sister_of(X, Z).

uncle_of(X, Y) :- parent_of(Z, Y), brother_of(X, Z).

ancestor_of(X, Y) :- parent_of(X, Y).
ancestor_of(X, Y) :- parent_of(Z, Y), ancestor_of(X, Z).
