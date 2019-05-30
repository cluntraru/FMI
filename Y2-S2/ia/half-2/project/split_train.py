import os
import subprocess

def copy_to_dir(dir_name, file_name):

def split_train(num):
    files = os.listdir("train")
    files = sorted(files)
    for i in range(num * 3000, (num + 1) * 3000):
        file = files[i]
        subprocess.run(["cp", file_name, dir_name])
        subprocess.run(["cp"

for i in range(3):
    split_train(i)
    
