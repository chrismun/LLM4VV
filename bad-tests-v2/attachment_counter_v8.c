#include <stdlib.h>
#include <openacc.h>
#include <assert.h>

#define SIZE 1000
#define NUM_ITERATIONS 10

int main() {
    int *host_array, *device_array;
    int i, j;

    host_array = (int *)malloc(SIZE * sizeof(int));
    for(i = 0; i < SIZE; ++i) {
        host_array[i] = i;
    }

    // allocate device memory and check if it is done successfully
    device_array = (int *)acc_malloc(SIZE * sizeof(int));
    assert(device_array != NULL);

    // attach and detach actions
    for(j = 0; j < NUM_ITERATIONS; ++j) {
        acc_attach(device_array);
        #pragma acc parallel loop present(device_array)
        for(i = 0; i < SIZE; ++i) {
            device_array[i] = host_array[i];
        }
        acc_detach(device_array);
    }

    // validate that all elements have maintained their data throughout the attach/detach actions
    #pragma acc update host(device_array[0:SIZE])
    for(i = 0; i < SIZE; ++i) {
        assert(device_array[i] == host_array[i]);
    }

    free(host_array);
    acc_free(device_array);

    return 0;
}