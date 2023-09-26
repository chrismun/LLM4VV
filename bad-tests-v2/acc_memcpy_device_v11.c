#ifndef T1
//T1:acc memcpy device,V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 1024;
    srand(SEED);
    
    // Allocate data on the device
    float *data_src_device = (float *) acc_malloc(size * sizeof(float));
    float *data_dest_device = (float *) acc_malloc(size * sizeof(float));

    // Initialize data on host
    float *data_src_host = (float *) malloc(size * sizeof(float));
    for(int i = 0; i < size; i++)
        data_src_host[i] = (float) rand() / RAND_MAX;

    // Copy data host to device
    acc_memcpy_to_device(data_src_device, data_src_host, size * sizeof(float));

    // Do the acc_memcpy_device copying
    acc_memcpy_device(data_dest_device, data_src_device, size * sizeof(float));

    // Copy back the data to the host
    float *data_dest_host = (float *) malloc(size * sizeof(float));
    acc_memcpy_to_device(data_dest_host, data_dest_device, size * sizeof(float));

    // Verify the copied data
    for(int i = 0; i < size; i++){
        if(data_src_host[i] - data_dest_host[i] > 1e-5){
            err = 1;
            break;
        }
    }

    // Free allocated memory
    acc_free(data_src_device);
    acc_free(data_dest_device);
    free(data_src_host);
    free(data_dest_host);

    return err;
}
#endif