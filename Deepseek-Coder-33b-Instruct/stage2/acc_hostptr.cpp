#include <stdlib.h>
#include <openacc.h>

#define N 100

int test1(){
    int err = 0;
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data;

    // Allocate device memory
    device_data = (int*)acc_malloc(N * sizeof(int));

    // Initialize host data
    for(int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    acc_memcpy_to_device(device_data, host_data, N * sizeof(int));

    // Get host pointer
    int *host_ptr = (int*)acc_hostptr(device_data);

    // Check if host pointer is the same as host data
    for(int i = 0; i < N; i++) {
        if(host_ptr[i] != host_data[i]) {
            err = 1;
            break;
        }
    }

    // Free device memory
    acc_free(device_data);

    // Free host memory
    free(host_data);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = test1();

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}