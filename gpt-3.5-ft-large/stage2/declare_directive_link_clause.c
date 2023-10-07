#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));
    int *a_host = (int *)malloc(n * sizeof(int));
    int *results = (int *)malloc(10 * n * sizeof(int));
    real_t temp = 0.;

    for (int x = 0; x < n; ++x){
        a[x] = x;
        a_host[x] = x;
        b[x] = 1;
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copy(b[0:n]) copyout(c[0:n])
    {
        #pragma acc declare device(link(c))
        {
            #pragma acc parallel present(c[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = c[x] + a[x];
                }
            }
            #pragma acc parallel present(c[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = c[x] + b[x];
                }
            }

        }
        #pragma acc parallel present(c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + 2 * b[x])) > PRECISION){
            err += 1;
        }
    }

    for (int x = 0; x < n; ++x){
        results[x] = 0;
    }
    for (int x = 0; x < n; ++x){
        results[x + n * 1] = 1;
    }
    for (int x = 0; x < n; ++x){
        results[x + n * 2] = x;
    }
    for (int x = 0; x < n; ++x){
        results[x + n * 3] = x + 1;
    }
    for (int x = 2; x < n; ++x){
        results[x] += results[x - 2];
    }
    temp = 0;
    for (int x = 0; x < n; ++x){
        temp += results[x];
    }
    temp = temp / n;
    for (int x = 0; x < n; ++x){
        if (fabs(temp - results[x + n * 4]) > PRECISION){
            err += 1;
        }
    }
    temp = 0;
    for (int x = 0; x < n; ++x){
        temp += a[x];
    }
    temp = temp / n;
    if (fabs(temp - a[0]) > PRECISION){
        err += 1;
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