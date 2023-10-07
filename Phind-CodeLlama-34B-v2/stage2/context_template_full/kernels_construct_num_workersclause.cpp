#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct num_workersclause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = 4;
    int num_gangs = 2;
    int total_workers = num_gangs * num_workers;

    int* a = (int*)malloc(total_workers * sizeof(int));
    int* b = (int*)malloc(total_workers * sizeof(int));

    for (int x = 0; x < total_workers; ++x){
        a[x] = rand() % 100;
        b[x] = 0;
    }

    #pragma acc kernels num_workers(num_workers) num_gangs(num_gangs)
    {
        int worker_id = acc_worker_id();
        int gang_id = acc_gang_id();
        int global_id = gang_id * num_workers + worker_id;
        b[global_id] = a[global_id] * 2;
    }

    for (int x = 0; x < total_workers; ++x){
        if (b[x] != a[x] * 2){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

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