function [Xs] = SubsDesc(A, B)
    sz = size(A, 1);
    X(sz) = 1 / A(sz, sz) * B(sz);
    k = sz - 1;
    while k > 0
        lineK = A(k, :);
        X(k) = 1 / A(k, k) * (B(k) - sum(lineK(k + 1:sz) .* X(k + 1:sz))); 
        k = k - 1;
    end
    
    Xs = X;
end