function [xAprox] = MetPozFalse(f, a, b, eps)
    A(1) = a;
    B(1) = b;
    X(1) = (A(1) * f(B(1)) - B(1) * f(A(1))) / (f(B(1)) - f(A(1)));
    
    k = 1;
    while 1
        k = k + 1;
        if f(X(k - 1)) == 0
            X(k) = X(k - 1);
            break;
        elseif f(A(k -1)) * f(X(k - 1)) < 0
            A(k) = A(k - 1);
            B(k) = X(k - 1);
            X(k) = (A(k) * f(B(k)) - B(k) * f(A(k))) / (f(B(k)) - f(A(k)));
        elseif f(A(k - 1)) * f(X(k - 1)) > 0
            A(k) = X(k - 1);
            B(k) = B(k - 1);
            X(k) = (A(k) * f(B(k)) - B(k) * f(A(k))) / (f(B(k)) - f(A(k)));
        end
        
        if abs(X(k) - X(k - 1)) / abs(X(k - 1)) < eps
            break
        end
    end
    
    xAprox = X(k);
end