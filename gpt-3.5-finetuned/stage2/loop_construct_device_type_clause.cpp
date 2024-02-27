#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct device_type clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

      #pragma acc parallel loop device_type(nvidia) reduction(+:err)
      for (int x = 1; x < 5; ++x)
      {
        err+=1;
      }

      #pragma acc parallel loop device_type(host) reduction(+:err)
      for (int x = 1; x < 5; ++x)
      {
            err-=1;
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