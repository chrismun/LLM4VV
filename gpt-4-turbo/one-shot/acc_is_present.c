#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// Assuming acc_testsuite.h defines common utilities like real_t, n, SEED, PRECISION, and possibly NUM_TEST_CALLS.
#include "acc_testsuite.h"

#ifndef TEST_COPYOUT
// TEST_COPYOUT:kernels,data,data-region,V:1.0-2.7
int test_copyout(){
    int err = 0;
    srand(SEED);
    real_t *input = (real_t *)malloc(n * sizeof(real_t));
    real_t *output = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; ++i){
        input[i] = rand() / (real_t)(RAND_MAX / 10);
        output[i] = 0;
    }

    #pragma acc data copyin(input[0:n])
    {
        #pragma acc kernels copyout(output[0:n])
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                output[i] = input[i];
            }
        }
    }

    for (int i = 0; i < n; ++i){
        if (fabs(output[i] - input[i]) > PRECISION){
            err += 1;
        }
    }

    free(input);
    free(output);
    return err;
}
#endif

int main(){
    int errorCode = 0;
    int failCount = 0;

#ifndef TEST_COPYOUT
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failCount += test_copyout();
    }
    if (failCount != 0){
        errorCode |= 1;
    }
#endif
    if (errorCode) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
    return errorCode;
}