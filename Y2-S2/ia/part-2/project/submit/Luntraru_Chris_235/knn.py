import pandas as pd
import numpy as np
from os import listdir

def distance(point_1, point_2):
    dist = 0
    for i in range(len(point_1)):
        dist += np.square(point_1[0] - point_2[0])
  
    return np.sqrt(dist)

def knn(train_data, train_labels, test_data, k):
    ''' train_data and test_data are dicts created from accelerometer readings
      
        train_labels and test_labels dicts
      
        all keys are ID
    '''

    test_labels = {}
    for test_key, test_avg in test_data.items():
        dist_list = [] # list of pairs (dist, train_id)
        for train_key, train_avg in train_data.items():
            dist_list.append([distance(train_avg, test_avg), int(train_key)]) 
      
        dist_list = sorted(dist_list)
    
        # Check the k nearest neighbours
        best_class = -1
        best_class_app = 0
        app = [0 for i in range(21)]
        for i in range(k):
            curr_id = dist_list[i][1]
            curr_class = train_labels[curr_id]
            app[curr_class] += 1
        
            if app[curr_class] > best_class_app:
                best_class_app = app[curr_class]
                best_class = curr_class
      
        test_labels[test_key] = best_class
    
    return test_labels


def data_from_dir(data_path, dir_name):
    data = {}
    files = listdir(data_path + dir_name)
    
    for file_name in files:
        curr_data = pd.read_csv(data_path + dir_name + file_name, sep=",", header=None)
        avg = [0, 0, 0]
        curr_id, _, _ = file_name.partition(".")
 
        # Calculate average accelerometer position in reading
        for i in range(len(curr_data)):
            for j in range(3):
                avg[j] += curr_data.loc[i, j]
  
        avg[0] /= len(curr_data)
        avg[1] /= len(curr_data)
        avg[2] /= len(curr_data)
        data[curr_id]= avg

    return data


data_path = ""
train_labels_list = pd.read_csv(data_path + "train_labels.csv", sep=",", header=0)
train_labels = {}
for i in range(len(train_labels_list)):
    train_labels[train_labels_list.loc[i, 'id']] = train_labels_list.loc[i, 'class']

train_data = {}

train_data = data_from_dir(data_path, "train/")
test_data = data_from_dir(data_path, "test/")

test_labels = knn(train_data, train_labels, test_data, 7)

out_file_name = data_path + "output.csv"
out_file = open(out_file_name, "w") 

out_file.write("id,class\n")
for test_id, test_class in test_labels.items():
    out_file.write(str(test_id) + "," + str(test_class) + "\n")

