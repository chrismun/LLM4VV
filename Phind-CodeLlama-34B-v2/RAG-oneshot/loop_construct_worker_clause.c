#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define N 1024

int test_worker_clause(){
    int i;
    int err = 0;
    real_t *a = (real_t *)malloc(N * sizeof(real_t));
    real_t *b = (real_t *)malloc(N * sizeof(real_t));

    for(i = 0; i < N; i++){
        a[i] = i;
        b[i] = 0.0;
    }

    #pragma acc data copy(a[0:N], b[0:N])
    {
        #pragma acc parallel
        {
            #pragma acc loop worker
            for(i = 0; i < N; i++){
                b[i] = a[i] * 2.0;
            }
        }
    }

    for(i = 0; i < N; i++){
        if(fabs(b[i] - (i * 2.0)) > PRECISION){
            err++;
        }
    }

    return err;
}

int main(){
    int i;
    int err = 0;
    int failed = 0;

    for(i = 0; i < NUM_TEST_CALLS; i++){
        failed = failed + test_worker_clause();
    }

    if(failed != 0){
        err = err + (1 << 0);
    }

    return err;
}