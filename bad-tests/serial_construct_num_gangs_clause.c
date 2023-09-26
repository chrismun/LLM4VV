#include "acc_testsuite.h"

#ifndef T1
/*T1:serial construct num_gangs clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    char verify[NUM_GANGS];
    int real_num_gangs;
    
    #pragma acc data create(verify[0:NUM_GANGS])
    {
        #pragma acc serial num_gangs(NUM_GANGS) copy(real_num_gangs)
        {
            real_num_gangs = _acc_num_gangs();
            verify[real_num_gangs - 1] = real_num_gangs;
        }

        for (int x = 0; x < real_num_gangs; ++x) {
            if (verify[x] != x+1) {
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