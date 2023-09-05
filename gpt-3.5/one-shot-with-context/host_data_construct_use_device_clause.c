int test_host_data_use_device()
{
    int err = 0;
    int num_devices, device;

    #pragma acc deviceinfo num_devices(num_devices)
    for (device = 0; device < num_devices; device++) {
        int *device_ptr = NULL;
        int *host_ptr = (int *) malloc(sizeof(int));

        #pragma acc host_data use_device(device_ptr) if(device_ptr != NULL)
        {
            if (device_ptr == NULL) {
                device_ptr = (int *) malloc(sizeof(int));
            }
            *device_ptr = *host_ptr;
        }

        if (*host_ptr != *device_ptr) {
            err += 1;
        }

        free(device_ptr);
        free(host_ptr);
    }

    return err;
}

int main()
{
    int failcode = 0;
    int failed;

    failed = test_host_data_use_device();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}