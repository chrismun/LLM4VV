#include "acc_testsuite.h"

#ifndef T1
// T1:kernels, loop, loop-gang-vector, V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % 100;
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop vector
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (abs(b[x] - a[x]) > PRECISION){
            err++;
        }
    }

    return err;
}
#endif

int main(){
    int failCode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < n; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failCode = failCode + (1 << 0);
    }
#endif
    return failCode;
}