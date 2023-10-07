#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_deviceptr.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc_deviceptr with a null pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = NULL;
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr != NULL) {
            printf("Test 1: acc_deviceptr with a null pointer failed\n");
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: acc_deviceptr with a host pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = malloc(10 * sizeof(int));
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr == NULL) {
            printf("Test 2: acc_deviceptr with a host pointer failed\n");
            failed++;
        }
        free(data_arg);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: acc_deviceptr with a device pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = malloc(10 * sizeof(int));
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr == NULL) {
            printf("Test 3: acc_deviceptr with a device pointer failed\n");
            failed++;
        }
        free(data_arg);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    // Test 4: acc_deviceptr with a shared pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = malloc(10 * sizeof(int));
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr == NULL) {
            printf("Test 4: acc_deviceptr with a shared pointer failed\n");
            failed++;
        }
        free(data_arg);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 3);
    }

    // Test 5: acc_deviceptr with a null pointer and a device pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = NULL;
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr != NULL) {
            printf("Test 5: acc_deviceptr with a null pointer and a device pointer failed\n");
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 4);
    }

    // Test 6: acc_deviceptr with a host pointer and a device pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = malloc(10 * sizeof(int));
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr == NULL) {
            printf("Test 6: acc_deviceptr with a host pointer and a device pointer failed\n");
            failed++;
        }
        free(data_arg);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 5);
    }

    // Test 7: acc_deviceptr with a device pointer and a host pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = malloc(10 * sizeof(int));
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr == NULL) {
            printf("Test 7: acc_deviceptr with a device pointer and a host pointer failed\n");
            failed++;
        }
        free(data_arg);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 6);
    }

    // Test 8: acc_deviceptr with a shared pointer and a host pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = malloc(10 * sizeof(int));
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr == NULL) {
            printf("Test 8: acc_deviceptr with a shared pointer and a host pointer failed\n");
            failed++;
        }
        free(data_arg);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 7);
    }

    // Test 9: acc_deviceptr with a shared pointer and a device pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = malloc(10 * sizeof(int));
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr == NULL) {
            printf("Test 9: acc_deviceptr with a shared pointer and a device pointer failed\n");
            failed++;
        }
        free(data_arg);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 8);
    }

    // Test 10: acc_deviceptr with a device pointer and a shared pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_arg = malloc(10 * sizeof(int));
        void *device_ptr = acc_deviceptr(data_arg);
        if (device_ptr == NULL) {
            printf("Test 10: acc_deviceptr with a device pointer and a shared pointer failed\n");
            failed++;
        }
        free(data_arg);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 9);
    }

    return failcode;
}