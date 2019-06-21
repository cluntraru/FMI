import pandas as pd
import numpy as np
import statistics as stats
import sklearn.metrics as sm
from sklearn import svm
from sklearn import preprocessing
from os import listdir
from random import randint


def svm_classifier(train_data, train_labels, test_data, c, gm):
    ''' Aplicarea efectiva a algoritmului SVM. '''
    svm_model = svm.SVC(C = c, kernel = "rbf", gamma = gm)
    svm_model.fit(train_data, train_labels)
    pred_train_labels = svm_model.predict(train_data)
    pred_test_labels = svm_model.predict(test_data)
    return pred_train_labels, pred_test_labels


def normalize_data(train_data, test_data, type="standard"):
    ''' Diferite tipuri de normalizare. Cea standard a fost singura care a dat
    rezultate. '''
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


def reading_abs_movement(reading):
    abs_move = [0, 0, 0]
    for i in range(1, len(reading)):
        for j in range(3):
            abs_move[j] += abs(reading[i][j] - reading[i - 1][j])

    return abs_move


def get_segment_values(segment):
    x_col = segment[:,0].tolist()
    y_col = segment[:,1].tolist()
    z_col = segment[:,2].tolist()
    x_col = np.sort(x_col)
    y_col = np.sort(y_col)
    z_col = np.sort(z_col)

    x_vals = [x_col[0], x_col[-1], x_col[len(x_col) // 2], stats.stdev(x_col), stats.variance(x_col)]
    y_vals = [y_col[0], y_col[-1], y_col[len(y_col) // 2], stats.stdev(y_col), stats.variance(y_col)]
    z_vals = [z_col[0], z_col[-1], z_col[len(z_col) // 2], stats.stdev(z_col), stats.variance(z_col)]
    return x_vals + y_vals + z_vals


def process_reading(reading):
    ''' Un reading este continutul unui fisier din directoarele train/test.
    Impartim un reading in segment_num segmente (partitii) si calculam niste
    metrice pe fiecare dintre ele in get_segment_values. '''
    processed_reading = np.array([])
    segment_num = 12
    segment_len = 150 // segment_num
    for segment_idx in range(segment_num - 1):
        segment = reading[segment_idx * segment_len : (segment_idx + 1) * segment_len][:]
        segment_vals = get_segment_values(segment)
        processed_reading = np.append(processed_reading, segment_vals, axis = 0)
   
    # Assuming that no readings are shorter than 135
    segment = reading[(segment_num - 1) * segment_len : len(reading)][:]
    segment_vals = get_segment_values(segment)
    processed_reading = np.append(processed_reading, segment_vals, axis = 0)
    
    processed_reading = processed_reading.flatten()
    return processed_reading
    

def data_from_dir(data_path, dir_name):
    ''' Folosim numpy pentru a citi din fisiere si a salva continutul in numpy arrays. '''
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

    # Number of numbers per x,y,z * 3 * number of blocks
    data = np.reshape(data, (len(files), 180))
    return data, ids


data_path = ""
train_labels = np.genfromtxt(data_path + "train_labels12.csv", delimiter = ",")
train_labels = train_labels[:,1]

# Citim datele de test si de antrenare
train_data, train_ids = data_from_dir(data_path, "train12/")
test_data, test_ids = data_from_dir(data_path, "train0/")

# Normalizare
scaled_train_data, scaled_test_data = normalize_data(train_data, test_data, "standard")
# Aplicarea algoritmului de SVM
pred_train_labels, pred_test_labels = svm_classifier(scaled_train_data, train_labels, scaled_test_data, 1, "scale") 

out_file_name = data_path + "output0.csv"
out_file = open(out_file_name, "w") 

# Calculam acuratetea estimata (am impartit train data in train0 si test0)
test_labels = np.genfromtxt(data_path + "test_labels0.csv", delimiter = ",", skip_header = 1)
test_labels = test_labels[:,1]

print(pred_train_labels, train_labels)
print("Training accuracy: ", sm.accuracy_score(pred_train_labels, train_labels))
#print("Test accuracy: ", sm.accuracy_score(pred_test_labels, test_labels))

out_file.write("id,class\n")
for i in range(len(pred_test_labels)):
    out_file.write(str(test_ids[i]) + "," + str(int(pred_test_labels[i])) + "\n")

