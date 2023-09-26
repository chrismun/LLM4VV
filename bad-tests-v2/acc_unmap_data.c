#include <openacc.h>

int main() {
    int failcode = 0;

    // Initialize data
    int n = 100;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Map data to device
    #pragma acc enter data copyin(a[0:n], b[0:n])

    // Perform computation on device
    #pragma acc kernels
    {
        #pragma acc loop
        for (int i = 0; i < n; i++) {
            b[i] = a[i] + 1;
        }
    }

    // Unmap data from device
    #pragma acc exit data delete(a[0:n], b[0:n])

    // Verify results
    for (int i = 0; i < n; i++) {
        if (fabs(b[i] - (a[i] + 1)) > PRECISION) {
            failcode = 1;
            break;
        }
    }

    // Clean up
    free(a);
    free(b);

    return failcode;
}