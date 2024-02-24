#include <iostream>
#include <openacc.h>

#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 100;
    int *host_array = new int[size];
    int *device_array;

    // Initialize host array
    for(int i = 0; i < size; i++) {
        host_array[i] = i;
    }

    // Allocate device memory
    device_array = (int*)acc_malloc(size * sizeof(int));

    // Copy host array to device
    #pragma acc data copyin(host_array[:size]) copyout(device_array[:size])
    {
        // Modify device array
        #pragma acc kernels present(device_array[:size]) no_create(host_array[:size])
        for(int i = 0; i < size; i++) {
            device_array[i] = host_array[i] * 2;
        }
    }

    // Check if host array is not modified
    for(int i = 0; i < size; i++) {
        if(host_array[i] != i) {
            err = 1;
            break;
        }
    }

    // Free device memory
    acc_free(device_array);
    delete[] host_array;

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}