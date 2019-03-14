# Problema cu testul de paternitate
# p este prob ca Gigel sa fie tatal copilului

p <- 1 - pnorm(2) + 1 - pnorm(3)

integrate(dnorm, -Inf, 1.555)

a <- pnorm(1.555)
qnorm(a)

simona <- function(x) {
  x^3
}

d <- integrate(simona, -1, 1)
# e <- integrate(simona, -Inf, 2)
g <- gamma(1/2)
spi <- sqrt(pi)