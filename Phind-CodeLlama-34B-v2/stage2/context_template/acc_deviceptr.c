#include "acc_testsuite.h"
#ifndef T1
//T1:acc deviceptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));

    int *host_data = (int *)malloc(n * sizeof(int));
    int *device_data = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        host_data[x] = rand() % n;
        device_data[x] = 0;
    }

    #pragma acc enter data copyin(host_data[0:n])
    #pragma acc enter data copyin(device_data[0:n])

    #pragma acc parallel present(host_data[0:n], device_data[0:n])
    {
        int *device_ptr = acc_deviceptr(host_data);
        if (device_ptr == NULL){
            err = 1;
        }
        for (int x = 0; x < n; ++x){
            device_data[x] = device_ptr[x];
        }
    }

    #pragma acc exit data copyout(host_data[0:n]) copyout(device_data[0:n])

    for (int x = 0; x < n; ++x){
        if (host_data[x] != device_data[x]){
            err = 1;
        }
    }

    free(host_data);
    acc_free(device_data);

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