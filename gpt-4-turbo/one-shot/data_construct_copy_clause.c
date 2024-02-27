#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// Define these constants for your test
#define n 1000
#define SEED 123
#define PRECISION 0.001

typedef float real_t; // Define real_t as needed, float is used here for simplicity

// Test function for copy clause
int test_copy_clause(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * ref = (real_t *)malloc(n * sizeof(real_t));

    // Initialize the arrays
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
        ref[x] = a[x];  // Copy 'a' to 'ref' for verification
    }

    // Use OpenACC to copy 'a' into the device, compute, and copy 'b' back
    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x] * 2;  // Example computation
            }
        }
    }

    // Verification
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - ref[x] * 2) > PRECISION){ // Verify b equals 2*a (as per our example computation)
            err += 1;
        }
    }

    free(a);
    free(b);
    free(ref);
    return err;
}

int main(){
    int errors = test_copy_clause();
    if (errors){
        printf("Test FAILED with %d errors.\n", errors);
    } else {
        printf("Test PASSED.\n");
    }
    return errors;
}