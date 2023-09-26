#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct tile clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int tile_size = 16;
    int num_tiles = 4;
    int num_elements = 1024;

    // Create a 2D array of size num_tiles x num_elements
    int** tile_array = (int**)malloc(num_tiles * sizeof(int*));
    for (int i = 0; i < num_tiles; i++) {
        tile_array[i] = (int*)malloc(num_elements * sizeof(int));
    }

    // Initialize the array with random values
    for (int i = 0; i < num_tiles; i++) {
        for (int j = 0; j < num_elements; j++) {
            tile_array[i][j] = rand() % 100;
        }
    }

    // Tile the array
    for (int i = 0; i < num_tiles; i++) {
        for (int j = 0; j < num_elements; j += tile_size) {
            int tile_start = j;
            int tile_end = j + tile_size - 1;
            if (tile_end >= num_elements) {
                tile_end = num_elements - 1;
            }
            for (int k = tile_start; k <= tile_end; k++) {
                tile_array[i][k] = tile_array[i][k] + 1;
            }
        }
    }

    // Check the result
    for (int i = 0; i < num_tiles; i++) {
        for (int j = 0; j < num_elements; j++) {
            if (tile_array[i][j] != (rand() % 100) + 1) {
                err = 1;
                break;
            }
        }
    }

    // Free the memory
    for (int i = 0; i < num_tiles; i++) {
        free(tile_array[i]);
    }
    free(tile_array);

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