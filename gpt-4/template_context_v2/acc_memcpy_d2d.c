#include "acc_testsuite.h"
#ifndef T1
//T1:acc_memcpy_d2d,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int* a = (int*)acc_malloc(NUM_ELEMS * sizeof(int));
    int* b = (int*)acc_malloc(NUM_ELEMS * sizeof(int));
    // Initialization
    for(int i = 0; i < NUM_ELEMS; i++)
        a[i] = rand();

    acc_memcpy_d2d(b, a, NUM_ELEMS * sizeof(int));

    // Verification
    float err_total = 0;
    for (int i = 0; i<NUM_ELEMS; ++i){
        err_total += (a[i]-b[i]) * (a[i]-b[i]);
    }

    if(sqrt(err_total)/NUM_ELEMS > TOLERANCE){
        err = 1;
    }
    acc_free(a);
    acc_free(b);
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