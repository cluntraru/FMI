import pandas as pd
import numpy as np
import sklearn.metrics as sm
from sklearn import svm
from sklearn import preprocessing
from os import listdir


def svm_classifier(train_data, train_labels, test_data, c):
    svm_model = svm.SVC(C = c, kernel = "linear")
    svm_model.fit(train_data, train_labels)
    pred_train_labels = svm_model.predict(train_data)
    pred_test_labels = svm_model.predict(test_data)
    return pred_train_labels, pred_test_labels


def normalize_data(train_data, test_data, type="standard"):
    if type == "standard":
        scaler = preprocessing.StandardScaler()
        scaler.fit(train_data)
        train_data = scaler.transform(train_data)
        test_data = scaler.transform(test_data)
        return train_data, test_data
    elif type == "min_max":
        min_max_scaler = preprocessing.MinMaxScaler(feature_range = (0, 1))
        min_max_scaler.fit(train_data)
        train_data = min_max_scaler.transform(train_data)
        test_data= min_max_scaler.transform(test_data)
    elif type == "l1":
        train_data /= np.sum(abs(train_data), axis = 1, keepdims = True)
        test_data /= np.sum(abs(test_data), axis= 1, keepdims = True)
        return train_data, test_data
    elif type == "l2":
        train_data /= np.sqrt(np.sum((train_data) ** 2, axis = 1, keepdims= True))
        test_data /= np.sqrt(np.sum((test_data) ** 2, axis = 1, keepdims = True))
        return train_data, test_data

    return train_data, test_data


def reading_avg(reading):
    avg = [0, 0, 0]
    for i in range(len(reading)):
        for j in range(3):
            avg[j] += reading[i][j]

    avg[0] /= len(reading)
    avg[1] /= len(reading)
    avg[2] /= len(reading)
    return avg


def process_reading(reading):
    ''' Turn accelerometer reading into a 3-tuple '''
    return reading_avg(reading) 


def data_from_dir(data_path, dir_name):
    data = np.array([]) 
    files = listdir(data_path + dir_name)
    files = sorted(files)
    ids = np.array([])

    for file_name in files:
        curr_data = np.genfromtxt(data_path + dir_name + file_name, delimiter = ",") 
        curr_id, _, _ = file_name.partition(".")
        reading = process_reading(curr_data)
        data = np.append(data, reading, axis = 0)
        ids = np.append(ids, curr_id)

    data = np.reshape(data, (len(files), 3))
    return data, ids


# Main
data_path = ""
# data_path = "/content/gdrive/My Drive/Colab Notebooks/project_data/project/"
train_labels = np.genfromtxt(data_path + "train_labels.csv", delimiter = ",", skip_header = 1)
train_labels = train_labels[:,1]
# print(train_labels)

train_data, train_ids = data_from_dir(data_path, "train/")
test_data, test_ids = data_from_dir(data_path, "test/")

scaled_train_data, scaled_test_data = normalize_data(train_data, test_data, "standard")
pred_train_labels, pred_test_labels = svm_classifier(scaled_train_data, train_labels, scaled_test_data, 1) 

out_file_name = data_path + "output.csv"
out_file = open(out_file_name, "w") 

print(pred_train_labels, train_labels)
print("Training accuracy: ", sm.accuracy_score(pred_train_labels, train_labels))

out_file.write("id,class\n")
for i in range(len(pred_test_labels)):
    out_file.write(str(test_ids[i]) + "," + str(pred_test_labels[i]) + "\n")

