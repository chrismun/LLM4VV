#ifndef T1
//T1:devices,devonly,compile-auto
int test1(){
    int err = 0;
    int num = acc_get_num_devices(acc_get_device_type());
    if (acc_get_device_type() == acc_device_none){
        if (num != 1){
            err += 1;
        }
    }
    else{
        if (num < 1){
            err += 1;
        }
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