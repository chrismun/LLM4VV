#include <stdio.h>
#include <openacc.h>

int main()
{
     // Set bytes to allocate
    size_t N = sizeof(int) * 512;

    // Use OpenACC to allocate memory on the device
    int* ptr = (int*) acc_malloc(N);

    // Check if memory was allocated successfully
    if (ptr == NULL) {
        fprintf(stderr, "Failed to allocate device memory\n");
        return -1;
    }

    // Do other operations...

    // Don't forget to free the allocated memory
    acc_free(ptr);

    return 0;