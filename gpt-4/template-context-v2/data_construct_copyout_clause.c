#include "acc_testsuite.h"
#ifndef T1
// T1:data construct copyout clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int len = 1024;
    float* a_host = (float*)malloc(len * sizeof(float));
    float* a_device = (float*)malloc(len * sizeof(float));
    for(int i = 0; i < len; i++) { 
        a_host[i] = (float)rand()/(float)(RAND_MAX/100.0); // Random values ranged in [0,100)
    }
    #pragma acc data copyout(a_device[0:len])
    {
        #pragma acc parallel loop
        for(int i = 0; i < len; i++) {
            a_device[i] = a_host[i];
        }
    }
    for(int i = 0; i < len; i++) {
        if(fabs(a_host[i] - a_device[i]) > PRECISION ){
            err = 1;
            break;
        }
    }

    free(a_host);
    free(a_device);
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