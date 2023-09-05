#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate and initialize host data
    int *host_data = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        host_data[i] = rand() % 100;
    }

    // Allocate and map device data
    int *device_data;
    #pragma acc enter data create(device_data[0:N])

    // Map host data to device
    #pragma acc update device(device_data[0:N])

    // Unmap device data
    #pragma acc unmap data(device_data)

    // Verify the device data is unmapped
    #pragma acc update self(device_data[0:N])
    for (int i = 0; i < N; i++) {
        if (device_data[i] != host_data[i]) {
            err = 1;
            break;
        }
    }

    // Free host and device data
    free(host_data);
    #pragma acc exit data delete(device_data)

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