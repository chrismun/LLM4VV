#include "acc_testsuite.h"
#ifndef T1
//T1:acc detach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));
    int* errors = (int *)malloc(2 * sizeof(int));
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        d[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc data copyout(c[0:n], d[0:n]) //data is already present at this point
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
            acc_detach(&c);
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a[x] * b[x];
            }
            acc_detach(&d);
        }
    }

    #pragma acc exit data copyout(a[0:n], b[0:n])
    err += check_attach_detach(a, b, c, d);

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