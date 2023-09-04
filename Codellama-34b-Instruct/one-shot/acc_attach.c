#include <openacc.h>

int main() {
    int *a, *b;
    int n = 100;

    // Allocate memory on the host
    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));

    // Initialize the host memory
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Attach the device memory to the host memory
    #pragma acc attach copyin(a[0:n])
    {
        #pragma acc kernels
        {
            // Copy the device memory to the host memory
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                b[i] = a[i];
            }
        }
    }

    // Detach the device memory from the host memory
    #pragma acc detach copyout(b[0:n])

    // Verify that the host memory has been updated
    for (int i = 0; i < n; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
        }
    }

    // Free the host memory
    free(a);
    free(b);

    return 0;
}