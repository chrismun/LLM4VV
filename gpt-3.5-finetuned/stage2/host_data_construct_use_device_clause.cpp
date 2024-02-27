#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *devdata = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        hostdata[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copy(hostdata[0:n])
    {
        #pragma acc host_data use_device(hostdata)
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    hostdata[x] = hostdata[x] * hostdata[x];
                }
            }
        }
    }

    #pragma acc exit data copyout(devdata[0:n]) copyin(hostdata[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                devdata[x] = hostdata[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(devdata[x] - (hostdata[x] * hostdata[x])) > PRECISION){
            err = 1;
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