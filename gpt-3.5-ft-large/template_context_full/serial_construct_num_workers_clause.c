#include "acc_testsuite.h"
#ifndef T1
#include<random>
//T1:serial construct num_workers clause,V:2.7-3.3
int test1(){
  int err = 0;
  srand(SEED);
  real_t multi[10] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
  real_t host_multi[10];
  int multi_present = 0;

  for (int x = 0; x < 10; ++x){
      host_multi[x] = 0.0;
  }

  #pragma acc data copy(multi[0:10]) copyout(host_multi[0:10])
  {
      multi_present = 1;
      #pragma acc serial num_workers(4)
      {
          #pragma acc loop
          for (int x = 0; x < 10; ++x){
              host_multi[x] = multi[x];
              #pragma acc loop worker
              for (int y = 0; y < x; ++y){
                  host_multi[x] += 1.0;
              }
          }
      }
  }


  for (int x = 0; x < 10; ++x){
      if (fabs(host_multi[x] - (multi[x]*(x + 1) + 1)) > PRECISION){
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