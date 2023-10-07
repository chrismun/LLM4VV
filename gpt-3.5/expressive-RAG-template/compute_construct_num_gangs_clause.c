#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100000;
    int a[n], b[n], c[n];
    int *dev_a, *dev_b, *dev_c;

    // Allocate device memory
    #pragma acc data create(a[0:n], b[0:n], c[0:n])
    {
        // Initialize data on the host
        for (int i = 0; i < n; i++) {
            a[i] = rand() % 100;
            b[i] = rand() % 100;
        }

        // Allocate device memory
        dev_a = (int *)acc_malloc(n * sizeof(int));
        dev_b = (int *)acc_malloc(n * sizeof(int));
        dev_c = (int *)acc_malloc(n * sizeof(int));

        // Copy data from host to device
        #pragma acc update device(a[0:n], b[0:n])

        // Compute the sum of corresponding elements of a and b on the device
        #pragma acc kernels copyin(a[0:n], b[0:n]) copyout(c[0:n]) num_gangs(32)
        {
            #pragma acc loop gang
            for (int i = 0; i < n; i++) {
                c[i] = a[i] + b[i];
            }
        }

        // Copy result back to host
        #pragma acc update self(c[0:n])

        // Verify the result
        for (int i = 0; i < n; i++) {
            if (c[i] != a[i] + b[i]) {
                err = 1;
                break;
            }
        }

        // Free device memory
        acc_free(dev_a);
        acc_free(dev_b);
        acc_free(dev_c);
    }

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