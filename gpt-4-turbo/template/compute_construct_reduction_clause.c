#include "acc_testsuite.h"
#ifndef T1
//T1:compute,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int test_size = 1024;
    int *a = (int*)malloc(test_size * sizeof(int));
    int host_sum = 0, device_sum = 0;

    // Initialize test data
    for(int i = 0; i < test_size; ++i) {
        a[i] = rand() % 100;  // Random values between 0 and 99
        host_sum += a[i];
    }

    // Apply reduction using OpenACC
#pragma acc data copyin(a[0:test_size])
    {
#pragma acc parallel reduction(+:device_sum)
        {
            for(int i = 0; i < test_size; ++i) {
                device_sum += a[i];
            }
        }
    }

    // Compare results
    if(host_sum != device_sum) {
        err += 1;
    }

    free(a);
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