#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_serial_construct(int n) {
    int err = 0;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc serial
    {
        #pragma acc loop
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
        failed = test_serial_construct(i);
        if (failed != 0) {
            failcode = failcode + (1 << i);
        }
    }

    if (failcode != 0) {
        printf("Test failed with failcode %d\n", failcode);
    } else {
        printf("Test passed\n");
    }

    return failcode;
}