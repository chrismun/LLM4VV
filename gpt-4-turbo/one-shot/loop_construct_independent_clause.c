#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 10000
#define SEED 12345
#define PRECISION 0.00001

typedef float real_t; // Using 'float' for simplicity. Can be 'double' for higher precision.

// Function prototype for test
int test_independent_loop();

int main() {
    int failcode = test_independent_loop();
    if (failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }
    return failcode;
}

int test_independent_loop() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *result = (real_t *)malloc(n * sizeof(real_t));

    // Initialize arrays
    for (int i = 0; i < n; ++i) {
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = rand() / (real_t)(RAND_MAX / 10);
        result[i] = 0;
    }

    // Parallel computation using OpenACC
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(result[0:n])
    {
        #pragma acc parallel loop independent
        for (int i = 0; i < n; ++i) {
            result[i] = a[i] + b[i];
        }
    }

    // Verify the computation
    for (int i = 0; i < n; ++i) {
        real_t expected = a[i] + b[i];
        if (fabs(result[i] - expected) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(result);

    return err;
}