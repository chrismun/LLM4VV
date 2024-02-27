#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int * a = new int [10 * n];
    int * b = new int [10 * n];
    int * c = new int [10 * n];

    #pragma acc kernels loop present(a[0:10*n]) if(n>10000)
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            a[x * n + y] = 0;
        }
    }

    for (int x = 0; x < 10 * n; ++x){
        if (a[x] != 0){
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