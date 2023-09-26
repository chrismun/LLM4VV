#include <iostream>
#include <cstdlib>
#include <cmath>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    int vector_length = 4;
    int num_workers = 10;
    int num_vectors = 100;

    // Initialize the vector
    float* vector = new float[num_vectors];
    for (int i = 0; i < num_vectors; i++) {
        vector[i] = (float)rand() / RAND_MAX;
    }

    // Create the kernels construct
    #pragma acc kernels vector_length(vector_length)
    {
        // Loop over the vectors
        #pragma acc loop
        for (int i = 0; i < num_vectors; i++) {
            // Perform some computation on the vector
            vector[i] = vector[i] * 2.0f;
        }
    }

    // Check the results
    for (int i = 0; i < num_vectors; i++) {
        if (vector[i] != 2.0f * (float)rand() / RAND_MAX) {
            err = 1;
            break;
        }
    }

    // Clean up
    delete[] vector;

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}