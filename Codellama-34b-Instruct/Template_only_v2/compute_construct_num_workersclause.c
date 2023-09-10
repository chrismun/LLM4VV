#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = 4;
    int num_threads = 8;
    int num_blocks = 2;

    #pragma acc parallel num_workers(num_workers)
    {
        int tid = acc_get_thread_id();
        int bid = acc_get_block_id();
        int gid = acc_get_global_id();

        if (tid < num_threads && bid < num_blocks) {
            // Do some work
        }
    }

    if (acc_get_num_workers() != num_workers) {
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