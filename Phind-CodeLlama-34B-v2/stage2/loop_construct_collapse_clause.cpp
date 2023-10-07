#include "acc_testsuite.h"
#ifndef T1
/*T1:loop construct collapse clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(1024 * sizeof(real_t));
    real_t * b = (real_t *)malloc(1024 * sizeof(real_t));

    for (int x = 0; x < 1024; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copy(a[0:1024], b[0:1024])
    {
        #pragma acc parallel loop collapse(2)
        for (int x = 0; x < 32; ++x) {
            for (int y = 0; y < 32; ++y) {
                int idx = x * 32 + y;
                b[idx] = a[idx] * 2.0;
            }
        }
    }

    for (int x = 0; x < 1024; ++x) {
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