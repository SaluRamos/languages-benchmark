import time
import math
import random
from hashlib import md5
import os
import sys

def fib(n):
    if(n == 0 or n == 1):
        return n
    else:
        return fib(n-1) + fib(n-2)

def test_geometry(vector3_1, vector3_2, radius):
    distance = math.sqrt((vector3_2[0] - vector3_1[0])**2 + (vector3_2[1] - vector3_1[1])**2 + (vector3_2[2] - vector3_1[2])**2)
    distance_between_centers = math.sqrt((vector3_2[0] - vector3_1[0])**2 + (vector3_2[1] - vector3_1[1])**2 + (vector3_2[2] - vector3_1[2])**2)
    sphere_volume = (4/3) * math.pi * (radius**3)
    return distance + distance_between_centers + sphere_volume

def md5(string):
    md5_hash = md5()
    md5_hash.update(string.encode('utf-8'))
    md5_hex = md5_hash.hexdigest()
    return md5_hex

def load_data():
    current_dir = os.path.dirname(sys.argv[0])
    try:
        data_file_path = os.path.join(current_dir, '../data.txt')
        with open(data_file_path, "r") as f:
            data = f.read()
            return data
    except:
        data_file_path = os.path.join(current_dir, '../../../data.txt')
        with open(data_file_path, "r") as f:
            data = f.read()
            return data

# import fib
sys.path.append('build/lib.win-amd64-cpython-311')
sys.path.append('../../build/lib.win-amd64-cpython-311')
sys.path.append('python/build/lib.win-amd64-cpython-311')
import salubenchmark

start_fib = time.time()
result_fib = salubenchmark.fib(40)
# result_fib = fib(40)
finish_fib = time.time()
print(f"result fib = {result_fib}")


geometry_sum = 0
start_geometry = time.time()
# for i in range(10000000):
    # vector3_1 = (random.uniform(1, 10), random.uniform(1, 10), random.uniform(1, 10))
    # vector3_2 = (random.uniform(1, 10), random.uniform(1, 10), random.uniform(1, 10))
    # radius = random.uniform(1, 10)
    # geometry_sum += test_geometry(vector3_1, vector3_2, radius)
# salubenchmark.fastgeometry(vector3_1, vector3_2, radius)
salubenchmark.fastgengeometry()
finish_geometry = time.time()

start_data = time.time()
data = load_data()
finish_data = time.time()
print(f"data hash = {md5(data)}")
print("python 3.11.4:")
print(f"teste fibonacci: {math.floor((finish_fib-start_fib)*1000)} ms")
print(f"teste calculos geométricos: {math.floor((finish_geometry-start_geometry)*1000)} ms")
print(f"teste leitura de arquivo 90MB: {math.floor((finish_data-start_data)*1000)} ms\n")