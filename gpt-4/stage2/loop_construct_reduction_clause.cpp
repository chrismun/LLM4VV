#include "acc_testsuite.h"
#include <openacc.h>

int test() {
    const int length = 100;
    const int reduction_target = length * (length - 1) / 2;
    int host_array[length] = {0};
    for (int i = 0; i < length; ++i) {
        host_array[i] = i;
    }

    int reduction_output = 0;
#pragma acc parallel copyin(host_array[0:length]) reduction(+:reduction_output)
    {
    #pragma acc loop
        for(int i = 0; i < length; ++i) {
            reduction_output += host_array[i];
        }
    }

    if (reduction_output != reduction_target) {
        return 1; // Error occurred
    } else {
        return 0; // No error
    }
}

int main() {
    int error = 0;

    // Repeated testing to ensure accuracy
    for (int i = 0; i < 10; ++i) {
        error += test();
    }

    return error;
}