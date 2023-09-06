#ifndef T1
//T1:runtime,init,devonly-1.0
int test1(){
    int err = 0;

    if (acc_get_device_type() != acc_device_none){
        acc_init(acc_get_device_type());
        acc_shutdown(acc_get_device_type());
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,init,devonly-1.0
int test2(){
    int err = 0;
    int device_num = 0;

    if (acc_get_device_type() != acc_device_none){
        if (acc_get_device_type() == acc_device_host){
            device_num = acc_get_device_num(acc_device_host) + 1;
            if (device_num > acc_get_num_devices(acc_device_host)){
                device_num = acc_get_device_num(acc_device_host) - 1;
            }
        }
        else if (acc_get_device_type() == acc_device_default){
            device_num = acc_get_device_num(acc_device_default);
        }

        acc_init_device(device_num, acc_get_device_type());
        acc_shutdown(acc_get_device_type());
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}