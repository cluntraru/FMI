import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm 
from sklearn import preprocessing
import sklearn.metrics as sm
import pdb

def normalize_data(train_data, test_data, type=None):
    if type is None:
        return train_data, test_data
        
    if(type == 'standard'):
        scaler = preprocessing.StandardScaler()
        scaler.fit(train_data) 
        train_data = scaler.transform(train_data)
        test_data = scaler.transform(test_data)
        return train_data, test_data
        
    if(type == 'min_max'):
        min_max_scaler = preprocessing.MinMaxScaler(feature_range=(0, 1))  
        min_max_scaler.fit(train_data) 
        train_data = min_max_scaler.transform(train_data)
        test_data = min_max_scaler.transform(test_data)
        return train_data, test_data
        
    if(type == 'l1'): 
        train_data /= np.sum(abs(train_data), axis=1, keepdims=True)
        test_data /= np.sum(abs(test_data), axis=1, keepdims=True)
        return train_data, test_data
        
    if(type == 'l2'): 
        train_data /= np.sqrt(np.sum((train_data) ** 2, axis=1, keepdims=True))
        test_data /= np.sqrt(np.sum((test_data) ** 2, axis=1, keepdims=True))
        return train_data, test_data    
        

def svm_classifier(train_data, train_labels, test_data, c):
    linear_svm_model = svm.SVC(C=c, kernel='linear')
    linear_svm_model.fit(train_data, train_labels)
    predicted_labels_train = linear_svm_model.predict(train_data)
    predicted_labels_test = linear_svm_model.predict(test_data)
    return predicted_labels_train, predicted_labels_test


data_path = '../data0/'
train_images = np.loadtxt(data_path + 'train_images.txt')
train_labels = np.loadtxt(data_path + 'train_labels.txt', 'float')
test_images = np.loadtxt(data_path + 'test_images.txt')
test_labels = np.loadtxt(data_path + 'test_labels.txt', 'float')     
   
for label in train_labels:
    label = int(label)

for label in test_labels:
    label = int(label)

scaled_training_data, scaled_test_data = normalize_data(train_images, test_images, type='standard')
 
predicted_labels_train, predicted_labels_test = svm_classifier(scaled_training_data, train_labels, scaled_test_data, c=1)

print("Training accuracy using STD normalization: ", sm.accuracy_score(predicted_labels_train, train_labels))
print("Test accuracy using STD normalization: ", sm.accuracy_score(predicted_labels_test, test_labels))
 
