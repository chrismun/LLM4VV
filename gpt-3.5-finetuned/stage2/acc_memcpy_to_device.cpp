#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy to device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Size of data
    const int size = 10;
    // Host arrays
    real_t* a = new real_t[size];
    // Loop over data
    for (int x = 0; x < size; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    // Device arrays
    real_t* a_device = new real_t[size];

    // Copy data to device
    acc_memcpy_to_device(a_device, a, size * sizeof(real_t));

    // Retrieve data on the device
    #pragma acc data deviceptr(a_device)
    {
        #pragma acc parallel loop
        for (int x = 0; x < size; ++x){
            a_device[x] = a_device[x] + 1;
        }
    }

    // Copy data back to host
    acc_memcpy_to_device(a, a_device, size * sizeof(real_t));

    // Loop over data
    for (int x = 0; x < size; ++x){
        if (fabs(a[x] - (a_device[x] - 1)) > PRECISION){
            err += 1;
        }
    }

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