#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100
#define TILE_SIZE 10

int main() {
    int a[N][N], b[N][N];
    int i, j, tile_i, tile_j;

    // Initialize the arrays
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = i + j;
            b[i][j] = 0;
        }
    }

    // Tile the loop
    #pragma acc data copyin(a) copyout(b)
    {
        #pragma acc parallel loop tile(TILE_SIZE,TILE_SIZE)
        for (tile_i = 0; tile_i < N; tile_i += TILE_SIZE) {
            for (tile_j = 0; tile_j < N; tile_j += TILE_SIZE) {
                #pragma acc loop
                for (i = tile_i; i < tile_i + TILE_SIZE; i++) {
                    for (j = tile_j; j < tile_j + TILE_SIZE; j++) {
                        b[i][j] = a[i][j];
                    }
                }
            }
        }
    }

    // Check the result
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (a[i][j] != b[i][j]) {
                printf("Error: a[%d][%d] = %d, b[%d][%d] = %d\n", i, j, a[i][j], i, j, b[i][j]);
                return 1;
            }
        }
    }

    printf("Test passed.\n");
    return 0;
}