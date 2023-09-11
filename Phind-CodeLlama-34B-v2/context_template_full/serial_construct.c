#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int a[10], b[10], c[10];

    for (int x = 0; x < 10; ++x){
        a[x] = rand() % 10;
        b[x] = rand() % 10;
    }

    #pragma acc serial
    {
        for (int x = 0; x < 10; ++x){
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < 10; ++x){
        if (c[x] != a[x] + b[x]){
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