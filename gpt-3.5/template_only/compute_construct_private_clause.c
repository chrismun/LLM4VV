#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data pcopy(x, y)
    {
        int x[NUM_DEVICES], y[NUM_DEVICES];
        int thread_num = omp_get_thread_num();
        
        #pragma acc compute private(x, y)
        for(int i = 0; i < NUM_DEVICES; i++) {
            x[i] = rand();
            y[i] = x[i] * 2;
        }
        
        for(int i = 0; i < NUM_DEVICES; i++) {
            if(x[i] % 2 != 0 || y[i] != x[i] * 2) {
                err = 1;
                break;
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