#include "acc_testsuite.h"
#ifndef T1
// T1: loop construct private clause, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int sum = 0;
    int x = 0;

    #pragma acc parallel loop private(x)
    for (int i = 0; i < TEST_LOOP_SIZE; ++i) {
        x = i;
        sum += x;
    }

    for (int i = 0; i < TEST_LOOP_SIZE; ++i) {
        int expected = i;
        if (x != expected) {
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
        failed += test1();
    }
    if (failed != 0) {
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}