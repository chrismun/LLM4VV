#include "acc_testsuite.h"

#ifndef T1
//T1:cache directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 100;
    int a[size], b[size];

    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc data copyin(a, b) copyout(a, b)
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; i++) {
            #pragma acc cache(a[i])
            {
                a[i] += b[i];
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if (a[i] != b[i] + a[i]) {
            err++;
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