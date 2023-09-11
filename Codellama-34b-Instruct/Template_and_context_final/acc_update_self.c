#include "acc_testsuite.h"

#ifndef T1
//T1:acc update self,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int *data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Copy the data to the device
    acc_copyin(data, sizeof(int) * 10);

    // Update the data on the device
    acc_update_self(data, sizeof(int) * 10);

    // Check that the data on the device has been updated
    for (int i = 0; i < 10; i++) {
        if (data[i] != rand()) {
            err = 1;
            break;
        }
    }

    // Free the memory
    free(data);

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