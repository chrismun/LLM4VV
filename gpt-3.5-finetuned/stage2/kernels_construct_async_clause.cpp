#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = new real_t[n];
    real_t *b = new real_t[n];
    real_t *c = new real_t[n];
    real_t *d = new real_t[n];
    real_t *e = new real_t[n];

    for (int x = 0; x < n; ++x){
      a[x] = rand() / (real_t)(RAND_MAX / 10);
      b[x] = rand() / (real_t)(RAND_MAX / 10);
      c[x] = rand() / (real_t)(RAND_MAX / 10);
      d[x] = rand() / (real_t)(RAND_MAX / 10);
      e[x] = 0.0;
    }

    srand(SEED);
    for (int x = 0; x < n; ++x){
      a[x] = rand() / (real_t)(RAND_MAX / 10);
      b[x] = rand() / (real_t)(RAND_MAX / 10);
      c[x] = rand() / (real_t)(RAND_MAX / 10);
      d[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n], d[0:n]) create(e[0:n])
    {
        for (int async = 1; async < 10; ++async)
        {
            #pragma acc kernels async(async)
            {
                #pragma acc loop
                  for (int x = 0; x < n; ++x){
                    e[x] = a[x] + b[x] + c[x] + d[x];
                  }
            }
        }
        for (int async = 1; async < 10; ++async)
        {
            #pragma acc kernels wait(async) async(async)
            {
              #pragma acc loop
                for (int x = 0; x < n; ++x){
                  e[x] += a[x] + b[x] + c[x] + d[x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
      if (fabs(e[x] - 10*(a[x] + b[x] + c[x] + d[x])) > PRECISION)
      {
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