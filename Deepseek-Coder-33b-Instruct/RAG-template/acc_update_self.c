#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int i;

    // Initialize the array
    for(i = 0; i < N; i++) {
        a[i] = i;
    }

    // Update the array in parallel
    #pragma acc parallel loop present(a[0:N])
    for(i = 0; i < N; i++) {
        a[i] = a[i] * 2;
    }

    // Check the results
    for(i = 0; i < N; i++) {
        if(a[i] != i * 2) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All tests passed.\n");
    return 0;
}