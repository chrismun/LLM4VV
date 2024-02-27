#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Assuming n is defined. For illustration, let's define it as 1024.
#define n 1024
// Precision for floating-point comparison
#define PRECISION 0.001
// Seed for random number generation - ensuring determinism
#define SEED 12345
// Number of times the test is run to ensure reliability
#define NUM_TEST_CALLS 10

typedef float real_t; // Defining real_t as float for this example

int main() {
    int failcode = 0;

    real_t* a = (real_t*)malloc(n * sizeof(real_t));
    real_t* b = (real_t*)malloc(n * sizeof(real_t));

    // Populate `a` with random values and initialize `b` to 0
    srand(SEED);
    for (int i = 0; i < n; ++i) {
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = 0;
    }

    // Use OpenACC kernels construct with copyout clause
    #pragma acc kernels copyout(b[0:n])
    for (int i = 0; i < n; ++i) {
        b[i] = a[i];
    }

    // Check for correctness
    int errors = 0;
    for (int i = 0; i < n; ++i) {
        if (fabs(b[i] - a[i]) > PRECISION) {
            errors++;
        }
    }

    free(a);
    free(b);

    // Print the result
    if (errors > 0) {
        printf("Test failed with %d errors.\n", errors);
        failcode = 1;
    } else {
        printf("Test passed successfully.\n");
    }

    return failcode;
}