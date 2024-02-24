#include <stdio.h>
#include <openacc.h>

int main() {
    int *ptr = (int*) malloc(sizeof(int));
    *ptr = 10;

    // Attach the pointer to the device
    #pragma acc data copyin(ptr[0:1])
    {
        #pragma acc update device(ptr[0:1])
    }

    // Detach the pointer from the device
    #pragma acc data detach(ptr[0:1])
    {
        // Check if the pointer is still valid
        if (acc_is_present(ptr, sizeof(int)) == 0) {
            printf("Pointer is not present on the device\n");
        } else {
            printf("Pointer is present on the device\n");
        }
    }

    free(ptr);
    return 0;
}