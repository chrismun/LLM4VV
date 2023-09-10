#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct async clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int gang[10];
    int worker[10];
    int vector[10];
    srand(SEED);

    #pragma acc data copy(gang, worker, vector)
    {
      #pragma acc parallel async
      {
        for (int i=0; i<10; i++) {
          gang[i] = __pgi_gangidx();
          worker[i] = __pgi_workeridx();
          vector[i] = __pgi_threadidx();
        }
      }
      acc_wait();
      for (int i=0; i<10; i++) {
        if (gang[i] != __pgi_gangidx() ||
            worker[i] != __pgi_workeridx() ||
            vector[i] != __pgi_threadidx()) {
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