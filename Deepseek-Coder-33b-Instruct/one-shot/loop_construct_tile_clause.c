#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define TILE_DIM 16

int main() {
    int n = 1024; // size of the 2D array
    int *a = (int*)malloc(n * n * sizeof(int)); // 2D array
    int *b = (int*)malloc(n * n * sizeof(int)); // result array

    // Initialize the 2D array
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            a[i*n + j] = i*n + j;
        }
    }

    // Tile the loop
    #pragma acc data copyin(a[0:n*n]) copyout(b[0:n*n])
    {
        #pragma acc parallel loop tile(TILE_DIM,TILE_DIM)
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                b[i*n + j] = a[i*n + j] * 2; // some operation
            }
        }
    }

    // Verify the result
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(b[i*n + j] != a[i*n + j] * 2) {
                printf("Verification failed at index (%d, %d)\n", i, j);
                return 1;
            }
        }
    }

    printf("Verification passed\n");
    return 0;
}