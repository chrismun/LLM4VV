c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Scenario 1: The data section is in shared memory, and the dynamic reference counter is zero.
    int *data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    acc_copyout(data, sizeof(int) * 10);
    acc_delete(data, sizeof(int) * 10);
    if (data[0] != 0) {
        err = 1;
    }

    // Scenario 2: The data section is not in shared memory, and the dynamic reference counter is zero.
    data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    acc_copyout(data, sizeof(int) * 10);
    acc_delete(data, sizeof(int) * 10);
    if (data[0] != 0) {
        err = 1;
    }

    // Scenario 3: The data section is in shared memory, and the dynamic reference counter is non-zero.
    data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    acc_copyout(data, sizeof(int) * 10);
    acc_delete(data, sizeof(int) * 10);
    if (data[0] != 0) {
        err = 1;
    }

    // Scenario 4: The data section is not in shared memory, and the dynamic reference counter is non-zero.
    data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    acc_copyout(data, sizeof(int) * 10);
    acc_delete(data, sizeof(int) * 10);
    if (data[0] != 0) {
        err = 1;
    }

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