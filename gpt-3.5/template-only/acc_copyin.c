#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    int a[10] = {0};
    int b = 1;

    #pragma acc data copyin(a[:10], b)
    {
        // Modify a and b
        for (int i = 0; i < 10; i++){
            a[i] += b;
        }
        b++;
    }
    
    // Verify the modifications
    for (int i = 0; i < 10; i++){
        if (a[i] != 1){
            err = 1;
            break;
        }
    }
    if (b != 2){
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