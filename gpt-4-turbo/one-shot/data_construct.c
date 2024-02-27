#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"  // Assuming this header provides necessary macros and seed

#ifndef T2  // Additional test marker
//T2:kernels,data,data-region,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));  // Different array to demonstrate partial overlap

    // Initialize arrays with different values
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 100);
        c[x] = -1;  // Initialize with a different placeholder
    }

    // Modify and copy out a subsection of the 'a' array.
    #pragma acc data copyin(a[0:n/2])
    {
        #pragma acc kernels copyout(a[n/4:n/4])
        {
            #pragma acc loop
            for (int x = n/4; x < 3*n/4; ++x){
                a[x] *= 2;  // Example modification, doubling the value.
            }
        }
    }

    // Validation
    for (int x = n/4; x < 3*n/4; ++x){
        if (fabs(a[x] - (c[x] * 2)) > PRECISION){  // c remains unchanged, hence using as baseline
            err += 1;
        }
    }

    free(a);
    free(c);

    return err;
}
#endif

int main(){
    int failcode = 0;

#ifndef T1
    if (test_suite_run(test1)) { failcode |= (1 << 0); }
#endif

#ifndef T2
    if (test_suite_run(test2)) { failcode |= (1 << 1); }  // Execute the additional test
#endif

    return failcode;
}

// Assuming 'test_suite_run' is an abstraction to handle the execution and possible repetition of tests,
// and handles memory allocation and freeing, if not, the user should adapt it accordingly.