#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define n 10000
#define SEED 45545
#define PRECISION 1e-5

int test_attach(){
    int err = 0;
    srand(SEED);
    double * a = (double *)malloc(n * sizeof(double));
    double *original_a = a; // Holding the original pointer for later free() to avoid undefined behavior

    // Initialize array with some random values
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (double)(RAND_MAX / 10);
    }

    // Explicitly manage the data with enter data and the attach clause
    #pragma acc enter data create(a[0:n])
    #pragma acc parallel attach(a)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = a[x] * 2.0; // Doubling each element
        }
    }
    #pragma acc exit data copyout(a[0:n]) // fetching the modified data to host

    // Checking the results
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (original_a[x] * 2.0)) > PRECISION){ // original_a[x] * 2 because we doubled the values in the device
            err += 1;
        }
    }

    free(original_a); // Clean up
    return err;
}

int main(){
    int failcode = 0;
    int failed = test_attach();
    if (failed != 0){
        failcode = 1; // Indicating that there was an error
        printf("Test FAILED with %d errors.\n", failed);
    } else {
        printf("Test PASSED.\n");
    }
    return failcode;
}