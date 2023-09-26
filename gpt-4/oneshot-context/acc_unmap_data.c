#include "openacc.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    const int N = 200;
    float *hostData, *deviceData;

    /* Allocate space for the host and device data */
    hostData = (float*)malloc(N * sizeof(float));
    deviceData = acc_malloc(N * sizeof(float));

    /* Populate host data */
    for (int i = 0; i < N; ++i) {
        hostData[i] = i;
    }

    /* Copy data to the device */
    acc_memcpy_to_device(deviceData, hostData, N * sizeof(float));

    /* Map the device data to the host data */
    acc_map_data(hostData, deviceData, N * sizeof(float));

    /* Perform actions & computations on device.... */


    /* Unmap the device data from the host data */
    acc_unmap_data(hostData);

    /* Clean up */
    acc_free(deviceData);
    free(hostData);

    return 0;
}