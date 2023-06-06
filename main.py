import time
import math
import random
import hashlib
import os
import sys
    
def md5(string):
    md5_hash = hashlib.md5()
    md5_hash.update(string.encode('utf-8'))
    md5_hex = md5_hash.hexdigest()
    return md5_hex

def fib(n):
    if(n == 0 or n == 1):
        return n 
    else:
        return fib(n-1) + fib(n-2)      

def test_geometry(vector3_1, vector3_2, radius1, radius2, radius3):
    distance = math.sqrt((vector3_2[0] - vector3_1[0])**2 + (vector3_2[1] - vector3_1[1])**2 + (vector3_2[2] - vector3_1[2])**2)
    distance_between_centers = math.sqrt((vector3_2[0] - vector3_1[0])**2 + (vector3_2[1] - vector3_1[1])**2 + (vector3_2[2] - vector3_1[2])**2)
    sphere_volume = (4/3) * math.pi * (radius3**3)

def load_data():
    current_dir = os.path.dirname(sys.argv[0])
    data_file_path = os.path.join(current_dir, 'data.txt')
    try:
        with open(data_file_path, "r") as f:
            data = f.read()
            return data
    except FileNotFoundError:
        print("Arquivo 'data.txt' não encontrado.")


start_fib = time.time()
result_fib = fib(32)
finish_fib = time.time()

vector3_1 = (random.uniform(1, 10), random.uniform(1, 10), random.uniform(1, 10))
vector3_2 = (random.uniform(1, 10), random.uniform(1, 10), random.uniform(1, 10))
radius1 = random.uniform(1, 10)
radius2 = random.uniform(1, 10)
radius3 = random.uniform(1, 10)
start_geometry = time.time()
for i in range(1000000):
    result_geometry = test_geometry(vector3_1, vector3_2, radius1, radius2, radius3)
finish_geometry = time.time()

start_data = time.time()
data = load_data()
finish_data = time.time()
print(f"data hash = {md5(data)}")

print("python:")
print(f"teste fib: {round((finish_fib-start_fib)*1000, 0)} ms")
print(f"teste geometry: {round((finish_geometry-start_geometry)*1000, 0)} ms")
print(f"teste data: {round((finish_data-start_data)*1000, 0)} ms\n")