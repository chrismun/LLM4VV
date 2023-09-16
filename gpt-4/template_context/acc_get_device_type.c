#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test_acc_get_device_type() {
    int errors = 0;

    acc_device_t device_type = acc_get_device_type();
    if(device_type != acc_device_none &&
       device_type != acc_device_default &&
       device_type != acc_device_host &&
       device_type != acc_device_not_host &&
       device_type != acc_device_cuda &&
       device_type != acc_device_radeon) {
        errors += 1;
    }
    return errors;
}

int main() {
    int total_errors = 0;
    srand(SEED);

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        total_errors += test_acc_get_device_type();
    }

    if(total_errors != 0) {
        printf("There are %d errors in acc_get_device_type implementation.\n", total_errors);
        return 1;
    }
    printf("acc_get_device_type() implementation passed all tests.\n");
    return 0;
}