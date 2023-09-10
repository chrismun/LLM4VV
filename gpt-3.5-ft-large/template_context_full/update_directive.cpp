#include "acc_testsuite.h"
#ifndef T1
#pragma acc data copyin(a[0:10]) 
#pragma acc kernels
{
    #pragma acc loop
    for (int i = 0; i < 10; i++) {
        a[i] += 1.0;
    }
}
#pragma acc update host(a[0:10])
#endif

int test1(){
    int err = 0;
    srand(SEED);
  if (a[0] != 0){
        err = 1;
      }
    acc_attach(a, 10 * sizeof(real_t));
    if(a_present == 0){
        err = 1;
    }
    return err;
}

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