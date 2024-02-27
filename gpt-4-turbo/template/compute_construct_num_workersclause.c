#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1000;
    const int num_workers = 4;  // Example number of workers to test. Adjust based on hardware.
    int counts[size];
    int expected_counts[size / num_workers]; 

    for (int i = 0; i < size; ++i) {
        counts[i] = 0;
    }
    for (int i = 0; i < size / num_workers; ++i) {
        expected_counts[i] = 0;
    }

    #pragma acc parallel loop num_workers(num_workers)
    for (int i = 0; i < size; ++i) {
        int id = i % (size / num_workers); // Calculate an ID based on expected division of work
        #pragma acc atomic
        counts[i]++;
        #pragma acc atomic
        expected_counts[id]++;
    }

    // Verify the expected distribution of work among workers
    for (int i = 0; i < size / num_workers; ++i) {
        if (expected_counts[i] != num_workers) {
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