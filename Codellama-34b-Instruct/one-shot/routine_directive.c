#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_routine(int n, int *a, int *b) {
    int err = 0;
    int i;

    #pragma acc routine(routine_name)
    {
        #pragma acc loop
        for (i = 0; i < n; i++) {
            a[i] = b[i];
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    int n = 10;
    int a[n];
    int b[n];

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
    }

    failed = test_routine(n, a, b);

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}