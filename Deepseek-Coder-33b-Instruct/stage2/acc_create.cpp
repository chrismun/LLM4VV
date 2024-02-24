#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *h_a = (int*)malloc(N * sizeof(int));
    int *d_a;

    // Initialize host array
    for(int i = 0; i < N; i++) {
        h_a[i] = i;
    }

    // Create device array
    d_a = (int*)acc_create(h_a, N * sizeof(int));

    // Check if data is correctly copied
    for(int i = 0; i < N; i++) {
        if(h_a[i] != d_a[i]) {
            return 1; // Return non-zero if data is not correctly copied
        }
    }

    free(h_a);
    acc_delete(d_a, N * sizeof(int));

    return 0; // Return 0 if data is correctly copied
}