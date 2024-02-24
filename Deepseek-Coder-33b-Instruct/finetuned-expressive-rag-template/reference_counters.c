#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int test1(){
    int err = 0;
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = NULL;

    // Initialize host data
    for(int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Allocate device memory
    #pragma acc enter data create(device_data[0:N])

    // Copy data to device
    #pragma acc update device(device_data[0:N])

    // Check if data is present on device
    for(int i = 0; i < N; i++) {
        if(device_data[i] != i) {
            err = 1;
            break;
        }
    }

    // Free device memory
    #pragma acc exit data delete(device_data[0:N])

    // Check if data is still present on device
    for(int i = 0; i < N; i++) {
        if(device_data[i] == i) {
            err = 1;
            break;
        }
    }

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