#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int test1(){
    int err = 0;
    int i;
    int sum = 0;
    int sum_host = 0;
    int *a = (int*)malloc(N * sizeof(int));

    // Initialize array with random numbers
    for(i = 0; i < N; i++){
        a[i] = rand() % 100;
        sum_host += a[i];
    }

    // Compute sum of array in parallel using OpenACC
    #pragma acc parallel loop async(1) copy(sum)
    for(i = 0; i < N; i++){
        sum += a[i];
    }

    // Wait for the compute region to finish
    #pragma acc wait

    // Check that the sum computed by the compute region matches the sum computed by the host
    if(sum != sum_host){
        err = 1;
    }

    free(a);

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