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
        #pragma acc kernels
        {
            for (int i = 0; i < N; i++) {
                device_data[i] = host_data[i];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (host_data[i] != device_data[i]) {
            printf("Error: host_data[%d] = %d, device_data[%d] = %d\n", i, host_data[i], i, device_data[i]);
            return 1;
        }
    }

    printf("Copyout clause verified successfully.\n");
    return 0;
}