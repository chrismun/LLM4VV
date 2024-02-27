#include "acc_testsuite.h"
//T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test if the data present clause successfully transfers data between the host and the device
    #pragma acc data copyin(n)
    {
        #pragma acc parallel loop present(n_host)
        for (int x = 0; x < n; ++x){
            n_host[x] = rand() / (real_t)(RAND_MAX / 10);
        }
    }


    return err;
}

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