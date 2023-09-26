#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    const int n = 10;
    int *hostData = (int *)malloc(n * sizeof(int));
    int *deviceData = (int *)acc_malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        hostData[i] = i;
    }
    
    acc_memcpy_to_device(deviceData, hostData, n * sizeof(int));
    
    printf("Data copied to device:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", deviceData[i]);
    }
    printf("\n");
    
    acc_free(deviceData);
    free(hostData);
    
    return 0;