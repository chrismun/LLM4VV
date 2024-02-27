#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 1234
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    int *a;
    int n = 1024;
    int i;

    // Allocate memory for a on the host
    a = (int*)malloc(n * sizeof(int));

    // Initialize a on the host
    for(i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }

    // Declare a variable in device memory and initialize structured reference counter
    #pragma acc declare create(a[0:n])

    // Copy data to the device explicitly and increment present counter
    #pragma acc enter data copyin(a[0:n])

    // Perform some computations on 'a' in parallel
    #pragma acc parallel loop
    for(i = 0; i < n; i++) {
        a[i] += 1;
    }

    // Copy data back to the host explicitly and decrement present counter
    #pragma acc exit data copyout(a[0:n])

    // Check the results
    for(i = 0; i < n; i++) {
        if(a[i] != ((rand() % 100) + 1)) { // Re-seed and calculate expected value
            err++;
            break;
        }
    }

    // Cleanup
    free(a);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    srand(SEED);

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if (failcode == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    return failcode;
}