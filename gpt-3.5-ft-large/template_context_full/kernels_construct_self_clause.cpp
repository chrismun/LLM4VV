#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct self clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(true){
        #pragma acc kernels self(conditional: _dev_a[0:n])
            for(i = 0; i < n; i++){
                _dev_a[i] = 1;
            }
    }
        
         if(_dev_a.lengh > 0){
            for(int x = 0; x < _dev_a.length; ++x){
                if(_dev_a[x] != 1.0){
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