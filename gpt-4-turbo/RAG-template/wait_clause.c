#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

int test_wait_clause(){
    int err = 0;
    const int size = 1024;
    int *a, *b;
    int i;

    a = (int*)malloc(size*sizeof(int));
    b = (int*)malloc(size*sizeof(int));
    
    // Initialize arrays
    for(i = 0; i < size; ++i){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:size]) copyout(b[0:size])
    {
        #pragma acc parallel loop async(1)
        for(i = 0; i < size; ++i){
            b[i] = a[i] + 1;
        }

        // Wait for all operations in the async queue 1 to complete
        #pragma acc wait(1)

        #pragma acc parallel loop async(2)
        for(i = 0; i < size; ++i){
            b[i] = b[i] + 1;
        }

        // Without a specific async queue wait, it waits for all operations to complete
        #pragma acc wait
    }

    // Verify
    for(i = 0; i < size; ++i){
        if(b[i] != a[i] + 2){
            err++;
            printf("Test failed at index %d: expected %d, got %d\n", i, a[i]+2, b[i]);
            break;
        }
    }

    free(a);
    free(b);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_wait_clause();
    }
    if (failed != 0){
        failcode = 1;
    }

    if(failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed.\n");
    }

    return failcode;
}