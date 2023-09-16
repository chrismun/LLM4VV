#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define N 1024
#define TILE_SIZE 64

int test_kernels_loop_tile_clause(){
    int i;
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(N * sizeof(real_t));
    real_t * b = (real_t *)malloc(N * sizeof(real_t));

    for (i = 0; i < N; ++i){
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop tile(TILE_SIZE)
            for (i = 0; i < N; ++i){
                b[i] = a[i];
            }
        }
    }

    for (i = 0; i < N; ++i){
        if (fabs(b[i] - a[i]) > PRECISION){
            err += 1;
        }
    }

    return err;
}

int main(){
    int i;
    int err = 0;
    int failed = 0;

    for (i = 0; i < NUM_TEST_CALLS; ++i){
        failed = failed + test_kernels_loop_tile_clause();
    }

    if (failed != 0){
        err = err + (1 << 0);
    }

    return err;
}