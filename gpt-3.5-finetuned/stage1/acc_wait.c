#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;
    unsigned int *a = (unsigned int *)malloc(10 * n * sizeof(unsigned int));
    unsigned int *b = (unsigned int *)malloc(10 * n * sizeof(unsigned int));

    for (int i = 0; i < 10; ++i){
        for (int x = 0; x < n; ++x){
            a[i* n + x] = (unsigned int)arc4random();
            b[i* n + x] = a[i* n + x];
        }
    }

    #pragma acc data copy(a[0:10*n])
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int i = 0; i < 10; ++i){
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[i * n + x] += 1;
                }
            }
        }
        acc_wait(1);
        for (int x = 0; x < 10 * n; ++x){
            if (a[x] != b[x] + 1){
                err += 1;
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