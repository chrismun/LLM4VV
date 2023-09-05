#include <stdio.h>
#include <openacc.h>

int main()
{
    int N = 100;
    double *x_host, *x_device, sum;

    // Allocate space on the host and device
    x_host = (double*) malloc(N * sizeof(double));
    x_device = (double*) acc_malloc(N * sizeof(double));

    // Initialize the host data
    for (int i = 0; i < N; i++)
        x_host[i] = 1.0;

    // Transfer to the device
    acc_memcpy_to_device(x_device, x_host, N * sizeof(double));

    // Compute the sum on the device
    #pragma acc parallel loop deviceptr(x_device) reduction(+:sum)
    for (int i = 0; i < N; i++)
        sum += x_device[i];

    // Check the result
    if (sum != N)
        printf("Test failed!\n");
    else
        printf("Test passed!\n");

    // Clean up
    free(x_host);
    acc_free(x_device);

    return 0;
}