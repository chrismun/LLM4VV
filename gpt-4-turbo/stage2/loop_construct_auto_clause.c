#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef T1
//T1:loop construct auto clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(42); // Use a fixed seed for reproducibility

    int data[100];
    // Initialize with some values
    for (int i = 0; i < 100; ++i){
        data[i] = rand() % 100;
    }

    // Perform computation on the device
    #pragma acc kernels
    {
        // Using the auto clause
        #pragma acc loop auto
        for (int i = 0; i < 100; ++i){
            data[i] += 1;
        }
    }

    // Check the results; the increment should work on every element.
    for (int i = 0; i < 100; ++i){
        if (data[i] <= 0 || data[i] >= 101) { // Since we started with [0, 99] rand%100 and then added 1
            err++;
        }
    }
    return err;
}
#endif

int main(){
    int failcode = 0;
    #ifndef T1
    int failed = 0;
    const int NUM_TEST_CALLS = 10;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0); // Set bit 0 if failed
    }
    #endif
    return failcode;
}