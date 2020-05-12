from random import randint
from math import sqrt
from matplotlib import pyplot as plt

def GenBernoulli():
    return randint(0, 1)

def GenNorm(n):
    bernoulliSum = 0
    for i in range(n):
        bernoulliSum += GenBernoulli()

    return 2 * sqrt(n) * (bernoulliSum / n - 0.5) * sqrt(5) + 2.5

n = 1000

Xs = []
for i in range(1000):
    norm = GenNorm(n)
    Xs.append(norm)

plt.hist(Xs, 20)
plt.show()


