#include "acc_testsuite.h"
#ifndef T1
//T1:serial,async,construct 
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));
    real_t *e = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
      a[x] = rand() / (real_t)(RAND_MAX / 10);
      b[x] = rand() / (real_t)(RAND_MAX / 10);
      c[x] = 0;
      d[x] = rand() / (real_t)(RAND_MAX / 10);
      e[x] = 0;
    }

    #pragma acc enter data create(e[0:n])
    #pragma acc data copyin(a[0:n], b[0:n], d[0:n]) 
    {
        #pragma acc parallel async(1) 
        {
            #pragma acc loop 
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
        #pragma acc parallel async(2)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                e[x] = c[x] + d[x];
            }
        }
        #pragma acc update host(e[0:n]) async(2)
    }
    #pragma acc exit data copyout(e[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(e[x] - (a[x] + b[x] + d[x])) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);

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