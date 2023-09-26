#include <stdio.h>
#include <openacc.h>

int main(void) {
    int n = 100;
    float * hostData = (float*)malloc(n * sizeof(float));
    float * deviceData;

    // Initialize hostData
    for(int i = 0; i < n; i++) {
        hostData[i] = (float)i;
    }

    #pragma acc enter data create(deviceData[0:n])

    #pragma acc parallel loop present(deviceData)
    for(int i = 0; i < n; i++) {
        deviceData[i] = hostData[i] * 2;
    }

    // Get updated deviceData back to the host
    acc_update_self(hostData, n * sizeof(float));

    #pragma acc exit data delete(deviceData)

    // print the data to check
    for(int i = 0; i < n; i++) {
        printf("%.2f ", hostData[i]);
    }
    printf("\n");

    free(hostData);

    return 0;
}