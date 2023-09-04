#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the tile sizes
    int tile_sizes[3] = {16, 32, 64};

    // Initialize the loop bounds
    int loop_bounds[3] = {100, 200, 300};

    // Initialize the loop indices
    int loop_indices[3] = {0, 0, 0};

    // Loop over the tile sizes
    for (int i = 0; i < 3; i++) {
        // Set the tile size for the current loop
        int tile_size = tile_sizes[i];

        // Set the loop bounds for the current loop
        int loop_bound = loop_bounds[i];

        // Set the loop index for the current loop
        int loop_index = loop_indices[i];

        // Loop over the elements in the current loop
        for (int j = 0; j < loop_bound; j++) {
            // Check if the current element is within the tile
            if (j >= tile_size) {
                // If the current element is within the tile, increment the loop index
                loop_index++;
            }
        }

        // Check if the loop index is within the tile
        if (loop_index >= tile_size) {
            // If the loop index is within the tile, increment the error count
            err++;
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