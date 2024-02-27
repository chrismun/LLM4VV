#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:kernels,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t)); // Original data
    real_t * b = (real_t *)malloc(n * sizeof(real_t)); // Data to mirror 'a' in device
    real_t * c = (real_t *)malloc(n * sizeof(real_t)); // Verification array

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x]; // Initially copy 'a' to 'b'
        c[x] = 0;
    }

    #pragma acc data copyin(b[0:n])
    {
        // Intentionally using 'present' clause, expecting 'b' to be already present
        #pragma acc kernels present(b[0:n]) copyout(c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - a[x]) > PRECISION){
            ++err;
            break; // Error found, no need to check further
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
        failed += test1();
    }
    if (failed != 0){
        failcode |= (1 << 0); // Use bitwise OR to set specific bit for failure code
    }
#endif
    return failcode;
}