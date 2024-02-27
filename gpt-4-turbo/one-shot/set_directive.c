#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Assuming acc_testsuite.h defines SEED, n, and PRECISION among others.
#include "acc_testsuite.h"

#ifndef T2
// T2:set,V:1.0-2.7
int test_set_directive(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }
    
    // Set the number of gangs and vector length
    #pragma acc set num_gangs(128) vector_length(32)
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x];
            }
        }
    }
    
    // Verification step
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

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_set_directive();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1); // Adjust bit position for error flag.
    }
#endif
    return failcode;
}