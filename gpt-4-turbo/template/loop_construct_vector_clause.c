#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int array_size = 1024;
    float a[array_size], b[array_size];
    float scalar = 3.14f;

    // Initialize arrays
    for(int i = 0; i < array_size; i++){
        a[i] = (float)rand()/(float)(RAND_MAX/2) - 1.0f; // Random float between -1.0 and 1.0
        b[i] = 0.0f;
    }

    // Target computation on device
    #pragma acc parallel num_workers(128)
    #pragma acc loop vector(128)
    for (int i = 0; i < array_size; ++i) {
        b[i] = a[i] * scalar;
    }

    // Verify results
    for(int i = 0; i < array_size; i++){
        if (abs(b[i] - (a[i] * scalar)) > 1e-5) {
            err++;
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