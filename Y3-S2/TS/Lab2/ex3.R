require(plotrix)
n <- 10000
U <- runif(n, -1, 1)
V <- runif(n, -1, 1)

k <- 0

rez <- 4 * sum(ifelse(U ^ 2 + V ^ 2 <= 1, 1, 0)) / n

index <- U^2 + V^2 <= 1
#plot(U[index], V[index], asp = 1, col="red")
plot(U[!index], V[!index], asp=1, col="green", pch=20, cex=0.5)

indici <- which(U^2 + V^2 <= 1)
points(U[indici], V[indici], col="red", pch=20, cex=0.5)

#plotrix
draw.circle(0, 0, 1, border="black", lwd=2)