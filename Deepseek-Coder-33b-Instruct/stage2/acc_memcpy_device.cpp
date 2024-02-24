#include <stdlib.h>
#include <iostream>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize array a on host
    for(int i = 0; i < N; i++) {
        a[i] = i;
    }

    // Copy data from host to device
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        // Copy data from device to device
        #pragma acc memcpy device(b[0:N], a[0:N])
    }

    // Check if data has been correctly copied
    for(int i = 0; i < N; i++) {
        if(a[i] != b[i]) {
            std::cout << "Data not copied correctly" << std::endl;
            return 1;
        }
    }

    std::cout << "Data copied correctly" << std::endl;
    return 0;
}