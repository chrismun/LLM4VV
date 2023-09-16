#include "acc_testsuite.h"
#ifndef T1
#define T1 : 1.0-2.7
int test1() {
    int err = 0;
    int async = 5;  // Some async queue number
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    srand(SEED);
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 20);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel loop async(async)
        for (int x = 0; x < n; ++x) {
            b[x] = a[x];
        }

        #pragma acc wait(async)
    }
        
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

    #ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    
    if (failed != 0) {
        failcode = failcode | (1 << 0);
    }
    #endif

    return failcode;
}