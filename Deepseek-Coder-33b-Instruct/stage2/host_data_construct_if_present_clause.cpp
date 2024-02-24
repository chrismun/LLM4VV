#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int *ptr_a = a, *ptr_b = b;

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = -1;
    }

    // Copy data from host to device
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        // Use if_present clause to check if data is present on the device
        #pragma acc host_data if_present(ptr_a:length(N)) use_device(ptr_a)
        {
            // If data is present, copy it to the device
            #pragma acc parallel loop present(ptr_a[0:N])
            for (int i = 0; i < N; i++) {
                ptr_b[i] = ptr_a[i];
            }
        }
    }

    // Check if data was copied correctly
    for (int i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error: Data was not copied correctly\n");
            return 1;
        }
    }

    printf("Success: Data was copied correctly\n");
    return 0;
}