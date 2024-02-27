#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3

// Declare a global variable with the device_resident clause
#pragma acc declare create(x) device_resident
int x = 0;

int test1(){
    int err = 0;
    srand(SEED);

    // Setting value on host
    x = rand() % 100;

    // Using the variable on the device
    #pragma acc parallel num_gangs(1) vector_length(1) 
    {
        #pragma acc loop gang vector 
        for (int i = 0; i < 1; ++i) {
            x += 1; // Modify x on the device
        }
    }

    // Check if the modification made on the device is visible on the host
    if(x != (rand() % 100) + 1){
        err += 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}