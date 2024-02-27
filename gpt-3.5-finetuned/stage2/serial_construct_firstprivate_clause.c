#include "acc_testsuite.h"
#ifndef T1
//T1:serial,firstprivate,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    #pragma acc parallel loop reduction(+:err) num_gangs(1) vector_length(1)
    for (int x = 0; x < 1; ++x){
        int firstprivate = rand() / (real_t)(RAND_MAX/10);
        real_t y[10] = {
            firstprivate, firstprivate, firstprivate, firstprivate, firstprivate,
            firstprivate, firstprivate, firstprivate, firstprivate, firstprivate
        };
        for (int y_index = 0; y_index < 10; ++y_index){
            if (fabs(y[y_index] - firstprivate) > PRECISION){
                err += 1;
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