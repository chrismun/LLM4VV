#include "acc_testsuite.h"

//T1:testing parallel and kernels constructs of num_workers clause
int test1() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel num_workers(4)
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = a[x]*2;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - a[x]*2) > PRECISION){
            err += 1;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}