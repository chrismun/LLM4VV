#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SEED 12345
#define n 1000
#define PRECISION 0.00001

#ifndef REAL_T
#define REAL_T double
#endif

typedef REAL_T real_t;

// Utility function to check CUDA errors
static void checkCudaErrorAux(const char *file, unsigned line, const char *statement, cudaError_t err){
    if (err == cudaSuccess) return;
    fprintf(stderr, "CUDA error at %s:%d: %s (%d) \"%s\"\n", file, line, cudaGetErrorString(err), err, statement);
    exit(1);
}

#define CUDA_CHECK_RETURN(value) checkCudaErrorAux(__FILE__,__LINE__, #value, value)

// CUDA kernel to be used with OpenACC host_data construct
__global__ void addKernel(real_t *device_a, real_t *device_b, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        device_b[i] = device_a[i] + 1;
    }
}

#ifndef T1
// T1:host_data,use_device,V:1.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    real_t *a, *b;
    real_t *device_a, *device_b;
    
    a = (real_t *)malloc(n * sizeof(real_t));
    b = (real_t *)malloc(n * sizeof(real_t));
    
    if (!a || !b) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    CUDA_CHECK_RETURN(cudaMalloc((void **)&device_a, n*sizeof(real_t)));
    CUDA_CHECK_RETURN(cudaMalloc((void **)&device_b, n*sizeof(real_t)));
    CUDA_CHECK_RETURN(cudaMemcpy(device_a, a, n*sizeof(real_t), cudaMemcpyHostToDevice));

    #pragma acc host_data use_device(device_a, device_b)
    {
        addKernel<<<(n + 255) / 256, 256>>>(device_a, device_b, n);
    }

    CUDA_CHECK_RETURN(cudaMemcpy(b, device_b, n*sizeof(real_t), cudaMemcpyDeviceToHost));

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - (a[x] + 1)) > PRECISION) {
            err += 1;
        }
    }

    CUDA_CHECK_RETURN(cudaFree(device_a));
    CUDA_CHECK_RETURN(cudaFree(device_b));
    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}