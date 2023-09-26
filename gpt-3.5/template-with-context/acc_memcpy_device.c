#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int* host_data = (int*)malloc(N * sizeof(int));
    int* device_data1 = (int*)acc_malloc(N * sizeof(int));
    int* device_data2 = (int*)acc_malloc(N * sizeof(int));

    // Initialize host_data
    for (int i = 0; i < N; i++) {
        host_data[i] = rand();
    }

    // Copy host_data to device_data1
    acc_memcpy_device(device_data1, host_data, N * sizeof(int));

    // Copy device_data1 to device_data2
    acc_memcpy_device(device_data2, device_data1, N * sizeof(int));

    // Verify the data on device_data2
    for (int i = 0; i < N; i++) {
        if (device_data2[i] != host_data[i]) {
            err = 1;
            break;
        }
    }

    // Free memory
    free(host_data);
    acc_free(device_data1);
    acc_free(device_data2);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}