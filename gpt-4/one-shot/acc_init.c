#include "openacc.h"   // OpenACC library
#include <stdio.h>     // Provides printf
#include <stdlib.h>    // Provides EXIT_SUCCESS
#include <stdbool.h>   // Provides bool

bool validateHostData(int* data, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (data[i] != value) {
            return false;
        }
    }
    return true;
}

void init(int* data, int size, int value) {
    #pragma acc parallel loop copyout(data[0:size])
    for (int i = 0; i < size; ++i) {
        data[i] = value;
    }
}

int main() {
    int size = 1 << 20; // Array size
    int *data = (int*)malloc(size * sizeof(int));
    init(data, size, 42);

    if (acc_is_present(data, size * sizeof(int))) {
        printf("Data is present on the device\n");
    } else {
        printf("Data is not present on the device\n");
    }

    bool isValid = validateHostData(data, size, 42);
    if (isValid) {
        printf("The test PASSED!\n");
    } else {
        printf("The test FAILED!\n");
    }

    free(data);
    return EXIT_SUCCESS;
}