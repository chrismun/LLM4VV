#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *host_array = (int *)malloc(sizeof(int)*100);
    int *device_array = (int *)malloc(sizeof(int)*100);
    bool use_gpu = false; // Initially set to not use GPU

    // Simulated GPU operation using host_data construct if clause
    for (int i = 0; i < 100; ++i) {
        host_array[i] = rand() % 100;
    }
    
    #pragma acc data copyin(host_array[0:100]) copyout(device_array[0:100])
    {
        #pragma acc host_data use_device(device_array) if(use_gpu)
        {
            // Emulate a device operation
            for (int i = 0; i < 100; ++i){
                device_array[i] = host_array[i] * 2; // Dummy operation
            }
        }
    }

    for (int i = 0; i < 100; ++i){
        if (device_array[i] != host_array[i] * 2 && use_gpu) { // Should not be equal when use_gpu is false
            err++;
        }
        else if (use_gpu == false && device_array[i] != 0) { // Device array should remain unmodified
            err++;
        }
    }

    free(host_array);
    free(device_array);
    
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}