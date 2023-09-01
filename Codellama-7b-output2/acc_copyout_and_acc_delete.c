#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    int *data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = rand() % 100;
    }

    int *copyout_data = (int *)malloc(sizeof(int) * 10);

    #pragma acc parallel loop copyout(data)
    for (int i = 0; i < 10; i++) {
        copyout_data[i] = data[i];
    }

    #pragma acc parallel loop delete(data)
    for (int i = 0; i < 10; i++) {
        data[i] = 0;
    }

    for (int i = 0; i < 10; i++) {
        if (copyout_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    free(data);
    free(copyout_data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}