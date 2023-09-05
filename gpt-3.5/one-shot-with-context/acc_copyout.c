#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

void acc_copyout(void *data_arg, size_t bytes);
void acc_delete(void *data_arg, size_t bytes);

int test_acc_copyout() {
    int err = 0;
    int size = 10;

    float *data_in = (float *)malloc(size * sizeof(float));
    float *data_out = (float *)malloc(size * sizeof(float));

    #pragma acc data copyin(data_in[0:size])
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; i++) {
            data_out[i] = data_in[i];
        }
    }

    // Check if data_in is not modified on the device
    for (int i = 0; i < size; i++) {
        if (data_in[i] != 0.0) {
            err = 1;
            break;
        }
    }

    // Use acc_copyout to copy data_out from device memory to host memory
    acc_copyout(data_out, size * sizeof(float));

    // Verify if data_out has been properly copied from device memory to host memory
    for (int i = 0; i < size; i++) {
        if (data_out[i] != data_in[i]) {
            err = 1;
            break;
        }
    }

    // Clean up
    free(data_in);
    free(data_out);

    return err;
}

int main() {
    int result = test_acc_copyout();
    if (result == 0) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }
    return 0;