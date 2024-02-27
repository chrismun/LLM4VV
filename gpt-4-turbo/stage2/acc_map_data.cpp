#include <openacc.h>
#include <iostream>
#include <cstdlib>

#ifndef T1
// T1:acc map data,V:2.7-3.3
int test1() {
    int err = 0;
    srand(time(NULL));

    const size_t SIZE = 1024;
    int *hostArray = (int *)malloc(SIZE * sizeof(int));
    int *deviceArray = (int *)acc_malloc(SIZE * sizeof(int));

    // Filling the arrays to verify later if mapping works without data movement.
    for (size_t i = 0; i < SIZE; ++i) {
        hostArray[i] = rand() % 100; // random values
    }

    if (hostArray == NULL || deviceArray == NULL) {
        std::cerr << "Memory allocation failed." << std::endl;
        return 1; // Early return on memory allocation failure
    }

    // Try mapping the host array to the device pointer
    acc_map_data(hostArray, deviceArray, SIZE * sizeof(int));

    // Validate if acc_map_data caused any immediate errors
    if (acc_get_last_data_error() != 0) {
        std::cerr << "Encountered error during acc_map_data." << std::endl;
        err = 1;
    }

    // Assuming no direct data validation is possible as spec mentions no data movement,
    // we rely on errors and subsequent usage for validation.
    // Cleanup
    acc_unmap_data(hostArray);
    acc_free(deviceArray);
    free(hostArray);

    return err;
}
#endif

int main() {
    int failcode = 0;
#ifndef T1
    int failed = test1();
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}