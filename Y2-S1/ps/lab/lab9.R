# Repartitia normala de medie m si dispersie \sigma_2

m <- 0
sigma <- 1
x <- seq(-5, 5, 0.001)

plot(x, dnorm(x, m, sigma))
for (i in -3:3) {
  lines(x, dnorm(x, i, sigma), col=i+4)
}

plot(x, dnorm(x, m, sigma), xlim=c(-2, 2), ylim=c(0, 0.3))
for (i in -3:3) {
  lines(x, dnorm(x, m, i+4), col=i+4)
}

plot(x, pnorm(x, m, sigma))
for (i in -3:3) {
  lines(x, pnorm(x, i, sigma), col=i+4)
}

# Proprietatile functiei \Phi

y <- rep(0.5, length(x))
plot(x, pnorm(x))
lines(x, y)
