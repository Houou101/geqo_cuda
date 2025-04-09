import pycuda.autoinit
import pycuda.driver as cuda
import numpy as np
from pycuda.compiler import SourceModule

class CudaMutation:
    def __init__(self):
        self.module = SourceModule("""
        __global__ void swap_genes(int *genes, int swap1, int swap2) {
            int temp = genes[swap1];
            genes[swap1] = genes[swap2];
            genes[swap2] = temp;
        }
        """)
        self.swap = self.module.get_function("swap_genes")

    def mutate(self, genes, i, j):
        genes = np.array(genes, dtype=np.int32)
        gpu_genes = cuda.mem_alloc(genes.nbytes)
        cuda.memcpy_htod(gpu_genes, genes)

        self.swap(gpu_genes, np.int32(i), np.int32(j), block=(1,1,1))

        cuda.memcpy_dtoh(genes, gpu_genes)
        return genes

# Anwendung
mutator = CudaMutation()
print(mutator.mutate([9,8,7,6,5], 0, 4))
