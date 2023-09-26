#include "acc_testsuite.h"
#ifndef T1
//T1:routine,device-resident-data,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_device;
    real_t * b_device;
    
    for (int x = 0; x < n; ++x){
        a_host[x] = rand() / (real_t)(RAND_MAX / 10);
        b_host[x] = 0;
    }
    
    a_device = (real_t *)acc_malloc(n * sizeof(real_t));
    b_device = (real_t *)acc_malloc(n * sizeof(real_t));
    
    acc_memcpy_to_device(a_device, a_host, n * sizeof(real_t));
    
    #pragma acc parallel loop present(a_device[0:n], b_device[0:n])
    for (int x = 0; x < n; ++x){
        b_device[x] = a_device[x];
    }
    
    acc_memcpy_to_host(b_host, b_device, n * sizeof(real_t));
    
    for (int x = 0; x < n; ++x){
        if (fabs(b_host[x] - a_host[x]) > PRECISION){
            err += 1;
        }
    }
    acc_free(a_device);
    acc_free(b_device);
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