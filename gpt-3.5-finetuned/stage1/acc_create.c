#include "acc_testsuite.h"
#ifndef T1
//T1:acc create,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));


    for (int x = 0; x < n; ++x){
        a[x] = rand() % 10;
        b[x] = rand() % 10;
        c[x] = 0;
    }

    acc_create(c, n * sizeof(int));
    acc_copyin(a, n * sizeof(int));
    acc_copyin(b, n * sizeof(int));

    #pragma acc data copyout(c[0:n]) present(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    acc_delete(c, n * sizeof(int));
    acc_delete(a, n * sizeof(int));
    acc_delete(b, n * sizeof(int));

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
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