#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:parallel construct wait clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(2023); // Use a fixed seed for reproducibility

    // Define data size and create test data arrays
    int dataSize = 10000;
    float *data1 = (float*)malloc(dataSize * sizeof(float));
    float *data2 = (float*)malloc(dataSize * sizeof(float));

    // Initialize test data
    for (int i = 0; i < dataSize; ++i) {
        data1[i] = (float)rand() / RAND_MAX;
        data2[i] = 0.0f; // Will be used to store results
    }

    // First parallel region to process data1
#pragma acc parallel loop copy(data1[0:dataSize])
    for (int i = 0; i < dataSize; ++i) {
        data1[i] = data1[i] * 2.0f; // Arbitrary computation
    }

#pragma acc wait

    // Second parallel region that depends on the completion of the first
#pragma acc parallel loop copyin(data1[0:dataSize]) copy(data2[0:dataSize])
    for (int i = 0; i < dataSize; ++i) {
        data2[i] = data1[i] + 1.0f; // Second arbitrary computation, depending on data1
    }

    // Verification: data2 should now hold (original_data1 * 2) + 1
    for (int i = 0; i < dataSize; ++i) {
        float expected = ((float)rand() / RAND_MAX) * 2.0f + 1.0f;
        if (abs(data2[i] - expected) > 0.0001f) { // Simple floating point comparison
            err++;
        }
    }

    free(data1);
    free(data2);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;

#ifndef T1
    failed = 0;
    for (int x = 0; x < 5; x++) { // Example: Number of test calls could be adjusted accordingly
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}