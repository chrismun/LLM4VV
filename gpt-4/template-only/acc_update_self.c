#include "acc_testsuite.h"

#ifndef T1
// T1:acc update self, V:2.7-3.3

int test_acc_update_self(){
    int err = 0;
    long size = 10240;
    srand(SEED);
    float* a_host = (float*)malloc(size * sizeof(float));
    float* b_host = (float*)malloc(size * sizeof(float));

    for(long i=0 ; i<size ; i++){
        a_host[i] = rand()/(float)RAND_MAX;
        b_host[i] = rand()/(float)RAND_MAX;
    }

    float* a_device;
    float* b_device;
    
    #pragma acc data create(a_device[0:size]) copyin(b_host[0:size]) copyout(b_device[0:size])
    {
        #pragma acc-enter data copyin(a_host[0:size])
        #pragma acc parallel loop
        for(long i=0 ; i<size ; i++){
            a_device[i] = a_host[i] + b_host[i];
        }
        #pragma acc update self(a_device[0:size])
        #pragma acc exit data delete(a_host[0:size])
        #pragma acc parallel loop
        for(long i=0 ; i<size ; i++){
            b_device[i] = a_device[i] + b_host[i];
        }
    }
    
    for(long i=0 ; i<size ; i++){
        if(abs(a_host[i] - b_device[i]) > PRECISION){
            err = 1;
            break;
        }
    }
    
    free(a_host);
    free(b_host);
    
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_update_self();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}