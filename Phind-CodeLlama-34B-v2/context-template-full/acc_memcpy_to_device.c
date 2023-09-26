#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc memcpy to device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *host_array = (int *)malloc(n * sizeof(int));
    int *device_array = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        host_array[x] = rand() % n;
    }

    acc_memcpy_to_device(device_array, host_array, n * sizeof(int));
    acc_memcpy_from_device(host_array, device_array, n * sizeof(int));

    for (int x = 0; x < n; ++x){
        if (host_array[x] != device_array[x]){
            err = 1;
            break;
        }
    }

    free(host_array);
    acc_free(device_array);

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