from random import random
from math import sqrt
from math import log
from matplotlib import pyplot as plt

def GenNorm():
    V1 = 0
    V2 = 0
    S = 1
    while S >= 1:
        U1 = random()
        U2 = random()
        V1 = 2 * U1 - 1
        V2 = 2 * U2 - 1
        S = V1 * V1 + V2 * V2

    sqrtVal = sqrt(-2 * log(S) / S)
    Z1 = V1 * sqrtVal
    Z2 = V2 * sqrtVal

    X1 = sqrt(5) * Z1 + 2.5
    X2 = sqrt(5) * Z2 + 2.5
    return (X1, X2)

Xs = []
for i in range(10000):
    x1x2 = GenNorm()
    Xs.append(x1x2[0])
    Xs.append(x1x2[1])

plt.hist(Xs, 100)
plt.show()
