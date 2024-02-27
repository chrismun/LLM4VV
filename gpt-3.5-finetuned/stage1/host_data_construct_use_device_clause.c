#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *host_data = (real_t *)malloc(n * sizeof(real_t));
    real_t *host_data_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t *device_data = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        host_data[x] = rand() / (real_t)(RAND_MAX / 10);
        host_data_copy[x] = host_data[x];
        device_data[x] = 0.0;
    }

    #pragma acc enter data create(device_data[0:n]), copyin(host_data[0:n])
    #pragma acc host_data use_device(host_data)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                host_data[x] = x;
            }
        }
    }
    #pragma acc exit data copyout(host_data[0:n]) delete(device_data[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(host_data[x] - host_data_copy[x]) > PRECISION){
            err += 1;
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