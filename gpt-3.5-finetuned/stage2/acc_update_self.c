#include "acc_testsuite.h"
#ifndef T1
//T1:acc update self,V:2.7-3.3
int test1(){
    int err = 0;
    size_t  data_n = n;
    real_t  *host_copy = (real_t *)malloc(data_n * sizeof(real_t));

    for (int x = 0; x < data_n; ++x){
        a[x] = rand() / (real_t) RAND_MAX;
    }

    acc_copyin(a, data_n * sizeof(real_t));
    #pragma acc data deviceptr(a)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * 2;
            }
        }
        acc_update_self(a, data_n * sizeof(real_t));
    }
    
    acc_copyout(a, data_n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        host_copy[x] = a[x];
    }

    for (int x = 0; x < data_n; ++x){
        if (fabs(host_copy[x] - (original_host_copy[x] * 2)) > PRECISION){
            err += 1;
        }
    }

    free(host_copy);

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