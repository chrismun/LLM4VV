#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct num_workersclause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = 4; // Choose a value for num_workers
    int gang_size = 16; // Choose a value for gang_size

    #pragma acc parallel num_workers(num_workers) gang(gang_size)
    {
        int worker_id = acc_get_thread_id();
        int num_active_workers = acc_get_num_workers();

        if (worker_id >= num_active_workers) {
            err = 1;
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