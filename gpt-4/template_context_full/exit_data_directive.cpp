#include "acc_testsuite.h"
#ifndef T1
/*T1:exit data directive,V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);

    int* x = (int*)malloc(10 * sizeof(int));

    for(int i = 0; i < 10; i++) {
        x[i] = rand();
    }

    #pragma acc enter data copyin(x[0:10])

    #pragma acc parallel loop
    for(int i = 0; i < 10; i++) {
        x[i] += 1;
    }

    #pragma acc exit data copyout(x[0:10])

    for(int i = 0; i < 10; i++) {
        if(x[i] != (original_x[i] + 1)){
            err = 1;
        }
    } 

    free(x);
    
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}