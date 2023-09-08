#include "acc_testsuite.h"

#ifndef T1
//T1:data construct,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate memory on the device
    int *a;
    acc_malloc(a, sizeof(int));

    // Copy data from local memory to device memory
    acc_copyin(a, sizeof(int));

    // Launch a kernel to perform a calculation on the data
    acc_parallel(a, sizeof(int));

    // Copy data back from device memory to local memory
    acc_copyout(a, sizeof(int));

    // Free the memory on the device
    acc_free(a);

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