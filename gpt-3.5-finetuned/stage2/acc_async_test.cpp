#include "acc_testsuite.h"

int test1(){
    int err = 0;
    int wait_arg = acc_get_default_async();
    int *a = new int [10 * n];
    int *b = new int [10 * n];
    int *c = new int [10 * n];
    int *hosttest = new int[10 * n];
    int *d = a;
    int *e = b;

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        hosttest[x] = a[x] + b[x];
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) create(c[0:10*n])
    {
        for (int x = 0; x < 10; ++x){
            acc_set_default_async(x);
            #pragma acc loop async(x)
            for (int y = 0; y < n; ++y){
                c[x * n + y] = a[x * n + y] + b[x * n + y];
            }
        }
        #pragma acc wait
    }


    for (int x = 0; x < 10; ++x){
        if (!acc_async_test(x)){
            err += 1;
        }
    }



    return err;
}

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