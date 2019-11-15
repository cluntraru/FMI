f = @(x) x .^ 3 - 7 * x .^ 2 + 14 * x - 6;
syms x;
df = diff(f, x, 1);
x = linspace(0, 4);

hold on

line(xlim, [0 0]);
line([0 0], ylim);
plot(x, f(x));

eps = 10^(-5);
[xAprox1] = MetNR(f, df, 0.5, eps);
[xAprox2] = MetNR(f, df, 2.869, eps);
[xAprox3] = MetNR(f, df, 3.48, eps);

plot(xAprox1, f(xAprox1), 'o', 'MarkerSize', 10);
plot(xAprox2, f(xAprox2), 'o', 'MarkerSize', 10);
plot(xAprox3, f(xAprox3), 'o', 'MarkerSize', 10);
hold off