#include <stdio.h>
#include <openacc.h>

int main() {
    int a[100], b[100];
    int i;

    // Initialize the arrays
    for (i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Offload the computation to the GPU
    #pragma acc data copy(a[0:100], b[0:100])
    {
        #pragma acc parallel loop
        for (i = 0; i < 100; i++) {
            b[i] = a[i] * 2;
        }

        // Detach the device
        acc_detach(acc_device_nvidia);

        // The following loop will be executed on the host
        #pragma acc loop
        for (i = 0; i < 100; i++) {
            b[i] = a[i] * 3;
        }
    }

    // Print the results
    for (i = 0; i < 100; i++) {
        printf("b[%d] = %d\n", i, b[i]);
    }

    return 0;
}