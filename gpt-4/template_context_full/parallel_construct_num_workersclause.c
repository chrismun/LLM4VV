#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct num_workersclause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    
    int num_workers = 4; // can be any desired number that target architecture supports
    int num_gangs = 10; // can be any desired number that target architecture supports

    int results[num_gangs * num_workers];

    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers) copy(results[0:num_gangs * num_workers])
    {
        int gang_id = __pgi_gangidx();
        int worker_id = __pgi_workeridx();
        results[gang_id * num_workers + worker_id] = gang_id * num_workers + worker_id;
    }
    
    // Check results
    for(int i = 0; i < num_gangs * num_workers; ++i)
    {
        if(results[i] != i){
            err = 1;
            break;
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