#include "acc_testsuite.h"

#ifndef T1
//T1:declare,data,create,V:1.0-2.7
int test1(){
    int err = 0;
    int n = 100;
    int *a;

    #pragma acc enter data copyin(n)
    #pragma acc parallel present(a)
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            a[i] = i;
        }
    }
    #pragma acc exit data delete(n)

    for (int i = 0; i < n; ++i){
        if (a[i] != i){
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