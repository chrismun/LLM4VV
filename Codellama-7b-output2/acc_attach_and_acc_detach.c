#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 10
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    int* data = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = rand() % 100;
    }

    #pragma acc attach(data)
    {
        for (int i = 0; i < 10; i++) {
            data[i] = data[i] * 2;
        }
    }

    #pragma acc detach(data)

    for (int i = 0; i < 10; i++) {
        if (data[i] != (rand() % 100) * 2) {
            err = 1;
        }
    }

    free(data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel loop num_gangs(NUM_TEST_CALLS)
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}