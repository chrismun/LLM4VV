#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    
    // Initialize host data
    int *host_data = (int*) malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        host_data[i] = rand() % 100;
    }
    
    // Allocate device memory
    int *device_data;
    acc_mem_alloc(&device_data, sizeof(int) * N);
    
    // Map host data to device memory
    acc_map_data(host_data, device_data, sizeof(int) * N);
    
    // Access device data and check correctness
    for (int i = 0; i < N; i++) {
        if (device_data[i] != host_data[i]) {
            err = 1;
            break;
        }
    }
    
    // Unmap data to release device memory
    acc_unmap_data(host_data);
    acc_mem_free(device_data);
    
    free(host_data);

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