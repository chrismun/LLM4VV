#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define SIZE 1000

int seq_implementation(int* arr, int size) {
    int total = 0;
    for(int i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
}

int test_num_gangs() {
    int *arr = (int*) malloc(SIZE * sizeof(int));
    for(int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;  // filling array with random numbers
    }
	
    int seq_result = seq_implementation(arr, SIZE);

    int acc_result = 0;
    #pragma acc parallel num_gangs(10) vector_length(32) copy(arr[0:SIZE])
    {
        #pragma acc loop gang reduction(+:acc_result)
        for(int i = 0; i < SIZE; i++) {
            acc_result += arr[i];
        }
    }

    // compare results
    if(seq_result != acc_result) {
        printf("Failed. Seq: %d, ACC: %d\n", seq_result, acc_result);
        free(arr);
        return 1;
    }

    printf("Passed.\n");
    free(arr);
    return 0;
}

int main() {
    srand(SEED);
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_num_gangs();
    }
    return failed;
}