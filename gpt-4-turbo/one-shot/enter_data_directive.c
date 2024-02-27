#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Define some constants for test
#define n 10000
#define SEED 12345
#define PRECISION 0.00001
typedef float real_t;

#ifndef T1
//T1:enter_data,data,data-region,V:1.0-2.7
int test_enter_data(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize 'a' with some values
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 100);
    }

    // Use enter data to copy 'a' to the device
    #pragma acc enter data copyin(a[0:n])

    // Perform computations on device
    #pragma acc parallel loop copyout(b[0:n])
    for (int x = 0; x < n; ++x){
        b[x] = a[x] + 1; // Simple operation to modify the value
    }

    // Checking if the operation was correctly applied
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x] + 1)) > PRECISION){
            err += 1;
        }
    }

    // Cleanup: Release device memory
    #pragma acc exit data delete(a[0:n])

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

    // Test the enter data directive
#ifndef T1
    failed = test_enter_data();
    if (failed != 0){
        failcode = failcode + (1 << 0);
        printf("Test for enter data directive failed with %d errors.\n", failed);
    } else {
        printf("Test for enter data directive passed.\n");
    }
#endif

    return failcode;
}