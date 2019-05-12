animal(alligator). 
animal(tortue).
animal(caribou).
animal(ours).
animal(cheval).
animal(vache).
animal(lapin).

mutant(R) :- animal(X), animal(Y), X \== Y, atom_chars(X, L1), atom_chars(Y, L2), can_combine(L1, L1, L2, R), R \= [].

% Checks if L1 and L2 can create a mutant and returns it
can_combine(L1og, L1, L2, R) :- L1 \= [], is_prefix(L1, L2), cut_off(L1, L2, L2suff), concat(L1og, L2suff, R).
can_combine(_, [], _, R) :- R = [].
can_combine(L1og, L1, L2, R) :- L1 \= [], \+ is_prefix(L1, L2), L1 = [_ | T1], can_combine(L1og, T1, L2, R).

% I know that L1 is a prefix of L2, and I want the suffix of L2
cut_off([], L2, R) :- R = L2.
cut_off(L1, L2, R) :- L1 = [_ | T1], L2 = [_ | T2], cut_off(T1, T2, R).

% Concatenates
concat([], L2, R) :- R = L2.
concat(L1, L2, R) :- L1 \= [], L1 = [H1 | T1], concat(T1, L2, R2), R = [H1 | R2].

% Check if L1 is a prefix of L2
is_prefix([], _) :- true.
is_prefix(_, []) :- false.
is_prefix(L1, L2) :- L1 = [H1 | T1], L2 = [H2 | T2], H1 = H2, is_prefix(T1, T2).
