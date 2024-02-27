#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <openacc.h>

// Seed for srand
#define SEED 12345
// Number of loops for the test
#define N 10000
// Number of test calls
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Array for testing
    float *test_array = (float *)malloc(N * sizeof(float));

    // Initialize array
    for (int i = 0; i < N; ++i){
        test_array[i] = rand() / (float)RAND_MAX;
    }

    float sum = 0.0f;
    // Gang parallel loop to calculate sum
    #pragma acc parallel loop reduction(+:sum) gang
    for (int i = 0; i < N; i++){
        sum += test_array[i];
    }

    // Calculate the expected sum serially
    float expected_sum = 0.0f;
    for (int i = 0; i < N; i++){
        expected_sum += test_array[i];
    }

    // Check if there's a significant error
    if (fabs(sum - expected_sum) > 0.001 * fabs(expected_sum)) {
        err++;
    }

    free(test_array);
    
    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    
    if(failcode == 0){
        printf("PASS: Gang clause functions as expected.\n");
    }else{
        printf("FAIL: Gang clause resulted in errors.\n");
    }

    return failcode;
}