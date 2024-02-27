#include "acc_testsuite.h"
#ifndef T1
//T1:acc free,V:2.7-3.3
int test1(){
    int err = 0;

    #pragma acc data
    {
        int *a = (int *)malloc(n * sizeof(int));
        const size_t size = n * sizeof(int);
        int *a_ptr = (int *)acc_copyin(a, size);
        acc_free(a_ptr);
        free(a);
    }
    
    return err;
}

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