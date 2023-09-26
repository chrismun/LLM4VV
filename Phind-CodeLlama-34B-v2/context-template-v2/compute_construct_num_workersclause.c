#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int err = 0;
    int num_workers = 4;
    int gang_size = 16;
    int num_gangs = 1;
    int total_workers = num_gangs * gang_size;
    int *a = (int *)malloc(total_workers * sizeof(int));
    int *b = (int *)malloc(total_workers * sizeof(int));
    int *c = (int *)malloc(total_workers * sizeof(int));

    for (int x = 0; x < total_workers; ++x){
        a[x] = x;
        b[x] = x * 2;
        c[x] = 0;
    }

    #pragma acc parallel num_workers(num_workers) num_gangs(num_gangs)
    {
        int worker = acc_worker_id();
        int gang = acc_gang_id();
        int global_id = gang * gang_size + worker;
        c[global_id] = a[global_id] + b[global_id];
    }

    for (int x = 0; x < total_workers; ++x){
        if (c[x] != a[x] + b[x]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

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