import matplotlib.pyplot as plt
import numpy as np

def f1(x):
    return 1 + x


def f2(x):
    return 3 - x

def Segment():
    # f(x1, x2) = x1 + x2
    # x1 + x2 <= 3
    # x2 - x1 <= 1
    # x1, x2 >= 0
    plt.subplot(221)
    plt.title('Intersectie Segment: x1, x2 >= 0')
    xRange = (-2, 5)
    yRange = (-2, 5)
    
    OY = np.arange(yRange[0], yRange[1], 0.01)
    
    plt.xlim(xRange[0], xRange[1])
    plt.ylim(yRange[0], yRange[1])
    
    X = np.arange(xRange[0], xRange[1], 0.01)
    OX = [0 for i in range(len(X))]
    Y1 = f1(X)
    Y2 = f2(X)
    
    plt.plot(X, Y1, 'g')
    plt.plot(X, Y2, 'g')
    plt.plot(X, OX, 'g')
    plt.plot([0 for i in range(len(OY))], OY, 'g')
    
    # Zona cu valori posibile
    fillX = np.arange(0, 3, 0.01)
    hiY = np.concatenate((np.arange(1, 2, 0.01), np.arange(2, 0, -0.01)))
    loY = [0 for i in range(len(fillX))]
    
    plt.fill_between(fillX, loY, hiY)
    
    # Solutia
    solX = np.arange(1, 3, 0.01)
    solY = np.arange(2, 0, -0.01)
    plt.plot(solX, solY, 'y--')
    
    plt.grid(True)


def Punct():
    # f(x1, x2) = x1 + x2
    # x1 + x2 <= 3
    # x2 - x1 <= 1
    # x1 >= 0
    # x2 >= 2
    plt.subplot(222)
    plt.title('Intersectie Punct: x1 >= 0, x2 >= 2')
    xRange = (-2, 5)
    yRange = (-2, 5)
    
    OY = np.arange(yRange[0], yRange[1], 0.01)
    
    plt.xlim(xRange[0], xRange[1])
    plt.ylim(yRange[0], yRange[1])
    
    X = np.arange(xRange[0], xRange[1], 0.01)
    Y1 = f1(X)
    Y2 = f2(X)
    
    plt.plot(X, Y1, 'g')
    plt.plot(X, Y2, 'g')
    plt.plot(X, [2 for i in range(len(X))], 'g')
    plt.plot([0 for i in range(len(OY))], OY, 'g')
    
    # Solutia
    solX = np.arange(-2, 5, 0.01)
    solY = np.arange(5, -2, -0.01)
    plt.plot(solX, solY, 'y--')
    #solX = 1
    #solY = 2
    #plt.plot(X, [2 for i in range(len(X))], 'y--')
    #plt.plot(solX, solY, 'ro', alpha=1.0)

    # Zona cu valori posibile
    plt.plot(1, 2, 'bs', alpha = 0.4)
    
    plt.grid(True)


def Vid():
    # f(x1, x2) = x1 + x2
    # x1 + x2 <= 3
    # x2 - x1 <= 1
    # x1 >= 0
    # x2 >= 3
    plt.subplot(223)
    plt.title('Intersectie Vida: x1 >= 0, x2 >= 3')

    xRange = (-2, 5)
    yRange = (-2, 5)
    
    OY = np.arange(yRange[0], yRange[1], 0.01)
    
    plt.xlim(xRange[0], xRange[1])
    plt.ylim(yRange[0], yRange[1])
    
    X = np.arange(xRange[0], xRange[1], 0.01)
    Y1 = f1(X)
    Y2 = f2(X)
    
    plt.plot(X, Y1, 'g')
    plt.plot(X, Y2, 'g')
    plt.plot(X, [3 for i in range(len(X))], 'g')
    plt.plot([0 for i in range(len(OY))], OY, 'g')
    
    # Solutia
    solX = np.arange(-2, 5, 0.01)
    solY = np.arange(5, -2, -0.01)
    plt.plot(solX, solY, 'y--')
    #plt.plot(X, [3 for i in range(len(X))], 'y--')
    
    plt.grid(True)


def Infinit():
    # f(x1, x2) = x1 + x2
    # x1 + x2 <= 3
    # x2 - x1 <= 1
    plt.subplot(224)
    plt.title('Intersectie Infinit: x1, x2 reale')
    xRange = (-2, 5)
    yRange = (-2, 5)
    
    OY = np.arange(yRange[0], yRange[1], 0.01)
    
    plt.xlim(xRange[0], xRange[1])
    plt.ylim(yRange[0], yRange[1])
    
    X = np.arange(xRange[0], xRange[1], 0.01)
    OX = [0 for i in range(len(X))]
    Y1 = f1(X)
    Y2 = f2(X)
    
    plt.plot(X, Y1, 'g')
    plt.plot(X, Y2, 'g')
    plt.plot(X, OX, 'g')
    plt.plot([0 for i in range(len(OY))], OY, 'g')
    
    # Zona cu valori posibile
    fillX = X
    hiY = np.concatenate((np.arange(-1, 2, 0.01), np.arange(2, -2, -0.01)))
    loY = [-2 for i in range(len(fillX))]
    
    plt.fill_between(fillX, loY, hiY)
    
    # Solutia
    solX = np.arange(1, 5, 0.01)
    solY = np.arange(2, -2, -0.01)
    plt.plot(solX, solY, 'y--')
    
    plt.grid(True)

plt.figure()
Segment()
Punct()
Vid()
Infinit()
plt.show()

