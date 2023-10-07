#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test_acc_get_property(int dev_num, acc_device_t dev_type, acc_device_property_t property) {
    size_t value;
    const char* string_value;

    value = acc_get_property(dev_num, dev_type, property);
    string_value = acc_get_property_string(dev_num, dev_type, property);

    if (value == 0 && string_value == NULL) {
        printf("Error: acc_get_property returned 0 and acc_get_property_string returned NULL\n");
        return 1;
    }

    if (value != 0 && string_value == NULL) {
        printf("Error: acc_get_property returned non-zero value, but acc_get_property_string returned NULL\n");
        return 1;
    }

    if (value == 0 && string_value != NULL) {
        printf("Error: acc_get_property returned 0, but acc_get_property_string returned non-NULL value\n");
        return 1;
    }

    return 0;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test_acc_get_property(x, acc_device_current, acc_property_memory);
        failed = failed + test_acc_get_property(x, acc_device_current, acc_property_free_memory);
        failed = failed + test_acc_get_property(x, acc_device_current, acc_property_shared_memory_support);
        failed = failed + test_acc_get_property(x, acc_device_current, acc_property_name);
        failed = failed + test_acc_get_property(x, acc_device_current, acc_property_vendor);
        failed = failed + test_acc_get_property(x, acc_device_current, acc_property_driver);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}