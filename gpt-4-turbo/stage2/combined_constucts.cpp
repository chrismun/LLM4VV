#include <iostream>
#include <stdlib.h> // For rand() and srand()

// Assuming acc_testsuite.h defines constants like SEED and NUM_TEST_CALLS. 
// Please define these if not included from the testsuite header.
const int SEED = 123;
const int NUM_TEST_CALLS = 100;
const int ARRAY_SIZE = 1024;

#ifndef T1
// T1:combined constructs,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    float a[ARRAY_SIZE];
    float b[ARRAY_SIZE];

    // Initialize arrays and set test conditions
    for(int i = 0; i < ARRAY_SIZE; ++i){
        a[i] = static_cast<float>(rand()) / RAND_MAX; // Random float between 0 and 1
        b[i] = 0.0f;
    }

    // Using the combined parallel loop construct to perform operations on the arrays in parallel
    #pragma acc parallel loop
    for(int i = 0; i < ARRAY_SIZE; ++i){
        b[i] = a[i] * 2.0f; // Example operation: simply doubling each element
    }

    // Verifying the operation
    for(int i = 0; i < ARRAY_SIZE; ++i){
        if(b[i] != a[i] * 2.0f){
            err += 1; // Error if the operation didn't proceed as expected
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        std::cout << "Test passed successfully!" << std::endl;
    } else {
        std::cout << "Test failed; error code: " << failcode << std::endl;
    }
    return failcode;
}