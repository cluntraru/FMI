 x
 [1]  3.700000  4.200000  5.800000  6.900000  2.700000  5.500000  6.300000
 [8]  1.700000  2.000000  3.200000  2.300000  0.200000  3.500000  7.200000
[15]  3.141593  6.000000  3.000000  8.100000  8.000000 10.000000 13.000000
> y
Error: object 'y' not found
> length(x)
[1] 21
> y
Error: object 'y' not found
> y=c(10,23,17,11,15,19,5,13,2,3,7,8,5,11,12,23,21,32,45,4,8)
> length(y)
[1] 21
> #aflati o estimare nedeplasata pentru sigma 2
> xbar=mean(x)
> xbar
[1] 5.068647
> ybar=mean(y)
> ybar
[1] 14
> n=length(x)
> n
[1] 21
> #b:=B^
> b=sum((x-xbar)*(y-ybar))/sum((x-xbar)^2)
> b
[1] 0.7693001
> #a:=A^
> a=ybar-b*xbar
> a
[1] 10.10069
> #sigma 2 ^:=s2
> s2=(sum((y-ybar)^2)-b^2*sum((x-xbar)^2))/(n-2)
> s2
[1] 110.8085
> #Y~N(alfa+beta x,sigma 2)
> a) Aflati un interval de 90% incredere pentru alfa
Error: unexpected ')' in "a)"
> b=sum((x-xbar)*(y-ybar))/sum((x-xbar)^2)
> a=ybar-b*xbar
> s2=(sum((y-ybar)^2)-b^2*sum((x-xbar)^2))/(n-2)
> n=length(x)
> #ga:=gama
> ga=0.1
> #[100(1-gama)]%=90%
> #ta=t indice n-2,gama/2
> ta=qt(1-ga/2,n-2)
> ta
[1] 1.729133
> l1a=a-ta*sqrt(s2*sum(x^2)/(n*sum((x-xbar)^2)))
> l1a
[1] 2.322628
> l2a=a+ta*sqrt(s2*sum(x^2)/(n*sum((x-xbar)^2)))
> l2a
[1] 17.87875
> #Intervalul de 90% incredere pt. alfa e (2.322628,17.87875)
> #b) un interval de 95% incredere pt. beta
> gb=0.05
> tb=qt(1-gb/2,n-2)
> tb
[1] 2.093024
> b
[1] 0.7693001
> a
[1] 10.10069
> l1b=b-tb*sqrt(s2/sum((x-xbar)^2))
> l1b
[1] -0.8277303
> l2b=b+tb*sqrt(s2/sum((x-xbar)^2))
> l2b
[1] 2.36633
> #Intervalul de 95% incredere pt. beta e (-0.8277303,2.36633)
> #c) un interval de 99% incredere pt. alfa + beta x
> gc=0.01
> a
[1] 10.10069
> b
[1] 0.7693001
> tc=qt(1-gc/2,n-2)
> tc
[1] 2.860935
> s2
[1] 110.8085
> n
[1] 21
> xbar
[1] 5.068647
> sum((x-xbar)^2)
[1] 190.3247
> #un interval de 99% incredere pt. alfa + beta x e
> #(10.10069+0.7693001x-2.860935radical(110.8085(1/21+(x-5.068647)^2/190.3247)),
> #10.10069+0.7693001x+2.860935radical(110.8085(1/21+(x-5.068647)^2/190.3247)))
> #d) un interval de 99.5% incredere pentru sigma ^ 2 cu ambele margini finite
> gd=0.005
> c1d=qchisq(1-gd/2,n-2)
> c1d
[1] 40.88497
> c2d=qchisq(gd/2,n-2)
> c2d
[1] 6.16736
> l1d=(n-2)*s2/c1d
> l1d
[1] 51.49475
> l2d=(n-2)*s2/c2d
> l2d
[1] 341.3716
> #un interval de 99.5% incredere pentru sigma ^ 2 cu ambele margini finite e
> #(51.49475,341.3716)
> e) un interval de 99,9% incredere pentru sigma ^ 2 cu o margine finita
Error: unexpected ')' in "e)"
> ge=0.001
> ce=qchisq(1-ge,n-1)
> l=(n-2)*s2/ce
> l
[1] 46.46085
> #un interval de 99,9% incredere pentru sigma ^ 2 cu o margine finita e
> #(46.46085,infinit)
