#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define NUM_ELEMENTS 1024

int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(NUM_ELEMENTS * sizeof(int));
    int *b = (int *)malloc(NUM_ELEMENTS * sizeof(int));

    for (int x = 0; x < NUM_ELEMENTS; ++x){
        a[x] = rand() % 10;
        b[x] = 0;
    }

    #pragma acc data copy(a[0:NUM_ELEMENTS], b[0:NUM_ELEMENTS])
    {
        #pragma acc kernels
        {
            for (int x = 0; x < NUM_ELEMENTS; ++x){
                b[x] = a[x] * a[x];
            }
        }
    }

    for (int x = 0; x < NUM_ELEMENTS; ++x){
        if (b[x] != a[x] * a[x]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

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