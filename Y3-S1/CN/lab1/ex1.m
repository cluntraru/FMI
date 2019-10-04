function [xaprox] = MetBisectie(f, t, B, eps)
    a(1) = A;
    b(1) = B;
    x(1) = 1/2 * (a(1) + b(1));
    N = floor(log2((B-A)/eps);
    for k = 2 : N + 1
        if f(x(k-1)) == 0
            x(k) = x(k - 1);
        elseif f(a(k - 1)) * f(x(k-1)) < 0
            a(k) = a(k - 1);
            b(k) = x(k - 1);
            x(k) = 1 / 2 * (a(k) + b(k));
        elseif f(a(b - 1)) * f(x(b - 1)) > 0
            a(k) = x(k - 1);
            b(k) = b(k - 1);
            x(k) = 1 / 2 * (a(k) + b(k));
        end
    end
    xaprox = x(k);
end

