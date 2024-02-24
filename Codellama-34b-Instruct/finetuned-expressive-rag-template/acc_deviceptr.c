#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc deviceptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int *)malloc(n * sizeof(int));
    int *device_data = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        host_data[x] = rand() % n;
    }

    acc_memcpy_to_device(device_data, host_data, n * sizeof(int));

    int *device_ptr = (int *)acc_deviceptr(host_data);

    if (device_ptr == NULL){
        err = 1;
    }

    for (int x = 0; x < n; ++x){
        if (device_data[x] != host_data[x]){
            err = 1;
        }
    }

    acc_free(device_data);
    free(host_data);

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