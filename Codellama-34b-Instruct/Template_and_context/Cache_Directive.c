#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int arr[100];
    int i;

    #pragma acc cache(arr[0:100])
    for (i = 0; i < 100; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[0:100])
    for (i = 0; i < 100; i++) {
        if (arr[i] != i) {
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