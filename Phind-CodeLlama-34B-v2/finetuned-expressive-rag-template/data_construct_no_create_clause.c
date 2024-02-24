#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));

    #pragma acc data copy(a[0:10]) no_create(b[0:10])
    {
        #pragma acc kernels
        {
            for (int x = 0; x < 10; ++x){
                a[x] = x * 2;
                b[x] = x * 3;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        if (a[x] != x * 2){
            err += 1;
        }
        if (b[x] != x * 3){
            err += 1;
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