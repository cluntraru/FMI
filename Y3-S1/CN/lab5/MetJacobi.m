function [lambda] = MetJacobi(A, eps)
    n = size(A, 1);
    diagSum = 0;
    for i = 1 : n
        diagSum = diagSum + A(i, i) ^ 2;
    end
    modA = abs(sum(reshape(A .^ 2, [1 n ^ 2])) - diagSum);
    
    while modA >= eps
        p = 1;
        q = 1;
        for i = 1 : n
            for j = i + 1 : n
                if abs(A(p, q)) < abs(A(i, j))
                    p = i;
                    q = j;
                end
            end
        end
        
        if A(p, p) == A(q, q)
            theta = pi / 4;
        else
            theta = 1 / 2 * atan(2 * A(p, q) / (A(q, q) - A(p,p)));
        end
        
        c = cos(theta);
        s = sin(theta);
        
        for j = 1 : n
            if j ~= p && j ~= q
                u = A(p, j) * c - A(q, j) * s;
                v = A(p, j) * s - A(q, j) * c;
                A(p, j) = u;
                A(q, j) = v;
                A(j, p) = u;
                A(j, q) = v;
            end
        end
        
        u = c ^ 2 * A(p, p) - 2 * c * s * A(p, q) + s ^ 2 * A(q, q);
        v = s ^ 2 * A(p, p) + 2 * c * s * A(p, q) + c ^ 2 * A(q, q);
        A(p, p) = u;
        A(q, q) = v;
        A(p, q) = 0;
        A(q, p) = 0;
        
        diagSum = 0;
        for i = 1 : n
            diagSum = diagSum + A(i, i) ^ 2;
        end
        modA = abs(sum(reshape(A .^ 2, [1 n ^ 2])) - diagSum);
    end
    
    for i = 1 : n
        lambda(i) = A(i, i);
    end
end