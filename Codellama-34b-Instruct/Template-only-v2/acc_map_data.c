#include "acc_testsuite.h"

#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Map the data array to the device
    acc_map_data(data, 10, sizeof(int));

    // Create a compute construct
    acc_parallel(1, 10, 1);

    // Map the data array to the device again
    acc_map_data(data, 10, sizeof(int));

    // Check that the data array is mapped to the device
    for (int i = 0; i < 10; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

    // Unmap the data array from the device
    acc_unmap_data(data);

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