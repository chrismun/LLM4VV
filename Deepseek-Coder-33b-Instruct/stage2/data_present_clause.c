#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;
    int size = 100;
    int *host_data = (int*)malloc(size * sizeof(int));
    int *device_data = NULL;

    // Initialize host data
    for(int i = 0; i < size; i++) {
        host_data[i] = i;
    }

    // Allocate device memory
    device_data = (int*)acc_malloc(size * sizeof(int));

    // Copy data to device
    #pragma acc data copyin(host_data[0:size]) copyout(device_data[0:size])
    {
        // Copy data from host to device
        #pragma acc update device(device_data[0:size])

        // Check if data is present in device memory
        #pragma acc data present(device_data[0:size])
        {
            // If data is not present in device memory, err will be set to 1
            #pragma acc kernels
            for(int i = 0; i < size; i++) {
                if(device_data[i] != i) {
                    err = 1;
                    break;
                }
            }
        }
    }

    // Free device memory
    acc_free(device_data);

    // Free host memory
    free(host_data);

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