#include "acc_testsuite.h"
#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc set default(async(1))
    #pragma acc parallel loop present(a[0:n], b[0:n])
    for (int x = 0; x < n; ++x){
        b[x] = a[x];
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