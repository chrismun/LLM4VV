#include "acc_testsuite.h"
#ifndef T1
/*T1:declare directive device_resident clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a;
    int n = 100;

    #pragma acc enter data copyin(n)
    #pragma acc declare device_resident(a)

    a = (int*)malloc(n * sizeof(int));

    if (a == NULL){
        err = 1;
    }

    #pragma acc exit data delete(a)
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