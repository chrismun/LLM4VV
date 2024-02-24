#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int test1(){
    int err = 0;
    int i;
    int sum = 0;
    int sum_gpu = 0;
    int *a = (int*)malloc(N * sizeof(int));

    // Initialize array with random numbers
    for(i = 0; i < N; i++){
        a[i] = rand() % 100;
    }

    // Perform reduction on CPU
    for(i = 0; i < N; i++){
        sum += a[i];
    }

    // Perform reduction on GPU
    #pragma acc data copy(a[0:N])
    {
        #pragma acc parallel loop async(1)
        for(i = 0; i < N; i++){
            sum_gpu += a[i];
        }
        #pragma acc wait
    }

    // Check if the results are the same
    if(sum != sum_gpu){
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