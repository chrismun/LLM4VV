#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct vector_length clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int vector_length = 4; // Arbitrary vector length
    int N = 1000; // Array size
    real_t *a = (real_t *)malloc(N * sizeof(real_t));
    real_t *b = (real_t *)malloc(N * sizeof(real_t));

    for (int x = 0; x < N; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc kernels vector_length(vector_length)
    {
        #pragma acc loop
        for (int x = 0; x < N; ++x) {
            b[x] = a[x] * 2.0;
        }
    }

    for (int x = 0; x < N; ++x) {
        if (fabs(b[x] - (a[x] * 2.0)) > PRECISION) {
            err = 1;
            break;
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