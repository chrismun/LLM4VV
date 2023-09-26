#include "acc_testsuite.h"
#ifndef T1
//T1:data construct copyout clause,V:2.7-3.3
int test1(){
    int err = 0;
    float a = rand()/(float)RAND_MAX;
    float b = 0.0;
    float host, device;

    host = a;

    #pragma acc data copyout(b)
    {   
        #pragma acc parallel num_workers(128)
        {
            #pragma acc loop worker
            for(int i = 0; i < 128; i++){
                b = a;
            }
        }

        device = b;
    }

    if(host != device){
        err = 1;
    }

    return err;
}
#endif

int main(){
    srand(SEED);
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
    if (failcode == 0){
        return 0;
    }else{
        return 1;
    }
}