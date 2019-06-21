import numpy as np
import matplotlib.pyplot as plt
import scipy
import skimage

# array
a = np.array([1, 2, 3])
print(a)

print(a.shape, '\n----')

# matrix
b = np.reshape(a, [3, 1])
# print transpose
print(b, '\n----')


c = np.arange(0, 9)
print(c, '\n----')
np.reshape(c, (3, 3))
print(c[1:2][1:2])
print(c[1])
print(c[1:], '\n----')

g = np.zeros((4, 4))
print(g, '\n----')

h = np.ravel(c)
print(h, '\n----')

# np.dot(v1, v2)

a = np.array([[[1, 2, 3], [4, 5, 6]],
             [[1, 2, 3], [4, 5, 6]],
             [[1, 2, 3], [4, 5, 6]]])

m1 = np.mean(a, axis = 0)
print(m1, '\n----')

# broadcasting
a = np.array([[1, 2, 3], [4, 5, 6]])
b = 5

print(a + b)

# Plot
x = np.arange(0, 3 * np.pi, 0.1)
y = np.sin(x)
y2 = np.cos(x)

plt.figure()
plt.plot(x, y, '1')
plt.plot(y, y2, '1')
plt.subplot(2, 2, 2)
plt.show()