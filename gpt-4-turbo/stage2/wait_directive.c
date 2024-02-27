#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
// T1:wait directive, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    int *b = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    int async_tag = 1;

    // Async operation using OpenACC
#pragma acc data copy(a[0:size]) copyout(b[0:size])
    {
#pragma acc parallel loop async(async_tag)
        for (int i = 0; i < size; ++i) {
            b[i] = a[i] + 1;
        }
    }

    // Wait for the async operation to complete
#pragma acc wait(async_tag)

    // Verify results
    for (int i = 0; i < size; ++i) {
        if (b[i] != a[i] + 1) {
            err++;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}