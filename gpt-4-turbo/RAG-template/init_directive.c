#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL)); 

    // Attempt to initialize the runtime for all available devices.
    // Use of the init directive:
#pragma acc init

    // After attempting initialization, try to execute a simple operation on the default device to check if init was successful.
    int data[10];
    int result = 1;

    // Generate test data
    for (int i = 0; i < 10; ++i) {
        data[i] = i + 1;
    }

    // Attempt a simple parallel operation
#pragma acc parallel loop reduction(+:result)
    for(int i = 0; i < 10; i++){
        result += data[i];
    }

    // Verification by result is not a direct method to check for success of init,
    // but an operation without a runtime initialization error indirectly indicates success.
    if (result == 56) {
        printf("Test passed. OpenACC init seems to work.\n");
    } else {
        printf("Test failed. OpenACC init might have issues.\n");
        err = 1; // Mark test as failed
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < 1; ++x){ // Assuming NUM_TEST_CALLS = 1 for simplicity in this example
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}