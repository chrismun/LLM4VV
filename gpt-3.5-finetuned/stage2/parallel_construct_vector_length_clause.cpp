#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,loop,combined-constructs,V:2.7-3.3

int test1(){

    int err = 0;
    srand(SEED);

    real_t *a = new real_t[_PB_N];
    real_t *b = new real_t[_PB_N];
    real_t *c = new real_t[_PB_N];
    
    for (int x = 0; x < _PB_N; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:_PB_N], b[0:_PB_N]) copyout(c[0:_PB_N])
    {
      #pragma acc parallel vector_length(16)
      {
        #pragma acc loop
        for (int i = 0; i < N; ++i){
          c[i] = a[i] + b[i];
        }
      }
    }
  
    for (int x = 0; x < _PB_N; ++x){
        if(fabs(a[x] + b[x] - c[x]) > PRECISION){
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