#include <cstdlib>
#include <iostream>
#include <openacc.h>

#ifndef SEED
#define SEED 123
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = new int[size];
    int *b = new int[size];

    // Initialize arrays
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Using OpenACC copy clause
    #pragma acc data copy(a[0:size], b[0:size])
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i){
            // Simple operation to validate copy
            b[i] = a[i] + 1;
        }
    }

    // Check if the operation was successful
    for(int i = 0; i < size; ++i){
        if(b[i] != a[i] + 1){
            err++;
        }
    }

    delete[] a;
    delete[] b;

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if(failcode == 0) {
        std::cout << "Test Passed: OpenACC copy clause works as expected." << std::endl;
    } else {
        std::cout << "Test Failed: OpenACC copy clause does not work as expected, errors: " << failed << std::endl;
    }

    return failcode;
}