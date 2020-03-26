n <- 100000
a <- 0
b <- 1

U <- runif(n, a, b)

g <- function(t) {
  exp(-(t / (1 - t)) ^ 2) * (1 / (1 - t) ^ 2)
}

g2 <- function(u) {
  exp(-(tan(u) ^ 2)) / (cos(u) ^ 2)
}

gu <- g(U)
rez <- 2 * sum(gu) / n
