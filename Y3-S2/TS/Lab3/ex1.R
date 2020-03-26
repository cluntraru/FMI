x <- c(5)
MOD <- 150

getX <- function(xPrev) {
  3 * xPrev %% 150
}

for (i in 2:11)
  x <- c(x, getX(x[i - 1]))

# Functie
aleator <- function(x0, idx, num) {
  if (idx == 0) {
    return(x0)
  }
  
  xHead = aleator(x0, idx - 1, num)
  return(c(xHead, geX(xHead[idx - 1])))
}

rasp = aleator(5, 11, 11)