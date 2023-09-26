#include <openacc.h>
#include <stdio.h>

#define ARRAY_SIZE 10000000
#define NUM_TEST_CALLS 10

int test_wait_all(){

    int fail_count = 0;
    int *A = (int *) malloc(ARRAY_SIZE * sizeof(int));
    int *B = (int *) malloc(ARRAY_SIZE * sizeof(int));
    int *C = (int *) malloc(ARRAY_SIZE * sizeof(int));
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        A[i] = i;
        B[i] = i;
    }
    
    #pragma acc parallel async(1)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] + B[i];
    }

    acc_wait_all();

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (C[i] != i + i) {
            fail_count++;
        }
    }

    free(A);
    free(B);
    free(C);
    
    return fail_count;
}

int main(){
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_wait_all();
    }
    
    if (failed == 0){
        printf("Test Passed\n");
    } else {
        printf("Test Failed: %d failures\n", failed);
    }

    return failed;
}