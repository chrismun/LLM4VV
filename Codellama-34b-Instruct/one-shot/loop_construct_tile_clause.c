#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define TILE_SIZE 16

int test_loop_tile(int n) {
    int err = 0;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc kernels loop tile(TILE_SIZE)
        for (int i = 0; i < n; i++) {
            b[i] = a[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (b[i] != a[i]) {
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        failed = test_loop_tile(i);
        if (failed != 0) {
            failcode = failcode + (1 << i);
        }
    }

    return failcode;
}