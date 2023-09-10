#include "acc_testsuite.h"

int test() {
    int err = 0;
    srand((unsigned)time(NULL));

    int original = rand() % 100;  // initialize a random value
    int copy;

    #pragma acc parallel private(copy)
    {
        copy = original;  // private clause will ensure that copy of the variable is created for every gang
        original = 0;     // change original in one gang. Shouldn't affect copy in other gangs
    }

    // If OpenACC's private clause is implemented correctly, `copy` should remain unaltered
    if (copy != original) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failcode += test();
    }

    return failcode;
}