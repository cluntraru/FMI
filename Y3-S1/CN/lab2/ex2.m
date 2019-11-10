syms x;
f = @(x) x .^ 2 - 5.5 * x + 6;
% 2. b)
df = diff(f, x, 1);
mu = f / df;
simplify(mu);

% 2. c)
Xs = linspace(1, 2);

figure
hold on

plot(Xs, f(Xs));
plot(Xs, subs(mu, x, Xs));

line([0 0], ylim);
line(xlim, [0 0]);

[xAprox] = MetNR(mu, dmu, 1.5, 10^(-5));
plot(xAprox, f(xAprox), 'o');

hold off

% 2. a)
dmu = diff(mu, x, 1);
m = 1 / subs(dmu, x, 1.5);
m