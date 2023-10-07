#include "acc_testsuite.h"

#ifndef T1
//T1:acc copyin,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int *data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Copy the data to the device
    int *d_data = (int *)acc_copyin(data, sizeof(int) * 10);

    // Check that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (d_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory
    acc_free(d_data);

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