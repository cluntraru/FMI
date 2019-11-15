function [xAprox] = MetBisectie(f, A, B, Eps)
    a(1) = A;
    b(1) = B;
    x(1) = (A + B) / 2;
    N = floor(log2((B - A) / Eps)) + 1;
    for k = 2 : N
        if f(x(k - 1)) == 0
            x(k) = x(k - 1);
            break;
        elseif f(a(k - 1)) * f(x(k - 1)) < 0
            a(k) = a(k - 1);
            b(k) = x(k - 1);
            x(k) = (a(k) + b(k)) / 2;
        elseif f(a(k - 1)) * f(x(k - 1)) > 0
            a(k) = x(k - 1);
            b(k) = b(k - 1);
            x(k) = (a(k) + b(k)) / 2;
        end
    end
    
    xAprox = x(k);
end