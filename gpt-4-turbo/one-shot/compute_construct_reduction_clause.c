#include <stdlib.h>
#include <math.h>
#include <stdio.h>
// Assuming definitions for SEED, n, real_t, and PRECISION are provided
#include "acc_testsuite.h"

#ifndef T1
// T1:kernels,parallel,loop,reduction,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t total = 0;
    real_t acc_total = 0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        total += a[x]; // Calculating expected total
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel loop reduction(+:acc_total)
        for (int x = 0; x < n; ++x){
            acc_total += a[x];
        }
    }

    if (fabs(acc_total - total) > PRECISION){
        err += 1;
    }

    free(a);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    if (failcode) {
        printf("Some tests have failed.\n");
    } else {
        printf("All tests have passed.\n");
    }
    return failcode;
}