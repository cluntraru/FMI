f = @(x) x.^3-7*x.^2+14*x-6;
X = linspace(0, 6, 100);
Y = f(X);
plot(X, Y, 'lineWidth', 2)
eps = 10^(-3);
syms x
df = diff(f, x, 1);
[x1] = MetNR(f, df, 0.5, eps);
[x2] = MetNR(f, df, 2.75, eps);
[x3] = MetNR(f, df, 3.75, eps);
grid on
xl = xlim;
yl = ylim;

hold on

line(xl, [0 0], 'Color', 'k')
line([0 0], yl, 'Color', 'k')

hold off