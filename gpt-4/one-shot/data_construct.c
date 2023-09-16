#include "acc_testsuite.h"

// The test1 function tests the OpenACC copyout clause
// in a kernels region. The function allocates two arrays
// 'a' and 'b', fills 'a' with random values and zero-initializes 'b'.
// Then, it copies into the device the array 'a', and inside a kernels region,
// it indicates that the array 'b' should be copied out from the device to the host.
int test1(){
    int err = 0;
    srand(SEED);
    
    // Allocate arrays 'a' and 'b'
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    // Fill 'a' with random values and 'b' with 0's
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }
    
    // Copy into device the array 'a'
    #pragma acc data copyin(a[0:n])
    {
        // Indicate that array 'b' should be copied out from the device to the host
        #pragma acc kernels copyout(b[0:n])
        {
            // Perform copies from 'a' to 'b'
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }
    
    // Check for any discrepancies in the copied arrays
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }
    
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    // Perform multiple test calls to test1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    return failcode;
}