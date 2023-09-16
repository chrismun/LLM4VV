#include <stdio.h>
#include <openacc.h>

void openACC_GPU_copyout(float *A, size_t size) {
    acc_init(acc_device_nvidia);

    float* gpuA = (float*) acc_malloc(sizeof(float)*size);

    acc_map_data(A, gpuA, sizeof(float)*size);
    printf("Data mapping completed\n");

    acc_memcpy_to_device(gpuA, A, sizeof(float)*size);
    printf("Memcpy to device completed\n");

    acc_delete(gpuA, sizeof(float)*size);
    printf("Data deleted from device\n");

    acc_unmap_data(A);
    printf("Unmapping data completed\n");
    acc_shutdown(acc_device_nvidia);

}

int main() {
    const int size = 100;
    float A[size];   

    for(int i=0; i<size; i++) {
        A[i] = i+1.0f;
    }

    openACC_GPU_copyout(A, size);
    return 0;
}