#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Adjust these values as needed, they're example sizes and precision.
#define n 1000
#define PRECISION 0.001
#define SEED 12345

typedef float real_t; // Change this type if testing with different data types.

#ifndef T1
// T1:kernels,data,data-region,copy,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));

    // Initialize the array with some test data.
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    // Use the copy clause to manage data for the duration of this region.
    #pragma acc data copy(a[0:n])
    {
        // Inside this kernels region, modify the array in parallel.
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * 2; // Example computation, modify as needed.
            }
        }
    }

    // Verify that modifications made on the device are reflected back on the host.
    for (int x = 0; x < n; ++x){
        real_t expected = (rand() / (real_t)(RAND_MAX / 10)) * 2;
        if (fabs(a[x] - expected) > PRECISION){
            err += 1;
        }
    }

    free(a);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;

#ifndef T1
    for(int x = 0; x < 1; ++x){ // Simplified loop for demonstration; adjust as needed.
        failed = test1();
        if (failed != 0){
            failcode |= 1; // Set specific bit for this test failure.
            break; // Early exit on failure for simplification.
        }
    }
#endif

    if (failcode == 0) {
        printf("Test passed: OpenACC copy clause implementation verified.\n");
    } else {
        printf("Test failed: Issues detected with OpenACC copy clause implementation.\n");
    }

    return failcode;
}