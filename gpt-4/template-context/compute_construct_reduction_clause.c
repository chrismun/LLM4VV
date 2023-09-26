#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 10000
#define ERROR_THRESH 1e-15

#define random_number() ((double)rand() / RAND_MAX)

double openacc_reduction_sum(double* a, int len) {
    double sum = 0.0;
    #pragma acc parallel loop reduction(+:sum)
    for (int i = 0; i < len; ++i) {
        sum += a[i];
    }
    return sum;
}

double sequential_reduction_sum(double* a, int len) { 
    double sum = 0.0;
    for (int i = 0; i < len; ++i) {
        sum += a[i];
    }
    return sum;
}

int test_reduction_sum() {
    int err = 0;
    srand(SEED);

    double* a = (double*)malloc(sizeof(double) * LENGTH);
    for (int i = 0; i < LENGTH; ++i) {
        a[i] = random_number();
    }

    double result_openacc = openacc_reduction_sum(a, LENGTH);
    double result_seq = sequential_reduction_sum(a, LENGTH);

    if (fabs(result_openacc - result_seq) > ERROR_THRESH) {
        err = 1;
    }

    free(a);
    return err;
}

int main(){
    int failcode = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failcode += test_reduction_sum();
    }
    if (failcode != 0){
        printf("Test failed! Total failures: %d\n", failcode);
    }
    else {
        printf("All tests passed!\n");
    }
    return failcode;
}