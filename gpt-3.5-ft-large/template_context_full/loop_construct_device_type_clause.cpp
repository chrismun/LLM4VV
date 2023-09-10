#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct device_type clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

  real_t array_length =n;

  #pragma acc kernels device_type(nvidia) present(out[0:10]) present(array_length)
  {
    int ID = blockIdx.x * blockDim.x + threadIdx.x;

    while(ID < array_length){
      out[0] = 1;
      out[ID] = out[ID] + out[ID - 1];
      ID = ID + 64;
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