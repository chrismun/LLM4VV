#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 1000 // Array size
#define SEED 12345
#define PRECISION 0.00001

typedef float real_t; // Define real_t as float for this example

int test_create_clause(){
    int err = 0;
    real_t *a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_device = (real_t *)malloc(n * sizeof(real_t)); // Using extra space for clarity

    // Initialize host array
    srand(SEED);
    for (int i = 0; i < n; ++i){
        a_host[i] = i;
    }

    // Use the create clause to allocate memory on the device without initializing it
    #pragma acc data create(b_device[0:n])
    {
        // Populate the array on the device
        #pragma acc parallel loop copyin(a_host[0:n]) copyout(b_device[0:n])
        for (int i = 0; i < n; ++i){
            b_device[i] = a_host[i] + 5; // Arbitrary operation to modify the data
        }
    }

    // Verification
    for (int i = 0; i < n; ++i){
        if (fabs(b_device[i] - (a_host[i] + 5)) > PRECISION){
            err++;
        }
    }

    free(a_host);
    free(b_device);

    return err;
}

int main(){
    int failcode = 0;
    int failed = test_create_clause();
    if (failed != 0){
        failcode = 1; // Using a simple flag for demonstration
        printf("Test FAILED with %d errors.\n", failed);
    } else {
        printf("Test PASSED.\n");
    }
    return failcode;
}