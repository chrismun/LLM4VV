#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int* a = (int*)malloc(sizeof(int) * 10);
    int* b = (int*)malloc(sizeof(int) * 10);
    int* c = (int*)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }

    #pragma acc kernels firstprivate(a, b, c)
    {
        for (int i = 0; i < 10; i++) {
            a[i] = b[i] + c[i];
        }
    }

    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i] + c[i]) {
            err = 1;
            break;
        }
    }

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