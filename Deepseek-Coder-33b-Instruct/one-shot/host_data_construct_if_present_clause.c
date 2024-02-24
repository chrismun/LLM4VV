#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    #pragma acc data copyin(host_data[0:N]) copyout(device_data[0:N])
    {
        #pragma acc host_data use_device(host_data) if_present
        {
            for (int i = 0; i < N; i++) {
                device_data[i] = host_data[i];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (device_data[i] != host_data[i]) {
            printf("Test failed at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}