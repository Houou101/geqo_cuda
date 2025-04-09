import pycuda.autoinit
import pycuda.driver as cuda
import numpy as np
from pycuda.compiler import SourceModule

stream1 = cuda.Stream()
stream2 = cuda.Stream()
# Multiplikation von Arrays
mod = SourceModule("""
__global__ void scale(int *data, int factor) {
    int idx = threadIdx.x;
    data[idx] *= factor;
}
""")
scale = mod.get_function("scale")

data1 = np.array([1, 2, 3, 4], dtype=np.int32)
data2 = np.array([5, 6, 7, 8], dtype=np.int32)
gpu_data1 = cuda.mem_alloc(data1.nbytes) # Speicher auf gpu reservieren
gpu_data2 = cuda.mem_alloc(data2.nbytes)

cuda.memcpy_htod_async(gpu_data1, data1, stream1)
cuda.memcpy_htod_async(gpu_data2, data2, stream2)

scale(gpu_data1, np.int32(2), block=(4,1,1), stream=stream1) # Kernel starten
scale(gpu_data2, np.int32(3), block=(4,1,1), stream=stream2)

cuda.memcpy_dtoh_async(data1, gpu_data1, stream1)
cuda.memcpy_dtoh_async(data2, gpu_data2, stream2)

stream1.synchronize()
stream2.synchronize()

print("data1:", data1)
print("data2:", data2)
