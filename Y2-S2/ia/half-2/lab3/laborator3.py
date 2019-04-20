
# coding: utf-8

# # Rezolvare laborator 3

# In[1]:


import numpy as np
import matplotlib.pyplot as plt


# In[2]:


dataPath = "/home/cluntraru/Documents/university/Y2-S2/ia/half-2/lab3/data"
#load train images
train_images = np.loadtxt(dataPath + "train_images.txt")
print(train_images.shape)
print(train_images.ndim)
print(type(train_images[0,0]))
print(train_images.size)
print(train_images.nbytes)


# In[3]:


#plot the first image
image = train_images[0,:]
image = np.reshape(image,(28,28))
plt.imshow(image,cmap = "gray")
plt.show()


# In[4]:


#load training labels
train_labels = np.loadtxt(dataPath + "train_labels.txt",'int8')
print(train_labels.shape)
print(type(train_labels[0]))
print(train_labels.size)
print(train_labels.nbytes)
#show the label of the first training image
print(train_labels[0])


# In[5]:


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

