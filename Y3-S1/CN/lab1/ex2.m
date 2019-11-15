figure;
x = linspace(0.5, 1.5);
plot(x, exp(x) - 2);

figure
plot(x, cos(exp(x) - 2));

f = @(x) exp(x) - 2 - cos(exp(x) - 2);
eps = 10^(-5);
xaprox = MetBisectie(f, 0.5, 1.5, eps);
xaprox