#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_DEVICES 2
#define N 1024

int main() {
    int i, j, err = 0;
    int *a, *b;
    int devices[NUM_DEVICES];

    // Initialize data
    a = (int *) malloc(N * sizeof(int));
    b = (int *) malloc(N * sizeof(int));
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Get the available devices
    acc_get_devices(devices, NUM_DEVICES);

    // Test acc_set_device_num
    for (i = 0; i < NUM_DEVICES; i++) {
        acc_set_device_num(i, acc_device_host);
        #pragma acc data copyin(a[0:N]) copyout(b[0:N])
        {
            #pragma acc parallel loop
            for (j = 0; j < N; j++) {
                b[j] = a[j];
            }
        }

        // Check results
        for (j = 0; j < N; j++) {
            if (b[j] != a[j]) {
                err++;
                break;
            }
        }
    }

    // Print result
    if (err) {
        printf("Validation failed with %d errors\n", err);
    } else {
        printf("Validation passed\n");
    }

    // Cleanup
    free(a);
    free(b);

    return err;
}