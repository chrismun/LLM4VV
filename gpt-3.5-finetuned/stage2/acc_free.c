#include "acc_testsuite.h"
#ifndef T1
//T1:acc free,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    // example of acc_malloc followed by acc_free
    int *a = (int *)malloc(n * sizeof(int));
    for (int x = 0; x < n; ++x){
        a[x] = 0;
    }
    acc_create(a);
    #pragma acc enter data create(a[0:n])
    acc_free(a);
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