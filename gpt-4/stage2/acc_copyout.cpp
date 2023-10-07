#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#if !defined(T1)
/*T1:acc copyout,V:2.0-2.7*/
int test1(){
    int err = 0;
    size_t data_size = 1024;
    float* a = (float*) malloc(sizeof(float) * data_size);
    float* b = (float*) malloc(sizeof(float) * data_size);

    // Initialize data
    for (size_t i = 0; i < data_size; ++i) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = 0.0f;
    }

    // Copy to device
    acc_copyin(a, data_size * sizeof(float));

    // Perform computation on device
    #pragma acc parallel loop present(a, b)
    for (size_t i = 0; i < data_size; ++i) {
        b[i] = a[i] * 2.0f;
    }

    // Copy out from device
    acc_copyout(b, data_size * sizeof(float));

    // Validate results
    for (size_t i = 0; i < data_size; ++i) {
        if(b[i] != a[i] * 2.0f){
            err = 1;
            break;
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
#if !defined(T1)
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