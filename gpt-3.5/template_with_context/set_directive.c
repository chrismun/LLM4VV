#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc set device_num(0)
    #pragma acc set default_async(acc_async_sync)
    #pragma acc set device_type(nvidia)
    #pragma acc set if(0)

    // Check if the set directives have been applied correctly
    if (acc_get_device_num() != 0) {
        err = 1;
    }
    if (acc_get_default_async() != acc_async_sync) {
        err = 1;
    }
    if (acc_get_device_type() != acc_device_nvidia) {
        err = 1;
    }

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