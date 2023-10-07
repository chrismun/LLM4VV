#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct wait clause,V:2.0-2.7*/
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

    #pragma acc data copy(a[0:n], b[0:n], c[0:n], d[0:n])
    {
        #pragma acc kernels wait(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                c[x] = a[x] + b[x];
            }
        }

        #pragma acc kernels wait(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                d[x] = a[x] - b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION || fabs(d[x] - (a[x] - b[x])) > PRECISION) {
            err = 1;
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