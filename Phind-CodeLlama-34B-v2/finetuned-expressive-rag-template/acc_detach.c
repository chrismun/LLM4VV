#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc detach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int *)malloc(sizeof(int));
    *host_ptr = 10;

    int *device_ptr = (int *)acc_malloc(sizeof(int));
    acc_attach(&device_ptr, host_ptr);
    acc_detach(&device_ptr);

    int *host_ptr_after_detach = (int *)acc_deviceptr(device_ptr);

    if (host_ptr_after_detach != host_ptr) {
        err = 1;
    }

    acc_free(device_ptr);
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