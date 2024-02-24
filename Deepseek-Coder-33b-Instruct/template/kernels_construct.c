#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000000
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int *data = (int*)malloc(N * sizeof(int));
    int expected_result = 0;
    int actual_result = 0;

    // Initialize data and compute expected result
    for(int i = 0; i < N; i++){
        data[i] = rand() % 100;
        expected_result += data[i];
    }

    // Perform parallel reduction using OpenACC
    #pragma acc parallel loop copyin(data[0:N]) copy(actual_result)
    for(int i = 0; i < N; i++){
        actual_result += data[i];
    }

    // Check if the results match
    if(expected_result != actual_result){
        err = 1;
    }

    free(data);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}