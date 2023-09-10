#include "acc_testsuite.h"
#ifndef T1
//T1:serial,V:2.7-3.3
int test1(){
    //loop does not run in parallel, unusually complicated reduction
    int err = 0;
    srand(SEED);
    real_t * a = new real_t[n];
    real_t * b = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc serail
        {
            #pragma acc loop default(none) reduction(+:b[0:n])
            for (int x = 0; x < n; ++x){
                b[x] += a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (2 * a[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:serial construct default clause, devcount, part:compatibility
int test2(){
    int err = 0;
    srand(SEED);
    int * dev_a = new int[m * n];
    int * a = new int[m * n];
    int multiplier = 1;

    #pragma acc data copyout(a[0:m*n])
    {
      #pragma acc serail 
      {
        #pragma acc loop default(multiplier)
          for (int x = 0; x < m * n; ++x){
              a[x] = multiplier;
              multiplier += 1;
            }
          }
      }
  }

    for (int x = 0; x < m * n; ++x){
        if (a[x] != dev_a[x] * (devcount + 1)){
            if (multiplier > devcount){
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
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}