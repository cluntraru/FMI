% A = [0 1 -2; 1 -1 1; 1 0 -1];
A = [1 -2 3; -2 3 -4; 3 -4 5];
tol = 10 ^ (-10);

[rang] = Rang(A, tol);
rang

% rank = rank(A, tol);
% rank

rank(A)
