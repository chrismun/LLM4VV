#include "acc_testsuite.h"
#ifndef T1
//T1:acc update device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *host_data = (real_t *)malloc(n * sizeof(real_t));
    real_t *dev_data = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        host_data[x] = rand() / (real_t)(RAND_MAX / 10);
        dev_data[x] = 0.0;
    }

    #pragma acc enter data copyin(host_data[0:n]) create(dev_data[0:n])
    #pragma acc data present(host_data[0:n], dev_data[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            dev_data[x] = host_data[x];
        }
        #pragma acc update device(dev_data[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(host_data[x] - dev_data[x]) > PRECISION){
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