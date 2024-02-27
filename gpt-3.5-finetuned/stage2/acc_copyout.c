#include "acc_testsuite.h"
#ifndef T1
//T1:acc copyout,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    char * a = (char *)malloc(n * sizeof(char));
    char * b = (char *)malloc(n * sizeof(char));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
    }

    #pragma acc enter data copyin(a[0:n])
    acc_copyout(b, n * sizeof(char));
    #pragma acc exit data delete(a[0:n])

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