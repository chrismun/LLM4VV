#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int *host_ptr = (int *) malloc(sizeof(int));

    *host_ptr = 10;

    #pragma acc data copyin(host_ptr) 
    #pragma acc host_data use_device(host_ptr)
    {
        int *device_ptr = host_ptr;

        #pragma acc parallel loop
        for (int i = 0; i < 1; i++) {
            device_ptr[i] = device_ptr[i] * 2;
        }
    }

    if (*host_ptr != 20) {
        err = 1;
    }

    free(host_ptr);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}