#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SEED 42
#define N 100
#define NUM_TEST_CALLS 10

// Utility function for generating a known test scenario.
void init_array(int *a, int n) {
    srand(SEED);
    for(int i = 0; i < n; i++) {
        a[i] = rand() % 100; // Populate with random integers
    }
}

int test1(){
    int err = 0;
    int data[N], sequential_result[N];
    init_array(data, N);

    // Generating sequential results for verification
    sequential_result[0] = data[0];
    for (int i = 1; i < N; ++i){
        sequential_result[i] = sequential_result[i-1] + data[i];
    }

    // OpenACC parallel region with a forcibly sequential loop
    #pragma acc parallel num_gangs(1)
    {
        #pragma acc loop seq
        for(int i = 1; i < N; ++i) {
            data[i] = data[i-1] + data[i];
        }
    }

    // Checking the result
    for(int i = 0; i < N; ++i) {
        if(data[i] != sequential_result[i]) {
            err = 1; // Error if any discrepancy
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}