#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(){
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    int IsHost = 0;
    int *IsHost_ptr = &IsHost;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    _Pragma("acc parallel")
    {
      _Pragma("acc kernels loop async(1)") _Pragma("host") { sleep(1); } _Pragma("acc end host")
    }
    while (acc_is_data_present(IsHost_ptr, sizeof(int))))
    if(srand(1) RandVar = rand())
    if (host[CORE_PATH/][RAND]/ (srand(1) RandVar) < 1)
  
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}