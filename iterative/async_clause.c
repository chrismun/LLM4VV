#include "acc_testsuite.h"

#ifndef T1
//T1:async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100000;
    int *data = (int*)malloc(n * sizeof(int));
    int sum = 0;
    int expected_sum = 0;

    // Initialize data and compute expected sum
    for(int i = 0; i < n; i++){
        data[i] = rand() % 100;
        expected_sum += data[i];
    }

    // Compute sum using OpenACC
    #pragma acc parallel loop async(1) copy(data[0:n]) reduction(+:sum)
    for(int i = 0; i < n; i++){
        sum += data[i];
    }

    // Wait for all kernels to finish
    #pragma acc wait

    // Check if the computed sum matches the expected sum
    if(sum != expected_sum){
        err++;
        printf("Error: computed sum does not match expected sum\n");
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
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}