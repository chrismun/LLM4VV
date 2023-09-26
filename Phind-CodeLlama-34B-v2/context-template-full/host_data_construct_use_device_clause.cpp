#include "acc_testsuite.h"
#ifndef T1
/*T1:host_data construct use_device clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = 0.0;
    }

    #pragma acc host_data use_device(a, b, c, d)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                c[x] = a[x] + b[x];
            }
        }

        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                d[x] = a[x] - b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION) {
            err += 1;
        }
        if (fabs(d[x] - (a[x] - b[x])) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);

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