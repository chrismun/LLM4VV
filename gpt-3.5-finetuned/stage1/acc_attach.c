#include "acc_testsuite.h"
#ifndef T1
//T1:acc attach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 1
    }
    for (int x = 0; x < n; ++x){
        b[x] = 2
    }
    for (int x = 0; x < n; ++x){
        c[x] = 0.0;
    }

    #pragma acc parallel 
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = 2 * a[x];
        }
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            b[x] = 2 * b[x];
        }
    }

    acc_attach((h_void **)&a);
    acc_attach((h_void **)&b);

    #pragma acc data copyin(a[0:n], b[0:n]) create(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }
    acc_detach((h_void **)&a);
    acc_detach((h_void **)&b);
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 6.0) > PRECISION - 0.5){
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