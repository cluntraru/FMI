A = [3 1 1; 1 3 1; 1 1 3];
eps = 10 ^ (-4);

[jLambda] = MetJacobi(A, eps);
jLambda

mLambda = eigs(A);
mLambda