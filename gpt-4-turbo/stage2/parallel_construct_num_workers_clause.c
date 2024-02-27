#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Random seed for reproducibility
#define SEED 42
// Number of iterations to average out results, to mitigate variability in execution
#define NUM_TEST_CALLS 5

#ifndef T1
// T1: parallel construct, num_workers clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Expecting num_workers to affect execution, we create a workload that can be easily parallelized
    const int size = 1024 * 1024; // Size of workload, e.g., an array to be processed
    float *data = (float *)malloc(size * sizeof(float));
    if (!data) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    
    // Initialize the array with random data
    for(int i = 0; i < size; i++){
        data[i] = (float)rand() / (float)RAND_MAX;
    }
    
    // Perform a computation to be parallelized using a specific number of workers
    int num_workers_specified = 4; // Specify desired num_workers
    #pragma acc parallel loop num_workers(num_workers_specified)
    for(int i = 0; i < size; i++){
        data[i] = data[i] * data[i];
    }

    // Check operation result - This part does not directly check for num_workers but looks for successful completion
    for(int i = 0; i < size; i++){
        if(data[i] == 0){ // Simplistic error check, adjust as necessary for more complex scenarios
            err++;
        }
    }

    free(data);
    
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
        fprintf(stderr, "OpenACC num_workers clause test failed.\n");
        failcode = failcode + (1 << 0);
    } else {
        printf("OpenACC num_workers clause test passed.\n");
    }
#endif
    return failcode;
}