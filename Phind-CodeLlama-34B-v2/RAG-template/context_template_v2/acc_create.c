#include "acc_testsuite.h"
#ifndef T1
//T1:acc create,V:2.7-3.3
int test1(){
    int err = 0;
    int *a = (int *)malloc(n * sizeof(int));
    int *devPtr;

    #pragma acc enter data copyin(a[0:n])
    #pragma acc parallel present(a[0:n])
    {
        devPtr = a;
    }

    if (devPtr != a) {
        err = 1;
    }

    #pragma acc exit data delete(a[0:n])
    free(a);

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