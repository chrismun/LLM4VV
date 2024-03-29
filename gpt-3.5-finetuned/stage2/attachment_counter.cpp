#include "acc_testsuite.h"

#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    for (int x = 0; x < n; ++x){
        a[x] = 0;
    }
    int * b = (int *)malloc(n * sizeof(int));
    for (int x = 0; x < n; ++x){
        b[x] = 0;
    }

    #pragma acc enter data create(a[0:n], b[0:n])
    #pragma acc enter data copyin(a[0:n], b[0:n]) attach(a)
    #pragma acc parallel present(a[0:n], b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = 1;
        }
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
    }
    #pragma acc exit data copyout(a[0:n], b[0:n]) delete(b[0:n])
    for (int x = 0; x < n; ++x){
        if (a[x] != 1){
            err += 1;
        }
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