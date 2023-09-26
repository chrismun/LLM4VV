#include "acc_testsuite.h"
#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int *a = (int *)malloc(n * sizeof(int));
    int *a_dev = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *b_dev = (int *)malloc(n * sizeof(int));

    // Initialize arrays
    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 1;
    }

    #pragma acc data copyin(b[0:n]) create(a[0:n]) copyout(a_dev[0:n]) copyout(b_dev[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = b[x];
            }
        }
        #pragma acc enter data create(a_dev[0:n])
        #pragma acc update device(a_dev[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a_dev[x];
            }
        }
        #pragma acc exit data copyout(a_dev[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (a[x] != 1){
            err += 1;
        }
        if (b[x] != 1){
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