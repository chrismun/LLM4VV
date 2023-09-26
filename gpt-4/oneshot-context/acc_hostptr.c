#include <openacc.h>
#include <stdlib.h>
#include <assert.h>

void test_acc_hostptr() {
    size_t n = 100;
    double *host_data = (double*) malloc(n * sizeof(double));

    // Initialize host_data
    for(size_t i = 0; i < n; ++i)
        host_data[i] = (double)i;

    // Copy data to the device
    double *device_data = (double*) acc_copyin(host_data, n * sizeof(double));

    // Perform test
    double *hostptr = (double*) acc_hostptr(device_data);
    assert(hostptr == host_data);

    // Clean-up
    acc_delete(device_data, n * sizeof(double));
    free(host_data);
}

int main() {
    test_acc_hostptr();
    return 0;
}