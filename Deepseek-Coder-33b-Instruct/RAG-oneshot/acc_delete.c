#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int *device_data;
    int i;

    // Initialize data
    for(i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Copy data to device
    device_data = (int*)acc_malloc(SIZE * sizeof(int));
    acc_memcpy_to_device(device_data, data, SIZE * sizeof(int));

    // Delete data from device
    acc_delete(device_data, SIZE * sizeof(int));

    // Check if data is still present in device memory
    int is_present = acc_is_present(device_data, SIZE * sizeof(int));
    if(is_present == 0) {
        printf("Data deleted successfully.\n");
    } else {
        printf("Data not deleted successfully.\n");
    }

    free(data);

    return 0;
}