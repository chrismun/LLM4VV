#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 1000;
    double *a = (double *)malloc(n * sizeof(double));
    double *b = (double *)malloc(n * sizeof(double));
    double sum = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (double)RAND_MAX;
        b[x] = rand() / (double)RAND_MAX;
    }

    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc parallel loop reduction(+:sum)
        for (int x = 0; x < n; ++x){
            sum += a[x] * b[x];
        }
    }

    double expected_sum = 0.0;
    for (int x = 0; x < n; ++x){
        expected_sum += a[x] * b[x];
    }

    if (fabs(sum - expected_sum) > PRECISION){
        err = 1;
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