#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct tile clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_tiles = 10;
    int tile_size = 10;
    int num_iterations = 100;

    #pragma acc parallel loop tile(num_tiles, tile_size)
    for (int i = 0; i < num_iterations; i++) {
        // Do some work
    }

    if (num_tiles * tile_size != num_iterations) {
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}