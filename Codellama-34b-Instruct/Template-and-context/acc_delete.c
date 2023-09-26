#include "acc_testsuite.h"

int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int *data = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Copy the data to the device
    acc_copyin(data, sizeof(int) * 10);

    // Delete the data from the device
    acc_delete(data, sizeof(int) * 10);

    // Check that the data has been deleted
    for (int i = 0; i < 10; i++) {
        if (data[i] != 0) {
            err = 1;
            break;
        }
    }

    free(data);
    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}