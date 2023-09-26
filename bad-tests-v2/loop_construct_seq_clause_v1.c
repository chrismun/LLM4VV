#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    int a[10];
    int b[10];

    srand(SEED);

    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 10;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:10]) create(b[0:10])
    #pragma acc parallel loop seq
    for (int i = 0; i < 10; i++) {
        b[i] = a[i] * a[i];
    }
    #pragma acc exit data delete(a, b)

    for (int i = 0; i < 10; i++) {
        if (b[i] != a[i] * a[i]) {
            err = 1;
            break;
        }
    }

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