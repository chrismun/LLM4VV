#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of random integers
    int arr[100];
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 100;
    }

    // Create a tile size of 10
    int tile_size = 10;

    // Create a loop construct with the tile clause
    #pragma acc loop tile(tile_size)
    for (int i = 0; i < 100; i++) {
        // Do some computation on the array
        arr[i] += 1;
    }

    // Check that the tile size is correct
    if (tile_size != 10) {
        err = 1;
    }

    // Check that the loop has been tiled correctly
    for (int i = 0; i < 100; i++) {
        if (arr[i] != i + 1) {
            err = 1;
            break;
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