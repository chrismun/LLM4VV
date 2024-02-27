#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef T1
//T1:{loop, tile},V:2.7-3.3
#define MATRIX_SIZE 100
#define TILE_SIZE 10

int test1(){
    int err = 0;
    srand(SEED);

    float matrixA[MATRIX_SIZE][MATRIX_SIZE];
    float matrixB[MATRIX_SIZE][MATRIX_SIZE];
    float resultTiled[MATRIX_SIZE][MATRIX_SIZE] = {0};
    float resultNonTiled[MATRIX_SIZE][MATRIX_SIZE] = {0};

    // Initialize matrices
    for (int i = 0; i < MATRIX_SIZE; ++i){
        for (int j = 0; j < MATRIX_SIZE; ++j){
            matrixA[i][j] = (float)rand() / RAND_MAX;
            matrixB[i][j] = (float)rand() / RAND_MAX;
        }
    }

    // Matrix addition with tiling
    #pragma acc parallel loop tile(TILE_SIZE, TILE_SIZE)
    for (int i = 0; i < MATRIX_SIZE; ++i){
        for (int j = 0; j < MATRIX_SIZE; ++j){
            resultTiled[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    // Matrix addition without tiling for validation
    for (int i = 0; i < MATRIX_SIZE; ++i){
        for (int j = 0; j < MATRIX_SIZE; ++j){
            resultNonTiled[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    // Validate results
    for (int i = 0; i < MATRIX_SIZE; ++i){
        for (int j = 0; j < MATRIX_SIZE; ++j){
            if (resultTiled[i][j] != resultNonTiled[i][j]) {
                printf("Mismatch at %d,%d: Tiled=%f, Non-Tiled=%f\n", i, j, resultTiled[i][j], resultNonTiled[i][j]);
                err++;
            }
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