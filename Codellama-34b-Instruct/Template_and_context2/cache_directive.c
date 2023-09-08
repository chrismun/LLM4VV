#include "acc_testsuite.h"

#ifndef T1
//T1:cache directive,V:2.7-3.3
int test1(){
    int err = 0;

    // create an array to be cached
    int arr[100];

    // initialize the array
    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }

    // cache the array
    #pragma acc cache(arr)

    // modify the array
    for (int i = 0; i < 100; i++) {
        arr[i] = arr[i] + 1;
    }

    // check that the array has been modified
    for (int i = 0; i < 100; i++) {
        if (arr[i] != i + 1) {
            err++;
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