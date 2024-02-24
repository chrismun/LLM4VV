#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = NULL;

    #pragma acc data create(device_data[0:N])
    {
        device_data = (int*)acc_malloc(N * sizeof(int));

        #pragma acc kernels
        for (int i = 0; i < N; i++) {
            device_data[i] = i;
        }
    }

    #pragma acc update host(host_data[0:N])

    for (int i = 0; i < N; i++) {
        if (host_data[i] != i) {
            printf("Error: device_resident clause not working as expected\n");
            return 1;
        }
    }

    printf("Success: device_resident clause is working as expected\n");
    return 0;
}