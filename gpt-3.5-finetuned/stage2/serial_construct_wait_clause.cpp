#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != acc_device_none){
        real_t *a = new real_t[n];
        real_t *b = new real_t[n];
        real_t *c = new real_t[n];

        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0.0;
        }

        #pragma acc enter data copyin(a[0:n], b[0:n])
        #pragma acc data copyout(c[0:n])
        {
          #pragma acc serial wait
          {
            {
              {
                {
                  #pragma acc loop 
                  for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                  }
                }
              }
            }
          }
        }
        #pragma acc exit data delete(a[0:n], b[0:n])

        for (int x = 0; x < n; ++x){
          if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
          }
        }
      }
      else{
        #pragma acc update device(c[0:n]) async(1)
        for (int x = 0; x < n; ++x){
          c[x] = (a[x] + b[x]);
        }
        #pragma acc wait
        for (int x = 0; x < n; ++x){
          if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
          }
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