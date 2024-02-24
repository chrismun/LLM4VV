#include <omp.h>
#include <stdio.h>

int main() {
    int default_device = omp_get_default_device();
    int num_devices = omp_get_num_devices();

    printf("Default device: %d\n", default_device);
    printf("Number of devices: %d\n", num_devices);

    for (int i = 0; i < num_devices; i++) {
        omp_set_default_device(i);
        int current_device = omp_get_default_device();
        printf("Current device: %d\n", current_device);
    }

    return 0;
}