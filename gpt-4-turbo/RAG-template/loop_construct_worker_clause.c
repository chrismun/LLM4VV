#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int size = 1024; // Array size for test
    int *a = (int *)malloc(size * sizeof(int));
    int *worker_ids = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i){
        a[i] = 0;
        worker_ids[i] = -1;
    }
    
    #pragma acc parallel num_workers(4) vector_length(128)
    {
        #pragma acc loop worker
        for (int i = 0; i < size; ++i){
            a[i] = 1;
            // Storing worker id for verification
            worker_ids[i] = acc_get_worker_num();
        }
    }
    
    // Verification
    int worker_count[4] = {0};
    for(int i = 0; i < size; ++i) {
        if(a[i] != 1) {
            err++;
            break;
        }
        if(worker_ids[i] >= 0 && worker_ids[i] < 4)
            worker_count[worker_ids[i]]++;
    }
    
    for (int i = 0; i < 4; ++i) {
        if(worker_count[i] == 0) { // Expecting each worker to handle part of the loop
            err++;
            break;
        }
    }
    
    free(a);
    free(worker_ids);
    
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