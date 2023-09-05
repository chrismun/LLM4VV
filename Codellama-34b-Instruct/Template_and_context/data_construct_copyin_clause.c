#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int* a = (int*)malloc(sizeof(int));
    int* b = (int*)malloc(sizeof(int));
    int* c = (int*)malloc(sizeof(int));

    #pragma acc enter data copyin(a[0:10], b[0:10], c[0:10])
    {
        // Do some work with the data
    }

    #pragma acc exit data delete(a[0:10], b[0:10], c[0:10])

    free(a);
    free(b);
    free(c);

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