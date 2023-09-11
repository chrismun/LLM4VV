#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc detach,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int *)malloc(sizeof(int));
    *host_ptr = rand() % 100;

    int *device_ptr;
    acc_attach(&device_ptr);
    acc_copyin(host_ptr, sizeof(int));
    acc_detach(&device_ptr);

    int *host_ptr_after_detach = (int *)malloc(sizeof(int));
    acc_attach(&device_ptr);
    acc_copyout(host_ptr_after_detach, sizeof(int));
    acc_detach(&device_ptr);

    if (*host_ptr != *host_ptr_after_detach){
        err = 1;
    }

    free(host_ptr);
    free(host_ptr_after_detach);

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