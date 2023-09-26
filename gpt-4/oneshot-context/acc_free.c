interface. This is a basic check and the code may need to be adjusted based on the specifics of your runtime environment.

Here is a simple example using CUDA as the backend:

```C
#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

#define SIZE 100

int main() {
    int *data_host, *data_dev, i;
    int error_count = 0; 

    // Allocate host memory
    data_host = (int*)malloc(SIZE*sizeof(int));

    // Initialize host data
    for(i=0; i<SIZE; i++)
        data_host[i] = i;

    // Allocate device memory
    data_dev = (int*)acc_malloc(SIZE*sizeof(int));

    // Copy host to device
    acc_memcpy_to_device(data_dev, data_host, SIZE*sizeof(int));

    // Free device memory
    acc_free(data_dev);

    // Try to copy data back to host, it should fail because we freed device memory
    acc_memcpy_to_device(data_host, data_dev, SIZE*sizeof(int));

    for(i=0; i<SIZE; i++) {
        if (data_host[i] != i) {
            error_count++;
        }
    }

    if(error_count != 0)
        printf("Test failed! %d errors found.\n", error_count);
    else
        printf("Test passed!\n");

    // Free host memory
    free(data_host);

    return error_count;
}