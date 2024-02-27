#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define n 1024
#define PRECISION 0.0001

real_t test_var[n]; // Global variable to apply declare directive

#pragma acc declare create(test_var) // Applying create clause to the global variable

int test_create_clause() {
    int err = 0;
    srand(SEED);
    real_t *host_var = (real_t *)malloc(n * sizeof(real_t));
    
    for (int i = 0; i < n; ++i) {
        host_var[i] = rand() / (real_t)RAND_MAX;
    }

    // Introducing an implicit data region where `test_var` is involved.
    #pragma acc parallel copy(test_var)
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i) {
            test_var[i] = host_var[i];
        }
    }

    /* Bring the data back to host to verify the correctness of 
     * the operation performed on the device.
     */
    #pragma acc update host(test_var[0:n])
    
    for (int i = 0; i < n; ++i) {
        if (fabs(test_var[i] - host_var[i]) > PRECISION) {
            err++;
        }
    }

    free(host_var);

    return err;
}

int main() {
    int error_count = test_create_clause();

    if (error_count != 0) {
        printf("Test FAILED with %d errors.\n", error_count);
        return 1;
    } else {
        printf("Test PASSED.\n");
        return 0;
    }
}