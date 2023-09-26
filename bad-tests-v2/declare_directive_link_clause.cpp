#include "acc_testsuite.h"
#include <cstdlib>
#include <cmath>

#pragma acc declare link(foo)
int foo; 

// Testing function with acc routine
#pragma acc routine seq
int square_foo(){
    return foo * foo;
}

int test(){
    int err = 0;
    srand(SEED);
    foo = rand() % 100;

    #pragma acc data copyout(foo)
    foo = square_foo();

    int hostResult = foo;
    foo = rand() % 100;
    int expected = foo * foo;

    if (abs(expected - hostResult) > PRECISION){
        err = 1;
    }
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test();
    }

    if (failed != 0){
        failcode = failcode + (1 << 1);
    }

    return failcode;
}