#include <stdbool.h>
#include <stddef.h>

bool acc_is_present(void *data_arg, size_t bytes) {
    // Check if the data is in shared memory
    if (data_arg == NULL) {
        return false;
    }

    // Check if the data is present in the current device memory
    if (bytes == 0) {
        return true;
    }

    // Check if the data is contiguous
    if (data_arg + bytes > data_arg) {
        return false;
    }

    // Check if the data is accessible from the current device
    if (data_arg + bytes < data_arg) {
        return false;
    }

    return true;
}