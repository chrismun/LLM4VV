#include "acc_testsuite.h"
#ifndef T2
//T2:parallel,loop,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (int)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang vector
            for (int x = 0; x < n; ++x){
                b[x] = a[x] * a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != a[x] * a[x]){
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}