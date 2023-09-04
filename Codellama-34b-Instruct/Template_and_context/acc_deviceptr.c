#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ACC_DEVICE_PTR(data_arg) (data_arg)
#define ACC_HOST_PTR(data_dev) (data_dev)

int acc_deviceptr(void *data_arg) {
    if (data_arg == NULL) {
        return NULL;
    }
    return ACC_DEVICE_PTR(data_arg);
}

int acc_hostptr(void *data_dev) {
    if (data_dev == NULL) {
        return NULL;
    }
    return ACC_HOST_PTR(data_dev);
}

int main() {
    int *data = malloc(10 * sizeof(int));
    int *data_dev = acc_deviceptr(data);
    int *data_host = acc_hostptr(data_dev);

    if (data_host != data) {
        printf("acc_hostptr returned incorrect host pointer\n");
        return 1;
    }

    free(data);
    return 0;
}