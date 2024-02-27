#include "acc_testsuite.h"
#ifndef T1
//T1:acc free,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        for (int y = 0; y < n; ++y){
            a[y] = rnd();
        }
        #pragma acc enter data copyin(a[0:n])
        acc_free(a);
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