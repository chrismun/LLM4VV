#include "acc_testsuite.h"
#ifndef T1
//T1:compute,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    int *b = (int*)malloc(size * sizeof(int));
    int condition = rand() % 2; // Condition will randomly enable or disable the parallel execution
    for (int i = 0; i < size; ++i){
        a[i] = 1;
        b[i] = 0;
    }

    // Compute construct with if-clause
    #pragma acc parallel loop if(condition)
    for (int i = 0; i < size; ++i){
        b[i] = a[i] + 1;
    }

    // Verification
    for (int i = 0; i < size; ++i){
        if (condition) {
            if (b[i] != a[i] + 1) {
                err++;
            }
        } else {
            // Condition is false. Changes should not have occurred.
            if (b[i] != 0) {
                err++;
            }
        }
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