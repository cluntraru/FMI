function [xAprox] = MetNR(f, df, x0, eps)
    k = 2;
    X(1) = x0;
    X(2) = X(1) - subs(f, X(1)) / subs(df, X(1));
    while abs(X(k) - X(k - 1)) / abs(X(k - 1)) > eps
        k = k + 1;
        X(k) = X(k - 1) - subs(f, X(k-1)) / subs(df, X(k - 1));
    end
    
    xAprox = X(k);
end