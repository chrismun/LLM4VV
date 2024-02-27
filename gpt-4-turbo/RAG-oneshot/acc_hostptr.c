#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100
#define PRECISION 0.00001

int main() {
    float *hostArray;
    float *deviceArray;
    float *retrievedHostPtr;
    int i, errors = 0;
  
    hostArray = (float *)malloc(N * sizeof(float));
  
    // Initialize host array
    for(i = 0; i < N; i++) {
        hostArray[i] = i * 1.0f;
    }
    
    // Copy data to device
    #pragma acc enter data copyin(hostArray[0:N])
    deviceArray = acc_deviceptr(hostArray);
  
    // Use acc_hostptr to retrieve the host pointer from the device pointer
    retrievedHostPtr = (float *)acc_hostptr(deviceArray);
  
    // Check if the retrieved host pointer matches the original host pointer
    if (retrievedHostPtr != hostArray) {
        printf("Test Failed: Retrieved host pointer does not match the original host pointer.\n");
        errors++;
    }
    
    // Validate data integrity by comparing values
    #pragma acc exit data copyout(hostArray[0:N])
    for(i = 0; i < N; i++) {
        if(abs(hostArray[i] - i * 1.0f) > PRECISION) {
            printf("Test Failed: Data integrity check failed at index %d.\n", i);
            errors++;
            break;
        }
    }
  
    if(errors == 0){
        printf("All tests passed.\n");
    } else {
        printf("Errors found.\n");
    }
  
    free(hostArray);
    return errors;
}