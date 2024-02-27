#include "acc_testsuite.h"
#ifndef T1
// T1:kernels,data,data-region,V:1.0-2.7

// This function checks if data is properly marked as residing on the device
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_device;
    real_t *b_device;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Using 'declare' directive with 'device_resident' clause to tell the compiler
    // that the given data should live on the device for the duration of the program.
    #pragma acc declare device_resident(a_device, b_device)

    #pragma acc data create(a_device[0:n], b_device[0:n])
    {
        #pragma acc update device(a[0:n]) // copying host to device
        {
            #pragma acc parallel loop
            for (int x = 0; x < n; ++x){
                a_device[x] = a[x]; // initialize a_device with values from a
            }
        }
        
        // Perform operation on device-resident data
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            b_device[x] = a_device[x]; // copying data within the device
        }
        
        #pragma acc update host(b[0:n]) // copying device to host after computation
        {
            #pragma acc parallel loop
            for (int x = 0; x < n; ++x){
                b[x] = b_device[x]; // copying data back to host from device memory
            }
        }
    }

    // Verification
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1() + failed;
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}