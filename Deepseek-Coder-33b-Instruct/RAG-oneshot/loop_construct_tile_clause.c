#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define TILE_DIM 32
#define SIZE 1024

int main() {
    int *a = (int*)malloc(SIZE * SIZE * sizeof(int));
    int *b = (int*)malloc(SIZE * SIZE * sizeof(int));

    // Initialize array a
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            a[i*SIZE + j] = i*SIZE + j;
        }
    }

    // Tile the array
    #pragma acc data copyin(a[0:SIZE*SIZE]) copyout(b[0:SIZE*SIZE])
    {
        #pragma acc parallel loop tile(TILE_DIM,TILE_DIM)
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                b[i*SIZE + j] = a[i*SIZE + j];
            }
        }
    }

    // Verify the results
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(b[i*SIZE + j] != a[i*SIZE + j]) {
                printf("Verification failed at index (%d, %d)\n", i, j);
                return 1;
            }
        }
    }

    printf("Verification passed\n");
    return 0;
}