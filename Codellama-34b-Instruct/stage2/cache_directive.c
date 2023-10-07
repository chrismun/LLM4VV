#include "acc_testsuite.h"

#ifndef T1
//T1:cache directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int arr[100];
    int i;

    #pragma acc cache(arr[0:100])
    {
        for (i = 0; i < 100; i++) {
            arr[i] = i;
        }
    }

    if (arr[0] != 0 || arr[99] != 99) {
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