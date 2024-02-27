#include "acc_testsuite.h"
#ifndef T1
//T1:loop,construct,reduction,combined-constructs,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = new real_t[10 * n];
    real_t * b = new real_t[10 * n];
    real_t * c = new real_t[10 * n];
    real_t * totals = new real_t[10];

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }


    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copyout(c[0:10*n]) copy(totals[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop worker gang private(totals)
            for (int x = 0; x < 10; ++x) {
                totals[x] = 0.0;
            }

            #pragma acc loop worker gang 
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = a[x] + b[x];
            }

            #pragma acc loop worker gang reduction(+:totals)
            for (int x = 0; x < 10 * n; ++x) {
                totals[x/10] += c[x];
            }

            #pragma acc loop worker gang 
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = c[x] / totals[x/10];
            }
        }
    }

    for (int x = 0; x < 10; ++x) {
        totals[x] = 0.0;
    }

    for (int x = 0; x < 10 * n; ++x) {
        totals[x/10] += a[x] + b[x];
    }

    for (int x = 0; x < 10 * n; ++x) {
        if (fabs(c[x] - ((a[x] + b[x]) / totals[x/10])) > 3*PRECISION) {
            err += 1;
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