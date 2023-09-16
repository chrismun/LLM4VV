#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 1000;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy data to the device
    #pragma acc enter data copyin(a[0:n])

    // Check if data is present on the device
    int is_present = acc_is_present(a, n * sizeof(int));

    if (is_present) {
        printf("Data is present on the device.\n");
    } else {
        printf("Data is not present on the device.\n");
    }

    // Copy data back to the host
    #pragma acc exit data copyout(a[0:n])

    // Cleanup
    free(a);
    free(b);

    return 0;
}