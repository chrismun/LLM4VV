#include "acc_testsuite.h"

#define SIZE 10000

int test(){
    int err = 0;
    int reduced_value_cpu, reduced_value_gpu;
    int* values = (int*) malloc(sizeof(int)*SIZE);

    // Initialize values
    for (int i = 0; i < SIZE; i++) {
        values[i] = i+1;
    }

    reduced_value_cpu = 0;
    // CPU reduction
    for (int i = 0; i < SIZE; i++) {
        reduced_value_cpu += values[i];
    }

    reduced_value_gpu = 0;
    #pragma acc parallel loop reduction(+:reduced_value_gpu)
    for (int i = 0; i < SIZE; i++) {
        reduced_value_gpu += values[i];
    }

    if (reduced_value_cpu != reduced_value_gpu) {
        err = 1;
    }

    free(values);

    return err;
}

int main(){
    int failcode = 0;
    int num_failed = 0;

    num_failed = test();
    if (num_failed > 0) {
        printf("Test failed with %d errors\n", num_failed);
        failcode = 1;
    }

    return failcode;
}