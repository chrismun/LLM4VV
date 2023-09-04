#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: declare directive with no variables
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        #pragma acc declare
        {
            // Do nothing
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: declare directive with one variable
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = 0;
        #pragma acc declare create(a)
        {
            a = 1;
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: declare directive with multiple variables
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = 0, b = 0;
        #pragma acc declare create(a, b)
        {
            a = 1;
            b = 2;
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    // Test 4: declare directive with a variable that is already declared
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = 0;
        #pragma acc declare create(a)
        {
            a = 1;
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 3);
    }

    // Test 5: declare directive with a variable that is not declared
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        #pragma acc declare create(a)
        {
            a = 1;
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 4);
    }

    // Test 6: declare directive with a variable that is not used
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = 0;
        #pragma acc declare create(a)
        {
            // Do nothing
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 5);
    }

    // Test 7: declare directive with a variable that is used in a loop
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = 0;
        #pragma acc declare create(a)
        {
            for (int i = 0; i < 10; ++i) {
                a = i;
            }
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 6);
    }

    // Test 8: declare directive with a variable that is used in a nested loop
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = 0;
        #pragma acc declare create(a)
        {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    a = i * j;
                }
            }
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 7);
    }

    // Test 9: declare directive with a variable that is used in a function call
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = 0;
        #pragma acc declare create(a)
        {
            a = foo(a);
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 8);
    }

    // Test 10: declare directive with a variable that is used in a nested function call
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int a = 0;
        #pragma acc declare create(a)
        {
            a = foo(bar(a));
        }
        failed = failed + (acc_get_device_type() != acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 9);
    }

    return failcode;
}

int foo(int a) {
    return a + 1;
}

int bar(int a) {
    return a * 2;
}