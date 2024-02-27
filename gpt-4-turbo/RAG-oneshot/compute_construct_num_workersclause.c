#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 10000
#define NUM_WORKERS 4  // Example value, the actual optimal number depends on the target device

int test_num_workers(){
    int err = 0;
    float * a = (float *)malloc(n * sizeof(float));
    float * b = (float *)malloc(n * sizeof(float));
    
    srand(SEED);
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (float)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc parallel num_workers(NUM_WORKERS) copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            b[x] = sqrt(a[x]); // A simple computation
        }
    }

    // Simple correctness check
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - sqrt(a[x])) > 1e-5){
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed = test_num_workers();
    
    if (failed != 0){
        failcode = 1;
        printf("Test failed with %d errors.\n", failed);
    }else{
        printf("Test passed.\n");
    }
    
    return failcode;
}