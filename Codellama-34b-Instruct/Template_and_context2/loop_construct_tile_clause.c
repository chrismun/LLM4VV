#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct tile clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the tile size to 16
    int tile_size = 16;

    // Create a loop nest with two loops
    #pragma acc loop tile(tile_size)
    for (int i = 0; i < 100; i += tile_size) {
        for (int j = 0; j < 100; j += tile_size) {
            // Do some work here
        }
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