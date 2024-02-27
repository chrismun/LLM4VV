#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T_DEFAULT
// T_DEFAULT:kernels,loop,data,constructs,default,V:1.0-2.7
int test_default_none(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }
    
    #pragma acc data copyin(a[0:n]) copyout(c[0:n])
    {
        #pragma acc kernels default(none) copyin(a[0:n]) copyout(c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                c[x] = a[x] + 1;
            }
        }
    }
    
    for (int x = 0; x < n; ++x) {
        if (fabs(c[x] - (a[x] + 1)) > PRECISION) {
            err += 1;
        }
    }
    
    free(a);
    free(c);
    return err;
}
#endif

#ifndef T_DEFAULT_PRESENT
// Test for verifying 'default(present)' clause
// Add a similar test function here if needed...
#endif

int main() {
    int failcode = 0;
    int failed;
    
    #ifndef T_DEFAULT
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_default_none();
    }
    if (failed != 0) {
        failcode += (1 << 0);
        printf("Test for 'default(none)' failed.\n");
    } else {
        printf("Test for 'default(none)' passed.\n");
    }
    #endif
    
    // Additional tests for other default clause types (like 'default(present)') can go here...

    return failcode;
}