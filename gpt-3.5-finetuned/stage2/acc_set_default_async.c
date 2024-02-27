#include "acc_testsuite.h"
#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int device = acc_get_device_type();

    acc_set_default_async(1);
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        for (int x = 0; x < n; ++x){
            #pragma acc parallel async
            {
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        failing = (c[x] - c_host[x] > PRECISION);
    }

    return err;
}

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