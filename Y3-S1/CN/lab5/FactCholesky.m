function [x, L] = FactCholesky(A, b)
    alpha = A(1, 1);
    
    if alpha <= 0
        printf("A nu este pozitiv definita");
        return;
    end
    
    L(1, 1) = sqrt(A(1, 1));
    for i = 2 : n
        L(i, 1) = A(i, 1) / L(1, 1);
    end
    
    for k = 2 : n
        alpha = A(k, k) - sum(L(k, 1 : k - 1) .^ 2);
        if alpha <= 0
            printf("A nu este pozitiv definita");
            return;
        end
        
        L(k, k) = sqrt(alpha);
        for i = k + 1 : n
            L(i, k) = 1 / L(k, k) *...
                      (A(i, k) - sum(L(i, 1 : k - 1) .* L(k, 1 : k - 1)));
        end
    end
end