#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#ifndef T1
//T1:loop,tile,V:1.0-3.1
#define n 100 // Assume n is a perfect square for simplicity
#define TILE_SIZE_X 10
#define TILE_SIZE_Y 10

int test_tile_clause(){
    int err = 0;
    srand(SEED);
    float matrixA[n][n], matrixB[n][n], result_parallel[n][n], result_serial[n][n];

    // Initialize matrices
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            matrixA[i][j] = rand() / (float)RAND_MAX;
            matrixB[i][j] = rand() / (float)RAND_MAX;
            result_parallel[i][j] = 0;
            result_serial[i][j] = 0;
        }
    }

    // Serial matrix addition for verification
    for (int y = 0; y < n; ++y){
        for (int x = 0; x < n; ++x){
            result_serial[y][x] = matrixA[y][x] + matrixB[y][x];
        }
    }

    // Parallel matrix addition using OpenACC
    #pragma acc data copyin(matrixA, matrixB), copy(result_parallel)
    {
        #pragma acc parallel loop tile(TILE_SIZE_Y, TILE_SIZE_X)
        for (int y = 0; y < n; ++y){
            for (int x = 0; x < n; ++x){
                result_parallel[y][x] = matrixA[y][x] + matrixB[y][x];
            }
        }
    }

    // Verify results
    for (int y = 0; y < n; ++y){
        for (int x = 0; x < n; ++x){
            if (fabs(result_parallel[y][x] - result_serial[y][x]) > PRECISION){
                err += 1;
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
        failed += test_tile_clause();
    }
    if (failed != 0){
        failcode |= (1 << 0);
    }
#endif

    if (failcode) {
        printf("Test failed\n");
    } else {
        printf("All tests passed\n");
    }

    return failcode;
}