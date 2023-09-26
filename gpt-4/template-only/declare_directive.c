#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 1000
#define SEED 12345
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    int a[SIZE], b[SIZE], i;

    srand(SEED);
    for(i = 0; i < SIZE; i++)
        a[i] = rand();

    #pragma acc declare copyin(a[0:SIZE]) copyout(b[0:SIZE])
    #pragma acc parallel loop
    for(i = 0; i < SIZE; i++)
        b[i] = a[i];

    for(i = 0; i < SIZE; i++)
        if(a[i] != b[i]) {
            printf("Mismatch at position %d: %d vs %d\n", i, a[i], b[i]);
            err = 1;
            break;
        }

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

    if(failcode != 0)
        printf("Test failed with error code %d\n", failcode);
    else 
        printf("Test passed successfully\n");

    return failcode;
}