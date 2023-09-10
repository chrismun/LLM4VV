#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int k = 0;

    real_t false_margin = pow(exp(1), log(.5)/n);

    data = (double *)malloc(n * sizeof(double));
    data_copy = (double *)malloc(n * sizeof(double));
    for (int x = 0; x < n; ++x){
        data[x] = rand() / (real_t)(RAND_MAX / 10);
        data_copy[x] = data[x];
    }

    #pragma acc parallel present(data[0:n]) firstprivate(data_copy[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            data[x] = data[x] + data_copy[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(data[x] - (data_copy[x] + data_copy[x] * false_margin)) > PRECISION * data[x]){
            err = 1;
        }
    }

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