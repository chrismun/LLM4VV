#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = 4;
    int num_threads = 8;
    int num_blocks = 2;

    #pragma acc kernels num_workers(num_workers)
    {
        #pragma acc parallel num_threads(num_threads)
        {
            #pragma acc loop
            for (int i = 0; i < num_blocks; i++) {
                #pragma acc loop
                for (int j = 0; j < num_threads; j++) {
                    #pragma acc loop
                    for (int k = 0; k < num_workers; k++) {
                        // Do some work here
                    }
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