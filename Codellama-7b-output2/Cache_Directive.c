#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of integers
    int a[10];
    for (int i = 0; i < 10; i++){
        a[i] = rand();
    }

    // Create a cache directive
    #pragma acc cache(a)

    // Check if the cache directive is working properly
    for (int i = 0; i < 10; i++){
        if (a[i] != rand()){
            err = 1;
            break;
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