#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,data,data-region,V:2.6
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for(int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Creating a data region around the computation to copy in 'a' and copy out 'b'
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        // Initiating an asynchronous operation and detaching it with 'detach' clause
        void *handle;
        #pragma acc kernels async(0) detach(handle)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x];
            }
        }
        // Synchronize the asynchronous operation
        #pragma acc wait(0) on(handle)
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
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}