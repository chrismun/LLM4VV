#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

#define SIZE 100

int main() {
    float *host = (float*) malloc(SIZE * sizeof(*host));
    float *device;

    for (int i = 0; i < SIZE; i++) {
        host[i] = i;
    }

    #pragma acc enter data create(host[0:SIZE])

    device = acc_deviceptr(host);
    
    if (device == NULL) {
    	printf("Test failed. acc_deviceptr returns NULL pointer. \n");
    	return EXIT_FAILURE;
    }

    // Clean up
    #pragma acc exit data delete(host[0:SIZE])

    free(host);

    printf("Test passed. acc_deviceptr returns a non-null pointer. \n");
    return EXIT_SUCCESS;	
}