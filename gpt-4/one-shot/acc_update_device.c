#include <openacc.h>
#include <stdlib.h>
#include <assert.h>

// Size of the array
#define N (1024*1024)

// Initialize an array on the host
void init(float *a, int n) {
    for(int i = 0; i < n; i++)
        a[i] = (float)i;
}

// Increment all elements of an array on the device
#pragma acc routine
void inc(float *a, int n) {
    #pragma acc loop
    for(int i = 0; i < n; i++) {
        a[i]++;
    }
}

int main() {
    float *a;

    // Allocate memory on the host
    a = (float*) malloc(N*sizeof(float));

    // Initialize the array
    init(a, N);

    // Copy the array to the device
    #pragma acc enter data copyin(a[0:N]) 

    // Increment the array on the device
    #pragma acc parallel
    {
        inc(a, N);
    }

    // Update the host copy of the array
    #pragma acc update host(a[0:N])

    // Check that the array has been correctly incremented
    for(int i = 0; i < N; i++) {
        assert(a[i] == (float)i + 1);
    }

    // Deallocate memory on both the host and the device
    #pragma acc exit data delete(a)
    free(a);

    return EXIT_SUCCESS;
}