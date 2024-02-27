#include "acc_testsuite.h"

#ifndef T1
//T1:host_data,if_present,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    // Initializing arrays
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x] + 1;  // Ensure b[] does not equal a[] initially
    }
    
    // Copying data to the device explicitly
    #pragma acc enter data copyin(a[0:n])

    // Attempting to modify data on the device conditionally using if_present
    #pragma acc host_data use_device(a) if_present
    {
        // This block is supposed to execute if a[] is present on the device
        for (int x = 0; x < n; ++x){
            a[x] = a[x] + 1;  // Modifying data, should reflect on the device if present
        }
    }

    // Copying data from the device to b[] to check if modifications took place
    #pragma acc update host(b[0:n]) if_present

    // Verifying the operations
    for (int x = 0; x < n; ++x){
        // Since b[] was initially set to a[]+1 and we further increment a[] inside the device,
        // b[] should now equal a[] if and only if the 'if_present' clause worked as expected.
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:n])

    free(a);
    free(b);
    
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}