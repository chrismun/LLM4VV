#include <iostream>
#include <stdlib.h> // For srand() and rand()
#include <openacc.h> // Necessary for OpenACC runtime routines

#ifndef T1
// T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Assuming a global array that we will declare for OpenACC
    const int size = 1024;
    int *testArray;

    // Dynamically allocate memory for the testArray
    testArray = (int *)malloc(size * sizeof(int));

    // Initialize array
    for(int i = 0; i < size; ++i) {
        testArray[i] = rand(); // Populate with some random values
    }

#pragma acc data create(testArray[0:size])
    {
        // Modify the array in an OpenACC parallel region
#pragma acc parallel loop present(testArray[0:size])
        for(int i = 0; i < size; ++i) {
            testArray[i] += 1; // Simple operation to change the value
        }
    }

    // Verification step to check if the create clause worked as expected
    for(int i = 0; i < size; ++i) {
        if (testArray[i] != (initialValue[i] + 1)) { // Assuming initialValue stores the original values of testArray before modification
            err++;
        }
    }

    free(testArray); // Cleanup

    return err;
}

#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0); // Bit 0 set to 1 indicates failure in test1
    }
#endif

    return failcode;
}