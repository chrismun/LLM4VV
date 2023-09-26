#include <stdio.h>
#include <openacc.h>

float* host_data;
float* device_data;

int main() {
    int i, num_elements = 10000, errors = 0;

    // Allocate host memory
    host_data = (float*) malloc(num_elements * sizeof(float));

    // Initialize host data
    for (i = 0; i < num_elements; ++i) {
        host_data[i] = (float)i;
    }

    // Allocate device memory (returns a device pointer)
    device_data = acc_copyin(host_data, num_elements * sizeof(float)); 

    if(device_data == NULL) {
      fprintf(stderr, "Error allocating device memory\n");
      return 1;
    }

    acc_create(host_data, num_elements * sizeof(float)); // Create data region without uploading data.
 
    #pragma acc parallel loop
    for(i = 0; i < num_elements; ++i) {
        if(host_data[i] != device_data[i]) errors++;
    }

    printf("Num errors: %d\n", errors);

    return 0;
}