import numpy as np

output0 = np.genfromtxt("output0.csv", delimiter=",", skip_header=1)[:,1]
output1 = np.genfromtxt("output1.csv", delimiter=",", skip_header=1)[:,1]
output2 = np.genfromtxt("output2.csv", delimiter=",", skip_header=1)[:,1]
labels0 = np.genfromtxt("train_labels0.csv", delimiter=",")[:,1]
labels1 = np.genfromtxt("train_labels1.csv", delimiter=",")[:,1]
labels2 = np.genfromtxt("train_labels2.csv", delimiter=",")[:,1]

matrix0 = np.zeros(shape=(21, 21))
matrix1 = np.zeros(shape=(21, 21))
matrix2 = np.zeros(shape=(21, 21))

for i in range(3000):
    matrix0[int(labels0[i])][int(output0[i])] += 1
    matrix1[int(labels1[i])][int(output1[i])] += 1
    matrix2[int(labels2[i])][int(output2[i])] += 1


f0 = open("matrix0.txt", "w")
f1 = open("matrix1.txt", "w")
f2 = open("matrix2.txt", "w")
count = 0
for i in range(1, 21):
    for j in range(1, 21):
        count += int(matrix0[i][j])
        f0.write(str(int(matrix0[i][j])) + " ")
        f1.write(str(int(matrix1[i][j])) + " ")
        f2.write(str(int(matrix2[i][j])) + " ")

    f0.write("\n")
    f1.write("\n")
    f2.write("\n")
