#include <iostream>
#include <cstdlib>
#include <cassert>
#include "acc_testsuite.h"
#ifndef T1
/*T1:acc memcpy from device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *host_src = (int *)malloc(n * sizeof(int));
    int *host_dest = (int *)malloc(n * sizeof(int));
    int *device_src = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        host_src[x] = rand() % n;
        host_dest[x] = -1;
    }

    acc_memcpy_to_device(device_src, host_src, n * sizeof(int));

    acc_memcpy_from_device(host_dest, device_src, n * sizeof(int));

    for (int x = 0; x < n; ++x){
        if (host_dest[x] != host_src[x]){
            err = 1;
            break;
        }
    }

    acc_free(device_src);
    free(host_src);
    free(host_dest);

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