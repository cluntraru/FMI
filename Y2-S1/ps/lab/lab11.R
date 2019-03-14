y <- c(1, 2, 4, 3, 2, 1, 2, 1, 3, 5, 4, 5, 5, 3, 3, 5, 2, 1, 5, 5, 6, 5, 3, 4, 3, 2, 5, 2, 4, 6, 1, 1)
y_sorted <- sort(y)
length(y_sorted)
me <- y_sorted[34]
y1 <- c(y[1:23], 5, y[24:32])
y[24]
y1[24]

me1 <- (y1s[21] + y1s[22]) / 2

quantile(y, 43 / 89)
summary(y)
hist(y, col="beige", main="main", freq=F)
lines(x, dgeom(x, 0.15), col="magenta")

m <- mean(y)
v <- var(y)

p <- rep(0, 9)
for (i in 1:9) {
  #frecvente relative de aparitie
  p[i] <- length(y[y == i]) / length(y)
}

# Numaram de cate ori apare o val intr-un vector
medie <- sum(1:9, p)

length(y[y==1])

p1 <- seq(0.1, 0.9, 0.1)

x <- 1:20
plot(x, dgeom(x, p1[1]), col="magenta")
for (i in 2:length(p1)) lines(x, dgeom(x, p1[i]))

hist(y, ylim=c(0, 12))
length(y[y <= 2 & y >= 1])
