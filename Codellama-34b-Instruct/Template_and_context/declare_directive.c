#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc declare copy(x)
    int x = 0;

    #pragma acc declare copyin(y)
    int y = 0;

    #pragma acc declare copyout(z)
    int z = 0;

    #pragma acc declare create(w)
    int w = 0;

    #pragma acc declare present(v)
    int v = 0;

    #pragma acc declare deviceptr(u)
    int u = 0;

    #pragma acc declare device_resident(t)
    int t = 0;

    #pragma acc declare link(s)
    int s = 0;

    #pragma acc parallel
    {
        x = 1;
        y = 2;
        z = 3;
        w = 4;
        v = 5;
        u = 6;
        t = 7;
        s = 8;
    }

    if (x != 1 || y != 2 || z != 3 || w != 4 || v != 5 || u != 6 || t != 7 || s != 8) {
        err = 1;
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