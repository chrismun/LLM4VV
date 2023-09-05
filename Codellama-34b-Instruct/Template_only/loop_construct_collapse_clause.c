#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int num_loops = 10;
    int num_iterations = 100;
    int num_threads = 4;

    // Initialize data
    int* data = (int*)malloc(num_loops * num_iterations * sizeof(int));
    for (int i = 0; i < num_loops * num_iterations; i++) {
        data[i] = i;
    }

    // Create OpenACC data environment
    acc_create(data, num_loops * num_iterations * sizeof(int));

    // Create OpenACC loop construct
    acc_loop(num_loops, num_iterations, num_threads, data);

    // Collapse loop construct
    acc_collapse(num_loops, num_iterations, num_threads, data);

    // Verify that the data has been updated correctly
    for (int i = 0; i < num_loops * num_iterations; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

    // Clean up
    acc_delete(data);

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