#include "acc_testsuite.h"

#ifndef T1
//T1:serial,device-only,V:2.6-2.7
int test1() {

    int err = 0;
    srand(SEED);
    real_t* a = (real_t*)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX/10);
    }

    #pragma acc data copyin(a[0:n])  // copy the data to the device
    {
        #pragma acc serial  // specify the work should be done serially, 
                            // this is particularly useful when there is an inherent data dependency 
                            // that makes parallelization not possible or less efficient 
        {
            for (int x = 0; x < n; ++x) {
                a[x] = a[x] * 2.0;
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(a[x] - 2.0*(rand() / (real_t)(RAND_MAX/10))) > PRECISION) {
            err += 1;
        }
    }

    free(a);

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
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}