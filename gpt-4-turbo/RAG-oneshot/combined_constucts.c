#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED 12345
#define NUM_ELEMENTS 1024
#define PRECISION 0.001

// Function prototypes
int testParallelLoop();

int main() {
    int failCode = 0;

    // Execute the parallel loop test function
    if (testParallelLoop() != 0) {
        failCode |= 1;  // Use bitwise OR to set the 1st bit indicating failure.
    }

    // Print the result based on the failCode
    if (failCode == 0) {
        printf("All OpenACC combined construct tests passed.\n");
    } else {
        printf("Some OpenACC combined construct tests failed.\n");
    }

    return failCode;
}

int testParallelLoop() {
    int errors = 0;
    srand(SEED);
    float *a = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    float *b = (float *)malloc(NUM_ELEMENTS * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        a[i] = rand() / (float)(RAND_MAX / 100);
        b[i] = 0.0;  // Initialize the array to zeros
    }

    // Applying OpenACC parallel loop
#pragma acc parallel loop copyin(a[0:NUM_ELEMENTS]) copyout(b[0:NUM_ELEMENTS])
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        b[i] = a[i] * 2;  // Simple operation to verify the correctness
    }

    // Check for correctness
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        if (fabs(b[i] - (a[i] * 2)) > PRECISION) {
            errors++;
        }
    }

    free(a);
    free(b);

    // Return the number of errors
    return errors;
}