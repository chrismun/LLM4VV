#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"
#ifndef T2
//T2:loop,V:2.6-2.7
int test_vector_clause(){
    int err = 0;
    srand(SEED);
    const int n = 1000; // Assuming array size to be 1000 for demonstration
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    // Initialize arrays
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0; // Initialize c with zeros
    }

    // Perform vectorized addition
    #pragma acc data copyin(a[0:n],b[0:n]) copyout(c[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop vector
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    // Verify correctness
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_vector_clause();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}