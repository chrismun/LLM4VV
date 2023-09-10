#include "acc_testsuite.h"
#ifndef T1
//T1:data construct copyin clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(n * sizeof(int));
    int * d = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
        c[x] = 0;
        d[x] = 3;
    }

    #pragma acc data copyin(c[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (c[x] < 3 && c[x] > 4){ //The value of c at position x should still be zero
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