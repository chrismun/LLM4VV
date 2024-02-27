#include "acc_testsuite.h"
#ifndef T1
//T1:{loop_construct_device_type},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 10000;
    float a[size], b[size];
    float sum = 0.0, correct_sum = 0.0;

    // Initialize arrays
    for(int i = 0; i < size; ++i){
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
        correct_sum += a[i] * b[i];
    }

    #pragma acc parallel loop device_type(host) reduction(+:sum)
    for(int i = 0; i < size; ++i){
        sum += a[i] * b[i];
    }

    if(fabs(sum - correct_sum) > 1e-5){
        err += 1;
    }

    sum = 0.0; // Reset sum for GPU test
    // Now test with GPU, if available
    #pragma acc parallel loop device_type(nvidia) reduction(+:sum)
    for(int i = 0; i < size; ++i){
        sum += a[i] * b[i];
    }

    if(fabs(sum - correct_sum) > 1e-5){
        err += 1;
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