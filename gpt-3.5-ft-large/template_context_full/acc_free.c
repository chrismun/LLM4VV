#include "acc_testsuite.h"
#ifndef T1
//T1: acc_free,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *host_data = (int *)malloc(n * sizeof(int));
    int *device_data = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        host_data[x] = 0;
    }
    for (int x = 0; x < n; ++x){
        device_data[x] = 1;
    }

    #pragma acc data copy(device_data[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                device_data[x] = 0;
            }
        }
    }

    #pragma acc exit data copyout(host_data[0:n])

    for (int x = 0; x < n; ++x){
        if (device_data[x] != host_data[x]){
            err += 1;
        }
    }

    acc_free(device_data);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    int invalid_device_num = acc_get_num_devices() + 1;
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