#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    // Initialize the arrays
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy data to the device
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        // Copy data from the device to the host
        #pragma acc kernels copy(a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                b[i] = a[i];
            }
        }
    }

    // Delete the arrays
    acc_delete(a, sizeof(int) * n);
    acc_delete(b, sizeof(int) * n);

    return 0;
}