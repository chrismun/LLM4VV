#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct gang clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(10* n * sizeof(int));
    int temp = 0;

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 1;
    }
    #pragma acc data copyin(a[0:10*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang
            for (int x = 0; x < 10; ++x){
                temp = 0;
                #pragma acc loop gang reduction(+:temp)
                for (int y = 0; y < n; ++y){
                    temp += a[x * n + y];
                }
                #pragma acc loop gang
                for (int y = 0; y < n; ++y){
                    a[x * n + y] = a[x * n + y] / temp;
                }
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            if (a[x * n + y] != 1 / n){
                err = 1;
            }
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