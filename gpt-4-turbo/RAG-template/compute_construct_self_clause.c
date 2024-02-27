#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef T1
// T1: { feature: "self clause" }, Version: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int N = 1024;
    int *a = (int *)malloc(sizeof(int) * N);
    int *b = (int *)malloc(sizeof(int) * N);
    int *c = (int *)malloc(sizeof(int) * N);
    bool executeOnHost = true;  // Change this to control where the computation should happen

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

#pragma acc data copyin(a[0:N], b[0:N]) copy(c[0:N])
    {
#pragma acc parallel loop self(executeOnHost)
        for (int i = 0; i < N; ++i) {
            c[i] = a[i] + b[i];
        }
    }

    // Verification
    for (int i = 0; i < N; ++i) {
        if (c[i] != a[i] + b[i]) {
            err++;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}