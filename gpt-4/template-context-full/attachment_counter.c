#include "openacc.h"
#include "acc_testsuite.h"

#ifndef T1
/*T1:attachment counter, V: 2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    
    //Allocate and initialize a pointer
    int *ptr = (int*) malloc(sizeof(int));
    *ptr = 10;

    // Check that device pointer points to NULL initially
    if (acc_deviceptr(ptr) != NULL){
        err = 1;
    }

    // Attach pointer to device
    #pragma acc enter data create(ptr[0:1])

    // Check that device pointer points to a valid address after attach
    if (acc_deviceptr(ptr) == NULL){
        err = 1;
    }

    // Detach pointer from device
    #pragma acc exit data delete(ptr[0:1])

    // Check that device pointer points to NULL after detach
    if (acc_deviceptr(ptr) != NULL){
        err = 1;
    }

    free(ptr);

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