function [xAprox] = MetSecantei(f, a, b, x0, x1, eps)
    X(1) = x0;
    X(2) = x1;
    k = 2;
    while abs(X(k) - X(k - 1)) / abs(X(k - 1)) >= eps
        k = k + 1;
        X(k) = (X(k - 2) * f(X(k - 1)) - X(k - 1) * f(X(k - 2))) /...
               (f(X(k - 1)) - f(X(k - 2)));
          
        if X(k) < a || X(k) > b
           fprintf("Alte valori\n");
           break;
        end
    end
    
    xAprox = X(k);
end