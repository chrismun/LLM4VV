#include <stdio.h>
#include <openacc.h>

int main() {
    int a[100];
    int *dev_ptr;

    // Initialize the array
    for(int i = 0; i < 100; i++) {
        a[i] = i;
    }

    // Copy the array to the device
    #pragma acc data copyin(a)
    {
        // Get the default device pointer
        #pragma acc get default async(dev_ptr)

        // Wait for the copy to complete
        #pragma acc wait

        // Print the first element of the array
        printf("First element of the array: %d\n", dev_ptr[0]);
    }

    return 0;
}