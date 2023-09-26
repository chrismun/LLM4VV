c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Test 1: Data section is in shared memory
    int *data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    int *dev_data = (int *)acc_create(data, sizeof(int) * 10);
    if (dev_data != data) {
        err = 1;
    }
    free(data);

    // Test 2: Data section is present in the current device memory
    int *data2 = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data2[i] = i;
    }
    int *dev_data2 = (int *)acc_create(data2, sizeof(int) * 10);
    if (dev_data2 != data2) {
        err = 1;
    }
    free(data2);

    // Test 3: Data section is not present in the current device memory
    int *data3 = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data3[i] = i;
    }
    int *dev_data3 = (int *)acc_create(data3, sizeof(int) * 10);
    if (dev_data3 == data3) {
        err = 1;
    }
    free(data3);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}