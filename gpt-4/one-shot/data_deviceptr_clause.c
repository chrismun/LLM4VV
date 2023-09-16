#include <stdlib.h>
#include <openacc.h>

void test_deviceptr() {
    int * h_array = NULL;
    int * d_array = NULL;
    int N = 1000;

    // Allocate host array
    h_array = (int*) malloc(N * sizeof(int));

    // Initialize host array
    for(int i = 0; i < N; ++i) {
        h_array[i] = i;
    }

    // Allocate device array
    d_array = (int*) acc_malloc(N * sizeof(int));

    // Copy host array to device
    acc_memcpy_to_device(d_array, h_array, N * sizeof(int));

    // Modify the device array
    #pragma acc parallel loop deviceptr(d_array)
    for(int i = 0; i < N; ++i) {
        d_array[i] += 1;
    }

    // Copy device array back to host
    acc_memcpy_from_device(h_array, d_array, N * sizeof(int));

    // Validate
    for(int i = 0; i < N; ++i) {
        if(h_array[i] != i+1) {
            printf("Validation failed at element %d! Found %d, expected %d\n", i, h_array[i], i+1);
        }
    }

    // Cleanup
    acc_free(d_array);
    free(h_array);
}

int main() {
    test_deviceptr();
    return 0;
}