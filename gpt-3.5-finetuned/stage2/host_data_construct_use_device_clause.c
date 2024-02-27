#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *host_array = (real_t *)malloc(n * sizeof(real_t));
    real_t *device_array = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        host_array[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    #pragma acc enter data create(device_array[0:n])
    #pragma acc host_data use_device(device_array[0:n])
    {
        #pragma acc parallel
        {
            for (int x = 0; x < n; ++x){
                device_array[x] = host_array[x];
            }
        }
    }
    #pragma acc exit data copyout(host_array[0:n]) delete(device_array[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(host_array[x] - device_array[x]) > PRECISION){
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