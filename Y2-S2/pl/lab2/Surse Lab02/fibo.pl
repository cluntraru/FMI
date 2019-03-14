fib(1, X, Y) :- X is 1, Y is 0.

fib(N, Val, Prev) :-
    N > 1,
    Nprev is N - 1,
    fib(Nprev, Prev, Prevprev),
    Val is Prev + Prevprev.
