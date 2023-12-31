#include "acc_testsuite.h"
#ifndef T1
//T1:data construct copy clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *b;
    a = (int *)malloc(sizeof(int));
    b = (int *)malloc(sizeof(int));
    *a = 1;
    *b = 2;
    #pragma acc data copy(a, b)
    {
        #pragma acc parallel
        {
            a[0] = 3;
            b[0] = 4;
        }
    }
    if (*a != 3 || *b != 4) {
        err = 1;
    }
    free(a);
    free(b);
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