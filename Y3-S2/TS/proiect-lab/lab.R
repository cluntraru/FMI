# Functia de intensitate din enunt
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

# Functie care intoarce timpul la care se petrece urmatorul eveniment Ts
genPoisson <- function(s, lambda, intensity) {
  # Initial, ne aflam la momentul de timp s
  t <- s
  # Generam U1 si U2
  U <- runif(2)
  # Actualizam momentul de timp curent
  t <- t - 1 / lambda * log(U[1])
  # Regeneram U1, U2 cat timp nu se indeplineste U2 <= lambda(t)/t
  while (U[2] > intensity(t) / lambda) {
    U <- runif(2)
    # Actualizam timpul, analog cu mai sus
    t <- t - 1 / lambda * log(U[1])
  }
  
  # Daca este indeplinita conditia, atunci Ts = t, deci returnam t
  return(t)
}