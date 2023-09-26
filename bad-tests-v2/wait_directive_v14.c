#include "acc_testsuite.h"
#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));
    int *d = (int *)malloc(n * sizeof(int));
    int *e = (int *)malloc(n * sizeof(int));
    int *f = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
        c[x] = 0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = d[x];
        f[x] = 0;
    }

    #pragma acc data copyin(a[0:n], d[0:n]) copyout(c[0:n], f[0:n])
    {
        #pragma acc wait
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = b[x] - a[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = b[x];
            }
        }
        #pragma acc parallel present(c[0:n], d[0:n], e[0:n]) wait(a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                e[x] = e[x] - c[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                f[x] = e[x];
            }
        }
        #pragma acc wait
    }

    for (int x = 0; x < n; ++x){
        if (c[x] + d[x] != f[x]){
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