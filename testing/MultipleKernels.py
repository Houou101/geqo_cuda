import pycuda.driver as cuda
import numpy as np
from pycuda.compiler import SourceModule
import pycuda.autoinit

mod = SourceModule("""
__global__ void add_one(int *data) {
    int idx = threadIdx.x;
    data[idx] += 1;
}

__global__ void square(int *data) {
    int idx = threadIdx.x;
    data[idx] *= data[idx];
}
""")

add_one = mod.get_function("add_one")
square = mod.get_function("square")

data = np.array([1, 2, 3, 4], dtype=np.int32)
gpu_data = cuda.mem_alloc(data.nbytes) # Speicher auf gpu reservieren
cuda.memcpy_htod(gpu_data, data)

# Erst addiere, dann quadriere
add_one(gpu_data, block=(4,1,1)) # 4 Threads in einem Block
square(gpu_data, block=(4,1,1))

cuda.memcpy_dtoh(data, gpu_data) # kopiert Daten zurück zu cpu
print("Result:", data)
