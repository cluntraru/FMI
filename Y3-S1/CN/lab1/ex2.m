figure
y = linspace(0, 2, 100);
plot(y, exp(y) - 2)
figure
plot(y, cos(exp(y) - 2))
f = @(x) exp(x) - 2- cos(exp(x) - 2)

X = linspace(0.5, 1.5, 100)
Y = f(X);

figure
plot(X, Y)
eps = 10^(-5);
[xaprox] = MetBisectie(f, 0.5, 1.5, eps)