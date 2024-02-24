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
    acc_attach(&device_ptr);
    device_ptr = host_ptr;

    int *host_ptr_copy = (int *)malloc(sizeof(int));
    *host_ptr_copy = 20;

    acc_detach(&device_ptr);
    device_ptr = host_ptr_copy;

    if (*host_ptr != 10){
        err = 1;
    }

    acc_detach_finalize(&device_ptr);

    free(host_ptr);
    free(host_ptr_copy);

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