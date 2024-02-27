#include "acc_testsuite.h"
#ifndef T1
//T1:acc attach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    // Declaring a pointer variable for device memory
    int* devPtr;

    // Allocating memory on a device to the pointer
    #pragma acc enter data create(devPtr[0:10])

    // Attaching the device pointer to a variable on the host
    acc_attach((h_void **)&devPtr);

    // Performing operations with the attached device pointer variable
    #pragma acc parallel loop present(devPtr[0:10])
    for (int x = 0; x < 10; ++x){
        devPtr[x] = 1;
    }
    
    // Removing the pointer from the device without freeing memory
    #pragma acc exit data delete(devPtr[0:10])
    
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