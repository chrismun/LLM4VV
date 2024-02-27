#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int num_gangs = 5;
    int count[num_gangs];
    for (int i = 0; i < num_gangs; ++i) {
        count[i] = 0;
    }
    
    #pragma acc parallel num_gangs(num_gangs) copy(count)
    {
        int gang_id = acc_gang_id();
        if (gang_id < num_gangs) {
            count[gang_id] = 1;
        }
    }

    for (int i = 0; i < num_gangs; ++i) {
        if (count[i] != 1) {
            err++;
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