#include "acc_testsuite.h"
#ifndef T1
/*T1:declare directive device_resident clause,V:2.0-2.7*/

int test1(){
    // Initialization
    int err = 0;
    srand(SEED);

    // Declare a device-resident array
    #pragma acc declare device_resident(arr)
    int arr[100];

    // Fill the array with some values
    #pragma acc parallel loop
    for(int i = 0; i < 100; i++){
        arr[i] = i;
    }

    // Check the array's values
    int hostArr[100];
    #pragma acc update host(hostArr)
    for(int i = 0; i < 100; i++){
        if(hostArr[i]!=i)
            err = 1;
    }

    return err;
}
#endif

int main(){
    // Initialise
    int failcode = 0;
    int failed;
#ifndef T1
    // Perform the test multiple times
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    // Check the test results
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    // Return the overall test result
    return failcode;
}