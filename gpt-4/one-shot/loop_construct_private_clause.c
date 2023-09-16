#include "acc_testsuite.h"
#ifndef T2
// T2: loop,private,V:2.5-2.7
int test2() {
    int err = 0;
    srand(SEED);
    real_t* a = (real_t*)malloc(n * sizeof(real_t));
    real_t* b = (real_t*)malloc(n * sizeof(real_t));
    real_t temp;
    
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc kernels 
        {
            #pragma acc loop private(temp)
            for (int x = 0; x < n; ++x) {
                temp = a[x];
                b[x] = temp;
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test2();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}