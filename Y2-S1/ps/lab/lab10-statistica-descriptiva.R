# Statistica descriptiva

# Importare de fisiere .dat
d <- read.table("~/iCloud/university/Y2-S1/ps/lab/d2.dat", header = TRUE)
attach(d)
t <- seq(12, 34, 0.001)
v <- var(y)

hist(y/sum(y), freq=FALSE)
lines(t, dnorm(t, m, sqrt(v)), col="red")

# summary(y)
# pie(y, labels=id, main="O placinta")
# barplot(facultate/49, names.arg=departament)