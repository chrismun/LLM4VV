#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int n = 20000;
    float *host = (float*) malloc(n * sizeof(float));
    float *device = (float*) malloc(n * sizeof(float));

    // Init host array
    for(int i = 0; i < n; i++)
        host[i] = i;

    // Start async copy
    #pragma acc enter data copyin(host[0:n]) async(1)

    for(int i = 0; i < n; i++)
        host[i] = 0;

    acc_wait(1);

    // Copy back to host
    #pragma acc exit data copyout(device[0:n])

    // Check result
    for(int i = 0; i < n; i++) {
        if(device[i] != i) {
            printf("Mismatch at position %d: %f != %d\n", i, device[i], i);
            break;
        }
    }

    // Clean up
    free(host);
    free(device);

    return 0;
}