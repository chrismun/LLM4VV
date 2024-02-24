#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc attach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int *)malloc(sizeof(int));
    *host_ptr = 10;

    int *device_ptr;
    #pragma acc enter data copyin(host_ptr[0:1])
    #pragma acc enter data create(device_ptr[0:1])

    #pragma acc kernels present(host_ptr, device_ptr)
    {
        device_ptr[0] = host_ptr[0];
    }

    #pragma acc update host(device_ptr[0:1])

    if (device_ptr[0] != 10) {
        err = 1;
    }

    #pragma acc attach(device_ptr[0:1])
    #pragma acc update device(device_ptr[0:1])
    *host_ptr = 20;
    #pragma acc update host(device_ptr[0:1])

    if (device_ptr[0] != 20) {
        err = 1;
    }

    #pragma acc detach(device_ptr[0:1])
    #pragma acc update device(device_ptr[0:1])
    *host_ptr = 30;
    #pragma acc update host(device_ptr[0:1])

    if (device_ptr[0] != 20) {
        err = 1;
    }

    #pragma acc detach_finalize(device_ptr[0:1])
    #pragma acc update device(device_ptr[0:1])
    *host_ptr = 40;
    #pragma acc update host(device_ptr[0:1])

    if (device_ptr[0] != 40) {
        err = 1;
    }

    #pragma acc exit data delete(host_ptr, device_ptr)

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