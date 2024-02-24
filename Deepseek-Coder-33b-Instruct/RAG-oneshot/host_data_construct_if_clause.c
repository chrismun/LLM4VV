#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    // Initialize array a
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }

    // Copy array a to device
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        // Copy array a to array b on device
        #pragma acc host_data use_device(a, b)
        {
            // Copy array a to array b on device
            #pragma acc parallel loop
            for (int i = 0; i < n; i++) {
                b[i] = a[i];
            }
        }
    }

    // Check if array b is correctly copied from array a
    for (int i = 0; i < n; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}