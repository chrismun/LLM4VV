#include "acc_testsuite.h"
#ifndef T1
//T1:acc hostptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));

    int *host_data = (int *)malloc(n * sizeof(int));
    int *device_data = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        host_data[x] = rand() % n;
        device_data[x] = 0;
    }

    acc_memcpy_to_device(device_data, host_data, n * sizeof(int));

    int *host_ptr = (int *)acc_hostptr(device_data);

    if (host_ptr != host_data){
        err = 1;
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