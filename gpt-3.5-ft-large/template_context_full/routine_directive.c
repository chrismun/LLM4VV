#include "acc_testsuite.h"
#ifndef T1
//T1:routine directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int defNum = 0;

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));

    for(int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 1;
    }

    #pragma acc data copy(a[0:n]) copyout(b[0:n])
    {
        #pragma acc routine seq
        for(int x = 0; x < n; ++x){
            b[x] = f(a[x]);
        }
    }

    for(int x = 0; x < n; ++x){
        if(b[x] < 0){
            err += b[x];
        }
    }

    acc_shutdown(acc_get_device_num(acc_get_device_type()), acc_get_device_type());

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