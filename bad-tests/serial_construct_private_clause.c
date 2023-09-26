#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct private clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int length = 128;
    int* a = (int*)malloc(length * sizeof(int));
    int* b = (int*)malloc(length * sizeof(int));
    srand(SEED);
    for (int x = 0; x < length; ++x){
        a[x] = rand() % 128;
        b[x] = 0;
    }
    #pragma acc serial copyin(a[0:length]) copyout(b[0:length]) private(x)
    {
    for (int x = 0; x < length; ++x){
        b[x] = a[x];
    }
    }
    for (int x = 0; x < length; ++x){
        if (b[x] != a[x]){
            err = 1;
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