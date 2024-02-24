#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data construct copyin clause,V:2.7-3.3
int test1(){
    int err = 0;
    int n = 10;
    int *host_array = (int*)malloc(n * sizeof(int));
    int *device_array;

    // Initialize host array
    for(int i = 0; i < n; i++) {
        host_array[i] = i;
    }

    // Allocate device memory
    device_array = (int*)acc_malloc(n * sizeof(int));

    // Copy data to device
    #pragma acc data copyin(host_array[:n])
    {
        // Copy data to device
        #pragma acc update device(device_array[:n])

        // Check if data was correctly copied
        for(int i = 0; i < n; i++) {
            if(device_array[i] != i) {
                err = 1;
                break;
            }
        }
    }

    // Free device memory
    acc_free(device_array);
    free(host_array);

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