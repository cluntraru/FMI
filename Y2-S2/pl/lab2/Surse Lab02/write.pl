line(1, C) :- write(C).

line(N, C) :- N > 0,
              write(C),
              N1 is N - 1,
              line(N1, C).

rectangle(Nlin, Ncol, C) :- Nlin > 0,
                            line(Ncol, C), nl,
                            Nlin1 is Nlin - 1,
                            rectangle(Nlin1, Ncol, C).

square(N, C) :- rectangle(N, N, C).
