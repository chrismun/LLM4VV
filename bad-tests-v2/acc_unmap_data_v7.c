#include "acc_testsuite.h"
#ifndef T2
//T2:kernels,data,data-region,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_device;

    for (int i = 0; i < n; ++i){
        a_host[i] = rand() / (real_t)(RAND_MAX / 10);
        a_device[i] = 0;
    }

    #pragma acc data create(a_device[0:n])
    {
        #pragma acc update device(a_host[0:n])
        acc_deviceptr((void**)&a_device, a_host, n * sizeof(real_t));

        #pragma acc kernels present(a_device[0:n])
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                a_device[i] = a_host[i];
            }
        }
        acc_unmap_data(a_host);
    }

    for (int i = 0; i < n; ++i){
        if (fabs(a_device[i] - a_host[i]) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}