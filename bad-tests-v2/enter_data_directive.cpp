#include "acc_testsuite.h"
#ifndef T1
/*T1:enter data directive,V:2.0-2.7*/

int test1(){
    int err = 0;
    srand(SEED);
    float *a = (float*)malloc(100*sizeof(float));
    float *b = (float*)malloc(100*sizeof(float));

    for(int i = 0; i < 100; i++) {
        a[i] = rand();
    }

    #pragma acc enter data create(b[0:100])

    #pragma acc parallel copyin(a[0:100]) copyout(b[0:100])
    for(int i = 0; i < 100; i++) {
        b[i] = a[i]*2;
    }

    #pragma acc exit data delete(b[0:100])

    for(int i = 0; i < 100; i++) {
        if(b[i] != a[i]*2) {
            err = 1;
            break;
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