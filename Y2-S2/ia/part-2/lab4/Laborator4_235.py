
# coding: utf-8

# # Laborator 4

# In[1]:


import numpy as np
import matplotlib.pyplot as plt


# In[2]:


dataPath = "/home/cluntraru/Documents/git-repos/FMI/Y2-S2/ia/half-2/data0/"
#load train images
train_images = np.loadtxt(dataPath + "train_images.txt")
train_labels = np.loadtxt(dataPath + "train_labels.txt",'int8')
print(train_images.shape)
print(train_images.ndim)
print(type(train_images[0,0]))
print(train_images.size)
print(train_images.nbytes)


# In[3]:


#plot the first 100 training images with their labels in a 10 x 10 subplot
nbImages = 10
plt.figure(figsize=(5,5))
for i in range(nbImages**2):
    plt.subplot(nbImages,nbImages,i+1)
    plt.axis('off')
    plt.imshow(np.reshape(train_images[i,:],(28,28)),cmap = "gray")
plt.show()
labels_nbImages = train_labels[:nbImages**2]
print(np.reshape(labels_nbImages,(nbImages,nbImages)))


# In[4]:


#load test images
test_images = np.loadtxt(dataPath + "test_images.txt")
test_labels = np.loadtxt(dataPath + "test_labels.txt",'int8')
#plot the first 100 testing images with their labels in a 10 x 10 subplot
nbImages = 10
plt.figure(figsize=(5,5))
for i in range(nbImages**2):
    plt.subplot(nbImages,nbImages,i+1)
    plt.axis('off')
    plt.imshow(np.reshape(test_images[i,:],(28,28)),cmap = "gray")
plt.show()
labels_nbImages = test_labels[:nbImages**2]
print(np.reshape(labels_nbImages,(nbImages,nbImages)))


# In[ ]:


#do 1-NN, 3-NN, 5-NN, 7 -NN for the first test image
#plot the neighbors

img = test_images[0]
c = np.sqrt(((a - b) ** 2).sum(axis = 1))
print(c)

a = np.array([[1, 2], [2, 3], [3, 2]])
b = np.array([2, 5])
c = a - b
print(c)

# In[ ]:


def compute_accuracy(true_labels, predicted_labels):
	return (true_labels == predicted_labels).mean()


#define class Knn_classifier
class Knn_classifier:
	def __init__(self, train_images, train_labels):
		self.train_images = train_images
		self.train_labels = train_labels

	def classify_image(self, test_image, num_neighbors = 3, metric = 'l2'):
		if metric == 'l2':
			distances = np.sqrt(((self.train_images - test_images) ** 2).sum(axis = 1))
		elif metric == 'l1':
			distances = (np.abs(self.train_images - test_images)).sum(axis = 1)
		else:
			print('Error')

		indices = distances.argsort()
		indices_knn = indices[:num_neighbors]
		train_labels_knn = self.train_labels[indices_knn]
		c = np.bincount(train_labels_knn)
		return c.argmax()

classifier= Knn_classifier(train_images, train_labels)
print(classifier.classify_image(img, num_neighbors = 1))
predicted_labels = np.zeros(500)
for i in range(500):
	predicted_labels[i] = classifier.classify_image(test_images[i])

print(compute_accuracy(test_labels.predicted_labels))