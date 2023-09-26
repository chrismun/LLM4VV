#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct firstprivate clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int N = 1000;
    real_t *a = (real_t *)malloc(N * sizeof(real_t));
    real_t *b = (real_t *)malloc(N * sizeof(real_t));
    real_t *c = (real_t *)malloc(N * sizeof(real_t));

    for (int x = 0; x < N; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc kernels firstprivate(a, b, N)
    {
        #pragma acc loop
        for (int x = 0; x < N; ++x) {
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < N; ++x) {
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

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