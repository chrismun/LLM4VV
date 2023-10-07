#include "acc_testsuite.h"
#ifndef T1
//T1:acc attach,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_ptr, *device_ptr;
    host_ptr = (int *)malloc(sizeof(int));
    *host_ptr = 10;

    #pragma acc enter data copyin(host_ptr[0:1])
    device_ptr = host_ptr;
    #pragma acc attach(device_ptr[0:1])

    // Check if the pointer has been updated to point to the device copy
    if (device_ptr != host_ptr){
        err = 1;
    }

    #pragma acc detach(device_ptr[0:1])
    #pragma acc exit data delete(host_ptr[0:1])
    free(host_ptr);

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