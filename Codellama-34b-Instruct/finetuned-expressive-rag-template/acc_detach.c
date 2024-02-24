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

    int *device_ptr;

    #pragma acc enter data copyin(host_ptr[0:1])
    #pragma acc attach(device_ptr, host_ptr)

    #pragma acc detach(device_ptr)

    #pragma acc update device(host_ptr[0:1])

    if (*host_ptr != 10){
        err = 1;
    }

    #pragma acc detach(device_ptr)

    #pragma acc exit data delete(host_ptr)

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