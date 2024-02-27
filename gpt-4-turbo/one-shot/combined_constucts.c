#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 1000
#define SEED 123
#define PRECISION 0.001

int test_parallel_loop_copy(){
    int err = 0;
    srand(SEED);
    float * a = (float *)malloc(n * sizeof(float));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (float)(RAND_MAX / 10);
    }

    #pragma acc parallel loop copy(a[0:n])
    for (int x = 0; x < n; ++x){
        a[x] = a[x] + 1;
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - ((rand() / (float)(RAND_MAX / 10)) + 1)) > PRECISION){
            err += 1;
        }
    }

    free(a);
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = test_parallel_loop_copy();
   
    if (failed != 0){
        failcode = 1; // indicates some tests failed
        printf("Test FAILED with %d errors.\n", failed);
    } else {
        printf("Test PASSED.\n");
    }
    
    return failcode;
}