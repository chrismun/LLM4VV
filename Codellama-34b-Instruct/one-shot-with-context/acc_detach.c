#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    // Initialize arrays
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Detach device from host thread
    acc_detach(a);

    // Copy data from device to host
    acc_copyout(b, a, sizeof(int) * 10);

    // Check if data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (b[i] != a[i]) {
            err++;
        }
    }

    // Reattach device to host thread
    acc_attach(a);

    // Copy data from device to host
    acc_copyout(b, a, sizeof(int) * 10);

    // Check if data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (b[i] != a[i]) {
            err++;
        }
    }

    // Detach device from host thread and attach it to a different host thread
    acc_detach(a);
    acc_attach(b);

    // Copy data from device to host
    acc_copyout(a, b, sizeof(int) * 10);

    // Check if data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i]) {
            err++;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Test 1: Detach device from host thread
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: Detach device from host thread and then reattach it
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: Detach device from host thread and then attach it to a different host thread
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    return failcode;
}