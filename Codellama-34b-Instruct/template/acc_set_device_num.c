#include "acc_testsuite.h"

//T1:acc set device num,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Set the device number to a random value
    int device_num = rand() % 10;

    // Set the device number using the acc_set_device_num() function
    acc_set_device_num(device_num);

    // Check that the device number was set correctly
    if (acc_get_device_num() != device_num) {
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure it passes consistently
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if (failed != 0){
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}