#include "openacc.h"
#include <stdio.h>

void verify(int *data, int size) {
    for (int i = 0; i < size; ++i) {
        if (data[i] != i) {
            printf("Data verification failed at index: %d\n", i);
            return;
        }
    }
    printf("Data verification successful.\n");
}

int main() {
    const int size = 10000;
    int data[size];

    for (int i = 0; i < size; ++i) {
        data[i] = 0;
    }

    int async = acc_async_test_all();

    if (async != 0) {
        printf("Before computation, async value is not zero. Value: %d\n", async);
    }

    #pragma acc parallel loop async
    for (int i = 0; i < size; ++i) {
        data[i] = i;
    }

    async = acc_async_test_all();

    if (async != 0) {
        printf("After computation, async value is not zero. Value: %d\n", async);
    }

    #pragma acc wait

    verify(data, size);

    return 0;
}