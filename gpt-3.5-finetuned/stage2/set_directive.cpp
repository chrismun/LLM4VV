#include "acc_testsuite.h"
#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc set device_type(nvidia)
    #pragma acc set device_num(0)

    int* a = new int[10];
    for(int x = 0; x < 10; ++x){
        a[x] = 1;
    }

    #pragma acc parallel present(a[0:10])
    {
        #pragma acc loop
        for (int x = 0; x < 10; ++x){
            a[x] = 2;
        }
    }

    for (int x = 0; x < 10; ++x){
        if (a[x] != 2){
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