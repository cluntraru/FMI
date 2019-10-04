f = @(x) x.^3 - 7.*x.^2+14*x-6;
X = linspace(0, 4, 100);
Y = f(X);
plot(X, Y, 'LineWidth', 2)
grid on
hold on
line(xlim, [0 0], 'Color', 'k', 'LineWidth', 2)
line([0 0], ylim, 'Color', 'k', 'LineWidth', 2)

eps = 10^(-5);
[xaprox1] = MetBisectie(f, 0, 1, eps)
[xaprox2] = MetBisectie(f, 1, 3.2, eps)
[xaprox3] = MetBisectie(f, 3.2, 4, eps)

plot(xaprox1, f(xaprox1), 'o', 'MarkerFaceColor', 'g', 'MarkerSize', 10)
plot(xaprox2, f(xaprox2), 'o', 'MarkerFaceColor', 'g', 'MarkerSize', 10)
plot(xaprox3, f(xaprox3), 'o', 'MarkerFaceColor', 'g', 'MarkerSize', 10)
title('Metoda Bisectiei')

hold off