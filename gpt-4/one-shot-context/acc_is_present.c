#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main(int argc, char* argv[]) {
    int n = 100;  // Define the size of the array
    float *a = (float *)malloc(n * sizeof(float));

    for(int i=0; i<n; i++)
        a[i] = (float)i;

    // Moving data to device memory explicitly (host --> device)
    #pragma acc enter data copyin(a[0:n])

    // Check if data is present in device
    if(acc_is_present(a, n*sizeof(float))) {
        printf("Test passed. Array 'a' is present in device memory\n");
    } else {
        printf("Test failed. Array 'a' is not found in device memory\n");
    }

    #pragma acc exit data delete(a[0:n])  // Remove data from device memory

    // Check data presence again after deletion from device memory
    if(acc_is_present(a, n*sizeof(float))) {
        printf("Test failed. Array 'a' is still present in device memory after deletion\n");     
    } else {
        printf("Test passed. Array 'a' is not present in device memory after deletion\n");
    }

    // Free the host memory
    free(a);

    return 0;
}