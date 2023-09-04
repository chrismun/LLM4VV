#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,data-region,attach,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * test = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (int)(RAND_MAX / 10);
        b[x] = 0;
        test[x] = b[x] + 1;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel copyout(b[0:n]) attach(test[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != test[x]){
            err += 1;
            break;
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