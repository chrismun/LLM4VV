#include "acc_testsuite.h"
#ifndef T1
//T1:atomic construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a = 0;
    #pragma acc kernels
    {
        #pragma acc loop gang
        for (int x = 0; x < 10; ++x){
            #pragma acc loop worker
            for (int y = 0; y < 10; ++y){
                #pragma acc loop vector
                for (int z = 0; z < 10; ++z){
                    #pragma acc atomic update
                        a = a + 1;
                }
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