#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:acc attach,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int *)malloc(sizeof(int));
    *host_ptr = rand() % 100;

    int *device_ptr;
    acc_malloc(&device_ptr, sizeof(int));
    acc_attach(&device_ptr);
    *device_ptr = *host_ptr;
    acc_detach(&device_ptr);

    int *host_ptr_after = (int *)malloc(sizeof(int));
    acc_attach(&device_ptr);
    *host_ptr_after = *device_ptr;
    acc_detach(&device_ptr);

    if (*host_ptr != *host_ptr_after){
        err = 1;
    }

    free(host_ptr);
    free(host_ptr_after);
    acc_free(device_ptr);

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