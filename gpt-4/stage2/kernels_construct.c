#include "acc_testsuite.h"
#include <stdlib.h>

#define N 100

#pragma acc routine seq
void mult(float *a, float *b, int i){
    a[i] = a[i] * b[i];
}

int test(){
    int err = 0;
    srand(SEED);
    float *a = (float*) malloc(N * sizeof(float));
    float *b = (float*) malloc(N * sizeof(float));

    for (int i = 0; i < N; ++i){
        a[i] = rand()/(float)RAND_MAX;
        b[i] = rand()/(float)RAND_MAX;
    }

    #pragma acc data copy(a[0:N]) copyin(b[0:N])
    {
        #pragma acc kernels
        {
            for (int i = 0; i < N; ++i){
                mult(a, b, i);
            }
        }
    }

    for (int i = 0; i < N; ++i){
        float expected_result = a[i] * b[i];
        if(fabs(a[i] - expected_result) > PRECISION) {
            err += 1;
        }
    }
    
    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}