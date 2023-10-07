#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define PRECISION 0.001

int main() {
    int failcode = 0;
    int failed = 0;
    int dev_num = 0;
    int dev_type = acc_device_nvidia;
    int property = acc_property_memory;
    size_t result;

    result = acc_get_property(dev_num, dev_type, property);
    if (result == 0) {
        printf("Test failed: acc_get_property returned 0\n");
        failcode = failcode + (1 << 0);
    } else {
        printf("Test passed: acc_get_property returned %zu\n", result);
    }

    return failcode;
}