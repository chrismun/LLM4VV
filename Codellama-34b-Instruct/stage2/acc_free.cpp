#include <iostream>
#include <cstdlib>

void acc_free(void* data_dev) {
    // Check if data_dev is a null pointer
    if (data_dev == nullptr) {
        return;
    }

    // Free the memory on the current device
    free(data_dev);
}

int main() {
    // Allocate some memory on the current device
    void* data_dev = malloc(100);

    // Use the memory
    // ...

    // Free the memory
    acc_free(data_dev);

    return 0;
}