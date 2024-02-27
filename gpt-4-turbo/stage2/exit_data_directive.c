#include "acc_testsuite.h"
#ifndef T1
//T1:exit data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int size = 1024;
    int *a = (int *)malloc(size * sizeof(int));
    // Initializing array
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100;
    }

    // Enter data to device
#pragma acc enter data copyin(a[0:size])

    // Modify data on device
#pragma acc parallel loop present(a[0:size])
    for(int i = 0; i < size; ++i){
        a[i] += 1;
    }

    // Exit data - delete from device
#pragma acc exit data delete(a[0:size])

    // Attempt to use the device data (should fail if exit data works)
#pragma acc parallel loop present(a[0:size])
    for(int i = 0; i < size; ++i){
        a[i] += 1; // This line should not execute successfully
    }

    // Verification
    // Since the data was deleted, changes made on the device should not be visible here.
    for(int i = 0; i < size; ++i){
        if(a[i] != (rand() % 100) + 1){
            err = 1; //If any data is different from expected, mark as error.
            break;
        }
    }

    free(a);
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