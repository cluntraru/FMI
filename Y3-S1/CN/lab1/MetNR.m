function [xAprox] = MetNR(f, df, x0, eps)
    k = 0;
    X(0) = x0;
    while abs(X(k) - X(k - 1)) / abs(X(k - 1)) > eps
        k = k + 1;
        X(k) = X(k - 1) - f(X(k-1)) / df(X(k - 1));
    end
    
    xAprox = X(k);
end