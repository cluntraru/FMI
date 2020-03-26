n <- 100000
a <- 0
b <- 1

U <- runif(n, a, b)
g <- function(t) {
  ((t / (1 - t)) ^ 3) * ((1 + (t / (1 - t)) ^ 2) ^ -2)
}

gu <- g(U)
rez <- sum(gu) / n
