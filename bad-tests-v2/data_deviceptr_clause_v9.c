#include "acc_testsuite.h"
#ifndef T1
/*T1:data deviceptr clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a, *b, *c, *d;
    real_t *dev_a, *dev_b, *dev_c, *dev_d;
    int n = 100;

    a = (real_t *)malloc(n * sizeof(real_t));
    b = (real_t *)malloc(n * sizeof(real_t));
    c = (real_t *)malloc(n * sizeof(real_t));
    d = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc data deviceptr(a, b, c, d)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                c[x] = a[x] + b[x];
            }

            #pragma acc update device(c[0:n])
        }

        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                d[x] = c[x] * 2;
            }

            #pragma acc update self(d[0:n])
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n])

    for (int x = 0; x < n; ++x) {
        if (fabs(d[x] - (c[x] * 2)) > PRECISION) {
            err = 1;
            break;
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