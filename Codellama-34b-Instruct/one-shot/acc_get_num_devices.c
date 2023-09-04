#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int num_devices;
    acc_get_num_devices(&num_devices);

    if (num_devices < 1) {
        printf("Error: No OpenACC devices found.\n");
        return 1;
    }

    printf("Number of OpenACC devices: %d\n", num_devices);

    return 0;
}