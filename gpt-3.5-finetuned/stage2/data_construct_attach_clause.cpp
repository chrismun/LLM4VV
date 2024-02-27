#include "acc_testsuite.h"
#ifndef T1
//T1:data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *attach_test = new real_t[n];

    for (int x = 0; x < n; ++x){
        attach_test[x] = 0.0;
    }

    #pragma acc enter data create(attach_test[0:n])
    #pragma acc data copy(attach_test[0:n]) attach(attach_test[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                attach_test[x] = x / n;
            }
        }
    }
    #pragma acc exit data copyout(attach_test[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(attach_test[x] - (x / n)) > PRECISION){
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