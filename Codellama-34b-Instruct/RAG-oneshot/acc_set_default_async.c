#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc_set_default_async with a valid async argument
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int async_arg = rand() % 100;
        acc_set_default_async(async_arg);
        if (acc_get_default_async() != async_arg) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: acc_set_default_async with acc_async_default
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        acc_set_default_async(acc_async_default);
        if (acc_get_default_async() != acc_async_default) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: acc_set_default_async with acc_async_noval
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        acc_set_default_async(acc_async_noval);
        if (acc_get_default_async() != acc_async_noval) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    // Test 4: acc_set_default_async with an invalid async argument
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int async_arg = rand() % 100;
        acc_set_default_async(async_arg);
        if (acc_get_default_async() == async_arg) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 3);
    }

    return failcode;
}