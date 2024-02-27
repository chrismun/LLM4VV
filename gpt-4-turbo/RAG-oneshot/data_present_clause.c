#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SEED 12345
#define n 1000
#define PRECISION 0.00001
typedef float real_t;

// Make sure to define or include your own acc_testsuite.h correctly.
// The example assumes basic macros/constants are defined there,
// like NUM_TEST_CALLS for the number of repetitions.

#ifndef T1
// T1: data, structured-data-region, V:1.0-2.7
int test1(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
        c[x] = a[x] + 1; // Avoid exact initial match to verify copy
    }

    // Explicit data region ensuring 'a' is present on the device.
    #pragma acc data copy(a[0:n])
    {
        // Attempt to use 'a' assuming it is present.
        // The present clause here serves as an assertion of our assumption.
        #pragma acc parallel present(a[0:n]) copyout(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x]; // Operation using the present data
            }
        }

        // Attempt to use 'c' without explicitly ensuring it's present.
        // This should lead to a runtime error if not handled properly as 'c' is not guaranteed to be present.
        #pragma acc parallel present(c[0:n]) // Deliberate runtime error if 'c' is not present
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + 1; 
            }
        }
    }

    // Verify correctness of operation on 'a' and 'b'
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
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
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        // Test to verify 'present' handling
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    printf("Test %s\n", (failcode == 0) ? "PASSED" : "FAILED");
    return failcode;
}