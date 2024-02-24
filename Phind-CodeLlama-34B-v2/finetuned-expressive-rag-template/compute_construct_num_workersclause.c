#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = rand() % 10 + 1;
    int num_gangs = rand() % 10 + 1;
    int total_workers = num_workers * num_gangs;

    int *a = (int *)malloc(total_workers * sizeof(int));
    int *b = (int *)malloc(total_workers * sizeof(int));

    for (int i = 0; i < total_workers; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers)
    {
        int worker = acc_worker_id();
        int gang = acc_gang_id();
        int global_worker_id = gang * num_workers + worker;

        #pragma acc loop
        for (int i = 0; i < total_workers; i++) {
            if (i == global_worker_id) {
                b[i] = a[i];
            }
        }
    }

    for (int i = 0; i < total_workers; i++) {
        if (i < num_workers) {
            if (b[i] != i) {
                err = 1;
                break;
            }
        } else {
            if (b[i] != 0) {
                err = 1;
                break;
            }
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