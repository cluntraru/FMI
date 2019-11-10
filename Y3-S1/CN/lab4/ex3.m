A = [0 1 1; 2 1 5; 4 2 1];
b = [3; 5; 1];

[L, U, w] = Lu(A);
L
U
% w
% L * U

[L2, U2, w2] = lu(A);
L2
U2
% w2