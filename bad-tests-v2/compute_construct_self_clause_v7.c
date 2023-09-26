#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 100;
    const float multiplication_factor = 2.0;
    float* data = (float*)malloc(size * sizeof(float));

    for (int i = 0; i < size; i++) {
        data[i] = (float)rand() / RAND_MAX;
    }

    if (!acc_is_present(data, size * sizeof(float))) {
        #pragma acc parallel loop copy(data[0:size]) self(acc_is_present(data, size * sizeof(float)))
        for (int i = 0; i < size; i++) {
            data[i] *= multiplication_factor;
        }
    }

    if (acc_is_present(data, size * sizeof(float))) {
        err = 1;
    }

    free(data);
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
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}