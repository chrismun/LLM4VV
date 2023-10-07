#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_WORKERS 4

int main() {
    int num_devices = acc_get_num_devices(acc_device_nvidia);
    if (num_devices == 0) {
        printf("No NVIDIA GPUs found. Exiting...\n");
        return 0;
    }

    acc_set_device_num(0, acc_device_nvidia);

    int num_workers_set[NUM_WORKERS];
    int num_workers_actual[NUM_WORKERS];

    for (int i = 0; i < NUM_WORKERS; i++) {
        num_workers_set[i] = i + 1;
    }

    for (int i = 0; i < NUM_WORKERS; i++) {
        #pragma acc parallel num_workers(num_workers_set[i])
        {
            num_workers_actual[i] = acc_get_num_workers();
        }
    }

    int error = 0;
    for (int i = 0; i < NUM_WORKERS; i++) {
        if (num_workers_set[i] != num_workers_actual[i]) {
            printf("Error: Expected %d workers, but got %d workers\n", num_workers_set[i], num_workers_actual[i]);
            error = 1;
        }
    }

    if (!error) {
        printf("Test passed: num_workers clause is correctly implemented\n");
    }

    return 0;
}