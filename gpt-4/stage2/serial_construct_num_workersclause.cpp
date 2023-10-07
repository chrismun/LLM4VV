#include "acc_testsuite.h"

#ifndef T1
/*T1:serial construct num_workersclause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int num_workers;
    int expected_result = 0;
    int actual_result = 0;

    #pragma acc parallel num_workers(5)
    {
        #pragma acc loop worker reduction(+:expected_result)
        for(int i = 0; i < 5; i++) {
            expected_result += i;
        }
 
        // Get the number of workers
        num_workers = acc_get_num_workers();

        #pragma acc loop worker reduction(+:actual_result)
        for(int i = 0; i < num_workers; i++) {
            actual_result += i;
        }
    }

    if(expected_result != actual_result){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}