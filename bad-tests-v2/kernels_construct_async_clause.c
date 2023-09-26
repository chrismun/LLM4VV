#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t a = acc_create(host_pinned, function, 1);
    real_t b = acc_create(host_pinned, function, 1);
    { 
      int _n = 1000;
        #pragma acc parallel loop copy(a[0:_n]) async(1)
        for (int i = 0; i < _n; ++i){
          a[i] = 1.0;
        }
        #pragma acc kernels loop copy(a[0:_n]) async(1)
        for (int i = 0; i < _n; ++i){
          a[i] += 1.0;
        }
      }
      while (acc_async_test(1) == acc_async_processing){
      }

      for (int x = 0; x < 1000; ++x){
          if (fabs(a[x]/b[x] - 2.0) > PRECISION){
              err = 1;
        break;
            }
      }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    int direction = 1;
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