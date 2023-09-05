#ifndef T1
//T1:directive,data,data-region,V:2.7
int test1(){
    int err = 0;
    srand(SEED);

    int device_type;

    #pragma acc set device_type(acc_device_default)
    device_type = acc_get_device_type();

    if (device_type != acc_device_default){
        err += 1;
    }

    #pragma acc set device_type(acc_device_host)
    device_type = acc_get_device_type();

    if (device_type != acc_device_host){
        err += 2;
    }

    #ifdef _OPENACC
    #pragma acc set device_type(acc_device_not_host)
    device_type = acc_get_device_type();

    if (device_type != acc_device_not_host){
        err += 4;
    }
    #endif

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