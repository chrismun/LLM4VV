#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int err = 0;
    int num_workers = 4;
    int gang_size = 16;
    int num_gangs = 1;
    int total_workers = num_gangs * num_workers;
    int data[total_workers];
    int host_data[total_workers];

    for (int x = 0; x < total_workers; ++x){
        data[x] = -1;
        host_data[x] = -1;
    }

    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers) copy(data(_length(total_workers)))
    {
        int worker = acc_worker_id();
        int gang = acc_gang_id();
        int global_id = gang * num_workers + worker;
        data[global_id] = global_id;
    }

    for (int x = 0; x < total_workers; ++x){
        if (data[x] != x){
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