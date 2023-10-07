#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define NUM_TEST_CALLS 1
#define SEED 123
#define N 1024
#define PRECISION 0.0001

int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(N * sizeof(real_t));
    real_t * b = (real_t *)malloc(N * sizeof(real_t));

    for (int x = 0; x < N; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copy(a[0:N])
    {
        #pragma acc kernels copy(b[0:N])
        {
            #pragma acc loop
            for (int x = 0; x < N; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < N; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}