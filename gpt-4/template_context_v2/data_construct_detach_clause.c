#include "acc_testsuite.h"

#ifndef T1
#define T1
int test1() {
    int err = 0;
    srand(SEED);
    int N = 1000;
    float* x = (float*)malloc(N*sizeof(float));

    #pragma acc data copyin(x[0:N]) detach(x)
    {
        #pragma acc parallel loop present(x)
        for (int i = 0; i < N; i++) {
            x[i] = (float)(rand()) / RAND_MAX;
        }
        #pragma acc update host(x) attach(x)
    }

    for (int i = 0; i < N; i++) {
        if (x[i] < 0 || x[i] > 1) {
            err = 1;
            break;
        }
    }

    free(x);
    return err;
}
#endif

int main() {
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