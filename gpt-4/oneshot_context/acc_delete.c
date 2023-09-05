void run_test(float *data) {
    float *dev_data;
    int i;

    // Allocate memory on the device
    dev_data = (float*)acc_malloc(N*sizeof(float));

    // Initialize data on the host
    for (i = 0; i < N; i++) {
        data[i] = (float)i;
    }

    // Copy data from the host to the device
    acc_memcpy_to_device(dev_data, data, N*sizeof(float));

    // Perform some operations on the data on the device
    #pragma acc parallel loop present(dev_data)
    for (i = 0; i < N; i++) {
        dev_data[i] = dev_data[i] * 2.0f;
    }

    // Copy data from the device to the host
    acc_copyout(data, N*sizeof(float));

    // Delete data from the device
    acc_delete(dev_data, N*sizeof(float));
}

int main() {
    float *data = (float*)malloc(N*sizeof(float));
  
    run_test(data);
  
    // Check results
    for (int i = 0; i < N; i++) {
        if (data[i] != i * 2.0f) {
            printf("Test failed! data[%d] = %f, expected %f\n", i, data[i], i*2.0f);
            return EXIT_FAILURE;
        }
    }

    printf("Test passed!\n");

    // Cleanup and exit
    free(data);
  
    return EXIT_SUCCESS;
}