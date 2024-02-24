#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_array = (int*)malloc(10 * sizeof(int));
    int *device_array = NULL;

    // Initialize host array
    for(int i = 0; i < 10; i++) {
        host_array[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_array[0:10])
    {
        // Allocate device array
        device_array = (int*)acc_malloc(10 * sizeof(int));

        // Copy data to device
        #pragma acc update device(device_array[0:10])

        // Use no_create clause
        #pragma acc data no_create(device_array[0:10])
        {
            // Check if device array is not created
            if(device_array == NULL) {
                err = 1;
            }
        }
    }

    // Free device array
    acc_free(device_array);

    // Free host array
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