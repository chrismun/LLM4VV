#include <stdlib.h>
#include <openacc.h>

int main() {
    int *host_data = (int*)malloc(100 * sizeof(int));
    int *device_data = acc_malloc(100 * sizeof(int));

    // Map the host and device data
    acc_map_data(host_data, device_data, 100 * sizeof(int));

    // Unmap the host data
    acc_unmap_data(host_data);

    // Free the device data
    acc_free(device_data);

    return 0;
}