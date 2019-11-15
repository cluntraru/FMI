function [rang] = Rang(A, tol)
    n = size(A, 1);
    m = size(A, 2);
    h = 1;
    k = 1;
    rang = 0;
    while h <= m && k <= n
        p = h;
        for j = h : k
            if abs(A(p, k)) < abs(A(j, k))
                p = j;
            end
        end
        
        if abs(A(p, k)) <= tol
            k = k + 1;
            continue;
        end
        
        if p ~= h
            linK = A(k, :);
            A(k, :) = A(h, :);
            A(h, :) = linK;
        end
        
        for l = h + 1 : m
            mlk = A(l, k) / A(h, k);
            A(l, :) = A(l, :) - mlk * A(h, :);
        end
               
        h = h + 1;
        k = k + 1;
        rang = rang + 1;
    end
end