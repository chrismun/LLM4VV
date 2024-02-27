#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);
    const int size = 10000;
    int *a = (int *) malloc(size * sizeof(int));
    int *b = (int *) malloc(size * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100; // Random numbers between 0 and 99
        b[i] = 0; // Initialize all elements to 0
    }

    // Apply the OpenACC parallel directive with async
    #pragma acc parallel loop async(1) copyin(a[0:size]) copyout(b[0:size])
    for (int i = 0; i < size; ++i) {
        b[i] = a[i] + 1;
    }

    // Use acc_wait to ensure that the async operation has completed
    acc_wait(1);

    // Verify the operation
    for (int i = 0; i < size; ++i) {
        if (b[i] != a[i] + 1) {
            err++;
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

    if (failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }

    return failcode;
}