f = @(x) x .^ 3 - 18 * x - 10;
Xs = linspace(-5, 5);
eps = 10^(-5);

% 3. a)
hold on

plot(Xs, f(Xs));

line([0 0], ylim);
line(xlim, [0 0]);

% 3. d) [-5, -3], [-1, 0], [4, 5]
[xSec1] = MetSecantei(f, -5, -3, -4, -2, eps);
[xSec2] = MetSecantei(f, -1, 0, -0.75, -0.25, eps);
[xSec3] = MetSecantei(f, 4, 5, 4.4, 4.6, eps);

% 3. e)
[xPozF1] = MetPozFalse(f, -5, -3, eps);
[xPozF2] = MetPozFalse(f, -1, 0, eps);
[xPozF3] = MetPozFalse(f, 4, 5, eps);

plot(xPozF1, f(xPozF1), 'o');
plot(xPozF2, f(xPozF2), 'o');
plot(xPozF3, f(xPozF3), 'o');

hold off