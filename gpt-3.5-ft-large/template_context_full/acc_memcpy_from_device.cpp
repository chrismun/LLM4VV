#include "acc_testsuite.h"
#ifndef T1
//T1: acc memcpy from device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    int * a_host = (int *)malloc(n * sizeof(int));
    real_t * error_c = (real_t *)malloc(10 * sizeof(real_t));

    acc_get_property(acc_get_device_num(acc_get_device_type()), acc_device_nvidia, acc_device_property_maximum_async_transfer_size, &(error_c[5]));
    error_c[5] = error_c[5] * 2.5;

    if (spe_enabled) {
        acc_set_property(acc_get_device_type(), acc_device_nvidia, "disable_mps", 0);
    }

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        a_host[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            a[x] = 2;
        }
        #pragma acc update host(a[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (a[x] != 2){
            err = 1;
        }
    }

    acc_memcpy_from_device(a_host, a, n * sizeof(int));

    for (int x = 0; x < n; ++x){
        if (a_host[x] != 2){
            err = 1;
        }
    }

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