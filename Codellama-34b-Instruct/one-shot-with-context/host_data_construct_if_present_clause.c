#include <openacc.h>

int main() {
    int failcode = 0;
    int failed;

    // Set up data
    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Create a host_data construct with an if_present clause
    #pragma acc host_data if_present(a[0:10])
    {
        // Copy data from device to host
        #pragma acc kernels copyout(b[0:10])
        {
            #pragma acc loop
            for (int i = 0; i < 10; i++) {
                b[i] = a[i];
            }
        }
    }

    // Check that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (b[i] != a[i]) {
            failcode = 1;
            break;
        }
    }

    // Clean up data
    free(a);
    free(b);

    return failcode;
}