intensity <- function(t) {
  if (t < 0 || t > 24) {
    return(-1)
  } else if (t >= 0 && t <= 8) {
    return(15)
  } else if (t < 14) {
    return(2 * tan(0.1 * t) + 14)
  } else {
    return(9)
  }
}

genPoisson <- function(s, lambda, intensity) {
  t <- s
  
  U <- runif(2)
  t <- t - 1 / lambda * log(U[1])
  while (U[2] > intensity(t) / lambda) {
    U <- runif(2)
    t <- t - 1 / lambda * log(U[1])
  }
  
  return(t)
}