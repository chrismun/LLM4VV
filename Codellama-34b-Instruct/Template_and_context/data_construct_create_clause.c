#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int* a = (int*)malloc(sizeof(int));
    int* b = (int*)malloc(sizeof(int));

    #pragma acc enter data create(a, b)
    {
        a[0] = 1;
        b[0] = 2;
    }

    #pragma acc exit data delete(a, b)

    if (a[0] != 1 || b[0] != 2) {
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