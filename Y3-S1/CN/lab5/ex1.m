A = [1 2 3; 2 5 8; 3 8 14];
b = [-5; -14; -25];

[x, L] = FactCholesky(A, b);
L
x