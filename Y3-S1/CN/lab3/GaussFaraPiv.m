function [Xs] = GaussFaraPiv(A, b)
    AExt = [A b];
    n = size(A, 1);
    for k = 1 : n - 1
        p = 1;
        while p <= n && AExt(k, p) == 0
            p = p + 1;
        end
        
        if AExt(k, p) == 0
            printf("Sistem incompatibil sau compatibil nedeterminat.");
        end
        
        if p ~= k
            if p < k
                l1 = p;
                l2 = k;
            else
                l1 = k;
                l2 = p;
            end
                
            lin1 = AExt(l1, :);
            lin2 = AExt(l2, :);

            chonk1 = AExt(1: l1 - 1);
            if isEmpty(chonk1)
                chonk1 = 
            AExt(l1 + 1 : l2 - 2)
            AExt(l2 + 1 : n)

            AExt = [AExt(1 : l1 - 1); lin1; AExt(l1 + 1 : l2 - 1);...
                    lin2; AExt(l2 + 1 : n)];
        end
        AExt
        for l = k + 1 : n
            l
            Mlk = AExt(l, k) / AExt(k, k);
            Mlk
            AExt(l, :) = AExt(l, :) - Mlk * AExt(k, :);
        end
    end
    
    if AExt(n, n) == 0
        printf("Sistem incomp sau comp nedet");
        return;
    end
    
    Xs = SubsDesc(A, AExt(: , n + 1));
end