> x=c(5,6,11,23,13,21,3,15,3,9,2,11,8,5,17,23,11,12,6,24,7,10,23,12,9,25,22,4,13,13,3,7,10,1,8,9,5,20,17,18,2,3,7,19,10,10,3,22,42,68,25,30,5,8)
> length(c)
[1] 1
> length(x)
[1] 54
> mean(x)
[1] 13.2963
> var(x)
[1] 128.9294
> #Verificati ipoteza H: X are rep. normala de medie 10 si dispersie 100 la un nivel de semnificatie de 5%
> x
 [1]  5  6 11 23 13 21  3 15  3  9  2 11  8  5 17 23 11 12  6 24  7 10 23 12  9 25 22  4 13 13  3  7 10  1  8  9  5
[38] 20 17 18  2  3  7 19 10 10  3 22 42 68 25 30  5  8
> #1)
> range(x)
[1]  1 68
> #Impartim R in 10 intervale disjuncte
> 68-1
[1] 67
> y=integer(11)
> y
 [1] 0 0 0 0 0 0 0 0 0 0 0
> y[1]=-Inf
> for (i in 2:10) y[i]=1+(i-1)*67/10
> y[11]=Inf
> y
 [1] -Inf  7.7 14.4 21.1 27.8 34.5 41.2 47.9 54.6 61.3  Inf
> # A1=(-infinit, 7.7], A2=(7.7, 14.4], ... ,A10=(61.3, infinit)
> # Det. nr. de valori ale selectiei din fiecare interval
> n=ieteger(10)
Error in ieteger(10) : could not find function "ieteger"
> n=integer(10)
> n
 [1] 0 0 0 0 0 0 0 0 0 0
> for (i in 1:54){
+ for (j in 1:10){
+ if((y[j]<x[i])&&(x[i]<=y[j+1]))
+ {n[j]=n[j]+1
+ next}}}
> n
 [1] 18 18  7  8  1  0  1  0  0  1
> sum(n)
[1] 54
> #nj<5, pt. j=5,...,10
> #combinam intervalele A4, A5, ..., A10
> k=4
> n=c(18,18,7,11)
> length(n)
[1] 4
> sum(n)
[1] 54
> y=c(-Inf, 7.7,14.4,21.1,Inf)
> length(y)
[1] 5
> # A1=(-infinit, 7.7], A2=(7.7, 14.4],A3=(14.4,21.1],A4=(21.1,infinit)
> #2)
> #determinam prob. teoretice
> p=integer(4)
> p
[1] 0 0 0 0
> p[1]=pnorm(y[2],10,10)
> for (i in 2:3) {p[i]=pnorm(y[i+1],10,10)-pnorm(y[i],10,10)}
> p[4]=1-pnorm(y[4],10,10)
> p
[1] 0.4090459 0.2609856 0.1964690 0.1334995
> sum(p)
[1] 1
> #3)
> #det. d
> d=sum(n^2/(54*p))-54
> d
[1] 5.061272
> #4)
> #det. chipatrat indice k-1, alfa
> qchisq(1-0.05,3)
[1] 7.814728
> #5) d<=chipatrat indice k-1, alfa -> acceptam ipoteza
> #cu aceleasi date, det daca o repartitie normala e potrivita la un nivel de semnificatie de 0.1% 
> #1) ca mai sus
> #2) m=mean(x)
> m
Error: object 'm' not found
> m=mean(x)
> m
[1] 13.2963
> sigma=sqrt((53/54)*var(x))
> sigma
[1] 11.24908
> #3)
>  p[1]=pnorm(y[2],m,sigma)
> for (i in 2:3) {p[i]=pnorm(y[i+1],m,sigma)-pnorm(y[i],m,sigma)
+ }
> p[4]=1-pnorm(y[4],m,sigma)
> p
[1] 0.3094221 0.2296574 0.2169913 0.2439292
> sum(p)
[1] 1
> #4)
> d=d=sum(n^2/(54*p))-54
> d
[1] 4.884655
> #5) k-r-1=4-2-1=1
> #det chipatrat indice k-r-1, alfa
> qchisq(1-0.001,1)
[1] 10.82757
> #6) d<=chipatrat indice k-r-1, alfa -> acceptam ipoteza rep. normale cu m=13.2963 si sigma = 11.24908 la nivelul de 0.1%