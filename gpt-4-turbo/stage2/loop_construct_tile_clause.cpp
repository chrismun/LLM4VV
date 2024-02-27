#include <iostream>
#include <stdlib.h> // For rand(), srand()
#include <openacc.h> // Necessary for OpenACC directives

#ifndef T1
// T1: loop construct, tile clause, V: 2.7-3.3
int test1(){
    int err = 0;
    srand(42); // Fixed seed for reproducibility.

    const int dim = 64; // Matrix dimensions, chosen for simplicity.
    float A[dim][dim];
    float B[dim][dim];
    float C[dim][dim]; // Result matrix.

    // Initialize matrices A and B with random values.
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            A[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            B[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }
    }

    // Perform matrix addition using OpenACC with a tile clause.
    // Using tile sizes that are divisors of the matrix dimensions for simplicity.
    #pragma acc parallel loop tile(16,16)
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // Verify the result of the addition, checking for errors.
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            if (abs((A[i][j] + B[i][j]) - C[i][j]) > 1e-5) { // Allow a small margin of error for floating-point comparison.
                err++;
            }
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

    // Since it's a simple test case with deterministic input, one test call should be sufficient to validate.
    failed = test1();
    if (failed != 0){
        failcode = 1; // Marking test as failed
      
        std::cout << "Test failed with " << failed << " errors." << std::endl;
    } else {
        std::cout << "Test passed." << std::endl;
    }

    return failcode;
}