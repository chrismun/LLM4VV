#include <stdio.h>
#include <openacc.h>

int main()
{
    size_t size = sizeof(int) * 100;

    // Allocate memory on the device
    void* ptr = acc_malloc(size);

    if (NULL == ptr) {
        fprintf(stderr, "Failed to allocate memory on the device\n");
        return -1;
    }

    // Associate the device pointer with a host pointer
    int* hostPtr = NULL;
#pragma acc host_data use_device(ptr)
    {
        hostPtr = (int*) acc_hostptr(ptr);
    }

    if (NULL == hostPtr) {
        fprintf(stderr, "Failed to get the host pointer associated with the device pointer\n");
        return -1;
    }

    printf("Host Pointer: %p\n", (void*)hostPtr);

    // Free the device memory
    acc_free(ptr);

    return 0;
}