#include "stdio.h"
#include "openacc.h"

#define N 1000000

void waitForAllDevices() {
    int numDevices;
    acc_set_device_type(acc_device_not_host);
    numDevices = acc_get_num_devices(acc_get_device_type());

    for (int deviceId = 0; deviceId < numDevices; deviceId++) {
        acc_set_device_num(deviceId, acc_get_device_type());
        #pragma acc wait
    }
}

int main() {
    float* input = (float*) malloc(N * sizeof(float));
    float* output = (float*) malloc(N * sizeof(float));

    #pragma acc enter data copyin(input[0:N]) create(output[0:N])
    
    #pragma acc parallel loop present(input[0:N], output[0:N])
    for(int i = 0; i < N; i++) {
        output[i] = input[i] * input[i];
    }

    waitForAllDevices();

    #pragma acc update host(output[0:N])

    // Verify the results
    for(int i = 0; i < N; i++) {
        if(output[i] != input[i] * input[i]) {
            printf("Test failed!\n");
            return -1;
        }
    }

    printf("Test passed!\n");

    return 0;
}