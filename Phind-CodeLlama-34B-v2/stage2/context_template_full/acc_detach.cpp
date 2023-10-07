#include <iostream>
#include <cstdlib>
#include <cassert>
#include "acc_testsuite.h"
#ifndef T1
/*T1:acc detach,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int *)malloc(n * sizeof(int));
    int *device_ptr = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        host_ptr[x] = rand() % n;
        device_ptr[x] = 0;
    }

    acc_attach(&device_ptr);
    acc_memcpy_to_device(device_ptr, host_ptr, n * sizeof(int));
    acc_detach(&device_ptr);

    for (int x = 0; x < n; ++x) {
        if (host_ptr[x] != device_ptr[x]) {
            err = 1;
            break;
        }
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