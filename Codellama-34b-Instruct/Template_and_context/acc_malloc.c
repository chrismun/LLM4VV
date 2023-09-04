#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ACC_MALLOC(bytes) acc_malloc(bytes)

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc_malloc with a valid size
    failed = 0;
    for (int x = 0; x < 10; ++x) {
        void* ptr = ACC_MALLOC(100);
        if (ptr == NULL) {
            failed++;
        }
        free(ptr);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: acc_malloc with an invalid size
    failed = 0;
    for (int x = 0; x < 10; ++x) {
        void* ptr = ACC_MALLOC(-1);
        if (ptr != NULL) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: acc_malloc with a size of 0
    failed = 0;
    for (int x = 0; x < 10; ++x) {
        void* ptr = ACC_MALLOC(0);
        if (ptr != NULL) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    return failcode;
}