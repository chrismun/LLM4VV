#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    #pragma acc parallel deviceptr(a, b)
    {
        #pragma acc loop
        for (int i = 0; i < 10; i++){
            a[i] = i;
            b[i] = i * 2;
        }
    }

    #pragma acc parallel deviceptr(a, b)
    {
        #pragma acc loop
        for (int i = 0; i < 10; i++){
            if (a[i] != i || b[i] != i * 2){
                err = 1;
            }
        }
    }

    free(a);
    free(b);

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